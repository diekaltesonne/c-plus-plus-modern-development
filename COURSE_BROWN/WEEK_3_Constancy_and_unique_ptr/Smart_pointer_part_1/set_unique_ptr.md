## set<unique_ptr>
На лекции для того, чтобы сохранить множество объектов unique_ptr, мы использовали тип unordered_map<T*, unique_ptr<T>>. Что выглядит несколько необоснованно, ведь, казалось бы, нам нужно множество, а тут у нас словарь (хеш-таблица).

В этом материале мы разберёмся, как использовать для этой задачи именно множество.

Логично было бы использовать контейнер unordered_set, но для этого нам нужно ещё кое-что узнать об умных указателях, так что к этому подходу мы вернёмся ближе к концу блока.

А пока давайте посмотрим, как решить эту задачу с использованием контейнера set. Объявим поле allocated как set<unique_ptr<T>>. Тогда реализация метода Allocate() примет следующий вид:


Как видим, никаких проблем не возникло. При использовании unordered_map мы писали allocated[ret] = move(ptr);, а при использовании set пишем allocated.insert(move(ptr));. Здесь всё хорошо. Аналогично с методом TryAllocate() --- он вообще не изменится.

Интереснее дела обстоят с методом Deallocate(). Он принимает сырой указатель T*, и затем ищет его в контейнере:


И вот тут-то начинаются проблемы.

## Поиск элемента
На лекции мы используем контейнер unordered_map, ключом которого является тот же самый сырой указатель T*. Поэтому метод find() работает прекрасно. Но теперь мы поменяли контейнер на set, и его ключами будут умные указатели unique_ptr<T>. А это, вообще говоря, совершенно другой тип. Давайте посмотрим документацию метода find() контейнера set:


Как видим, у него есть четыре перегрузки. При этом, перегрузки (1) и (2) нам не подходят, т.к. они принимают const Key&, то есть в нашем случае это будет const unique_ptr<T>&. Но у нас есть только сырой указатель! Мы не можем просто так взять и создать из него unique_ptr, т.к. последний удалил бы объект в своём деструкторе.

Значит, нам нужны перегрузки (3) или (4) (они отличаются только константностью). Посмотрим, что про них пишет документация:

3,4) [...] This overload only participates in overload resolution if the qualified-id Compare::is_transparent is valid and denotes a type. It allows calling this function without constructing an instance of Key.

Последнее предложение звучит именно как то, что нам нужно. Но что же значит загадочная фраза "qualified-id Compare::is_transparent is valid"?.. Чтобы в этом разобраться, начнём с того, что такое Compare.

## Пользовательский компаратор
Если мы посмотрим на документацию контейнера set, то увидим, что, помимо ключа Key, шаблон также принимает второй параметр Compare (ну, технически, там ещё есть третий параметр Allocator, но он нас сейчас не интересует). Про него сказано:

Sorting is done using the key comparison function Compare.

То есть Compare отвечает за сортировку элементов в множестве. По умолчанию они сортируются с использованием обычного сравнения "<". Но мы можем передать свой функтор, который определит произвольный порядок на этом множестве. Этот функтор называется компаратором.

Теперь вернёмся к фразе "qualified-id Compare::is_transparent is valid". Она значит, что в нашем компараторе определён вложенный тип is_transparent. Не важно, что именно это за тип. Важно, что он должен быть. Компаратор, в котором этот тип определён, называется прозрачным. Если множество использует прозрачный компаратор, то в нём доступны перегрузки (3) и (4) метода find().

Но почему бы не сделать эти перегрузки доступными всегда?.. Тут дело в богатом наследии С++. Дело в том, что вплоть до стандарта С++14 в контейнере set вообще нельзя было найти элемент, если у тебя нет значения точно такого же типа. В С++14 эту проблему исправили, добавив перегрузки (3) и (4). Но, чтобы не сломать существующий код, сделали так, что по умолчанию они не используются. А "прозрачный компаратор" - это просто хитрое название для "включателя дополнительных перегрузок метода find()".

Давайте теперь напишем наш компаратор и используем его для множества. Поскольку мы не хотим менять сам порядок элементов (мы просто хотим сделать компаратор прозрачным), определим operator() так, чтобы он просто вызывал стандартное сравнение через "<":


Ок, с этим разобрались. Теперь в метод find() можно передавать сырой указатель. Но вот беда - С++ из коробки не умеет сравнивать сырой указатель с unique_ptr. На всякий случай. Чтобы избежать неправильного использования. Ведь это, вообще говоря, разные типы.

## Сравнение T* и unique_ptr<T>
Казалось бы, что может быть проще. Если операций сравнения нет, то надо их определить. Причём, у нас уже есть компаратор, куда мы можем их положить!


С заголовками этих функций всё понятно. Но в теле появился странный функтор less, который мы используем для сравнения указателей. Поскольку он используется для сравнения, он тоже является компаратором.

Дело в том, что в С++ нельзя сравнивать указатели двух никак не связанных объектов с помощью стандартных операций сравнения ("<", "<=", ">", ">="). То есть если эти объекты лежат в одном массиве, или если они содержатся в качестве членов в другом объекте, то их сравнивать можно. А вот если это просто два объекта, которые были независимо созданы в куче, то уже нельзя. Точнее, сравнить-то их можно, и компилятор это разрешит, и это даже, вероятнее всего, будет работать. Но правильный порядок не гарантируется. И на некоторых платформах/компиляторах это вдруг внезапно может выстрелить. Например, для двух указателей p1 и p2 может вдруг оказаться, что условия p1 < p2 и p2 < p1 оба будут истинны.

Это происходит потому, что, в общем случае, указатель может быть сложносоставной сущностью. Это в наиболее распространённой модели памяти, используемой на большинстве современных компьютеров, указатель представляет собой просто индекс ячейки в линейном массиве памяти. Пусть и виртуальной. Но есть платформы, где адресация памяти не такая простая. Если бы С++ гарантировал, что операции сравнения всегда дают ожидаемые результаты, то компиляторам под данные платформы пришлось бы генерировать менее оптимальный код. А это против идеологии С++.

Поэтому, если вы действительно хотите получить правильный порядок при сравнении указателей, даже в случае указателей на несвязанные объекты, нужно об этом компилятору в явном виде сказать. И делается это, при помощи специального компаратора less. Выражение less<const T*>() инстанцирует шаблон класса less для указателя const T* и создаёт объект компаратора (здесь мы везде используем указатели на константу, т.к. обычные указатели могут быть неявно к ним преобразованы, но не наоборот). У него будет вызван operator(), куда мы передадим два указателя. Один возьмём напрямую из параметра функции, а второй вытащим из unique_ptr с помощью метода get(). И уже operator() вернёт нам результат сравнения.

Таким образом, выражение less<const T*>()(lhs.get(), rhs) вернёт нам по сути то же самое, что и обычное lhs.get() < rhs, но только с гарантией, что это будет всегда правильно работать.

Теперь остался последний шаг.

##Перемещение ключа
На лекции для перемещения элемента из множества занятых объектов в очередь свободных объектов в методе Deallocate() мы использовали следующий код:


где итератор it был найден ранее с помощью метода find(). Здесь всё понятно - переместили значение и удалили элемент. Однако, с контейнером set такой номер не пройдёт, потому как unique_ptr является не значением элемента, а ключом. А просто так модифицировать ключ в ассоциативном контейнере нельзя - сломается механизм индексации (в случае упорядоченного контейнера - может нарушиться порядок). А перемещение из ключа ещё как его модифицирует.

К счастью, из лекций по ассоциативным контейнерам мы уже знаем, как бороться с этой проблемой. Нам поможет метод extract():


То есть мы сначала извлекаем узел из множества, и после этого можем переместить из него ключ.

##Всё вместе
Ух. Вот теперь мы готовы написать полную реализацию класса ObjectPool с использованием контейнера set:


Как видим, изменений потребовалось немного. Но они требуют понимания некоторых дополнительных возможностей языка. Знание этих возможностей не понадобится вам в рамках данного блока, но наверняка может оказаться полезным в реальной разработке.
