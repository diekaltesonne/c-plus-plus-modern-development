
1. Задание очень мощное с точки зрения изучения языка и стандартной библиотеки
2. На решение задачи было потрачено 16 submit'ов, из которых, в разбивке по проблемам:

1 шт - тестирующая система под linux, соответственно имена ваших собственных *.h и *.cpp файлов - case sensitive! То есть если у вас #include "MyParse.h" а файл "myparse.h" - то не смотря на успешную компиляцию в Win, тестирующая система сообщит что ваш MyParse.h не найден, будьте внимательны

3 шт - не забывайте, что в тестирующей системе УЖЕ есть свой собственный test_runner, реализация которого ОТЛИЧАЕТСЯ (!) от той которая выложена в качестве решения в "Неделя 2 / Код фреймворка юнит-тестов" (https://www.coursera.org/learn/c-plus-plus-yellow/supplement/bTQAM/kod-frieimvorka-iunit-tiestov) - как минимум тем, что в тестирующей системе УЖЕ РЕАЛИЗОВАНА перегрузка << для vector<T>; моя персональная драма была в том, что я, (как и советовал Илья на Неделе 2) действительно взял и улучшил, доработал, фреймворк, улучшил формат вывода, перегрузил операторы для vector в том числе, а также для tuple, и проч.; - и естественно при сабмите я забыл что в тестирующей системе уже есть test_runner; 3 сабмита потратил на то чтобы понять что там внутри этого test_runner'а определено а что нет

2 шт - на мой взгляд наиболее бесполезная и бестолковая трата времени и эмоций за всё задание; обратите внимание на функцию ParseDate: ей в параметр оказывается (!) нужно передавать istream& А НЕ istringstream& как напрямую следует из контекста заготовок main.cpp и condition_parser.cpp; более подробный разбор с ответами в ветке обсуждения "Function Date ParseDate(istream&) not found in your submission" (https://www.coursera.org/learn/c-plus-plus-yellow/programming/n1Nbg/kursovoi-proiekt/discussions/threads/jM0WKdvNEemdBwrrZ59Rdg); в итоге я сделал так: объявил и определил две идентичные функции ParseDate, одну с istringstream&, которой я везде и пользовался, и вторую с istream& - для того чтобы заткнуть ей тестирующую систему;

6 шт - тест # 13 / 19 - из 6 сабмитов 3 честно признаюсь я потратил на бесполезные попытки понять природу теста :) я разными способами реализовывал отладочный вывод в stderr чтобы увидеть в выводе тестирующей системы его содержимое в случае неуспешного окончания теста, (что кстати работало на тестовых заданиях раньше) - но в этот раз, к сожалению это было впустую потраченное мною время; догадываться что тест #13 - это тест на Add пришлось из форума; для прохождения теста мне пришлось: а. упростить парсер даты (сделать его линейным безо всяких лишних проверок, просто взял его из Белого Пояса) и b. убрать из Add алгоритм линейной сложности для проверки существования события в дате: пришлось добавить параллельную структуру данных поиск наличия в которой уже был logN сложности; на эти a. и b. (а также на исправление опечатки в коде связанной с пропущенным пространством имен std) ушли оставшиеся 3 сабмита потраченные на #13 тест; (то есть подтверждаю из своего опыта: тест # 13 / 19 - это нагрузочный тест на Add)

2 шт - тест # 14 / 19 - собственно первый сабмит здесь уже преодолел тест # 13 заткнулся сразу же на тесте # 14 = Failed case #14/19: Wrong answer (Time used: 0.21/1.50); посмотрел код, и почти сразу нашел проблему - она появилась после появления параллельной структуры данных для прохождения теста # 13 - по ошибке две строки кода следующие друг за другом должны были идти наоборот, - просто невнимательность; собственно после исправления этой ошибки, второй сабмит был потрачен на опечатку в коде, забыл закомментировать использование перегруженного оператора << в собственной отладочной функции, << был НЕ определен в тестирующем test_runner (! опять test_runner - хз что там у них внутри !!!); итого тест # 14 - это тест на Del;

2 шт - тест # 19 / 19 - первый сабмит прошедший тест # 14 запоролся здесь на быстродействии теста # 19; в качестве решения я добавил еще одну паралелльную структуру данных, теперь уже для хранения последнего события в дате (map<Date, string>); ну и в итоге после определения еще одной описанной выше структуры данных и корректировки логики Add и Del - курс Желтый Пояс наконец-то сдался, Good job! (Max time used: 0.46/1.50);

3. В самом начале было потрачено очень много медитативного времени на осознание парсера условий с shared_ptr. Сейчас могу сказать что это реально полезное упражнение, без заглядывания в подсказки, как я действовал:

* детально несколько дней втыкал в код парсера к Неделе 5 (https://www.coursera.org/learn/c-plus-plus-yellow/supplement/SZRdK/kod-parsiera-k-liektsii) - по сути абсолютно идентичная тема

* как я вижу что там что здесь в курсовой работе это что-то вроде "обратной польской записи" или похожее - для разбора синтаксических выражений (https://ru.wikipedia.org/wiki/%D0%9E%D0%B1%D1%80%D0%B0%D1%82%D0%BD%D0%B0%D1%8F_%D0%BF%D0%BE%D0%BB%D1%8C%D1%81%D0%BA%D0%B0%D1%8F_%D0%B7%D0%B0%D0%BF%D0%B8%D1%81%D1%8C)

* основное что нужно понять: синтаксическое дерево создается посредством создания объектов разного назначения унаследованных от Node, и объекты связаны друг с другом через shared_ptr; то есть при разборе синтаксического дерева в поля объекта логической операции записываются shared_ptr указывающие на левую и правую часть этой операции (_left это lhs а _expr это rhs)

* через эти shared_ptr операции объединяются в дерево, каждый объект узла логической операции содержит в своих полях ссылки на объекты операций ниже уровнем

* Evaluate определенная для каждого типа узла просто выдает ответ по этому конкретному узлу, когда этот узел ture а когда false
(я даже чтобы всё это понять и протестировать аналогично Evaluate написал свой метод Print - чтобы при отладке видеть как код воспринимает входное выражение и параметры)

* у меня конечно больше всего времени ушло на то чтобы понять через что объекты выражения друг с другом связаны хотя в общем это на поверхности

Всем привет! Только что закончил проект. Потратил на это три дня. Без помощи других я бы не справился, поэтому вижу своим долгом помочь будущим поколениям.

Я решил написать несколько важных советов, а так же сделать подарок в конце поста.

1. template <class Func> int RemoveIf(Func func) и FindIf можно написать с такой вот шапкой в .h файле.
2. Все наверняка возьмут код из финального задания белого пояса. Там некоторые шапки придется изменить, например 3. ParceDate теперь должна принимать istream.
3. Вам понадобятся две структуры данных для базы, одна с которой мы все знакомы это словарь из Date в set<string>, другая для хранения очередности добавления.
4. Везде используйте методы контейнеров, а не функции из algorithms, если возможно однако такие вещи как find_if и stable_partition вам понадобятся.
5. Не бойтесь делать циклы вложенными (этого не избежать), только помните, что супер важно делать итерируясь с помощью ИТЕРАТОРОВ, никаких range based for, так как вам будет необходимо менять контейнеры в процессе итерации.
6. В Last вам хватит одного upper_bound (родного метода!).
7. Для Add прочитайте что возвращает insert словаря.
8. Для RemoveIf вам понадобится stable_partition.
9. Для Find_If - find_if c полученными предикатом.

Когда начинал думал, что придется много попотеть. Так и вышло. Главное не сдавайтесь, ведь знания получаются качественнее. Тяжело в учении легко в бою.

А в подарок я выкладываю файл со ВСЕМИ тестами, которые мне удалось найти + те которые я написал сам. Надеюсь это очень вам поможет как помогло мне. Спасибо друзья!

Ставьте Star если помогло!

https://gist.github.com/SergeiShumilin/a030350c6226b8091b57ed0c7ccba779

А по сути - запрос обрабатывается по принципу: найти все события, удовлетворяющие предикату. В Вашем примере- должны быть выбраны все события за все даты лексикографически большие , чем Holyday. Например События w1, w2, и zqwertyuiuytrewq.


Для чего нужен EmptyNode:
Из инструкций:
Для Del: Если условие пусто, результатом выполнения команды должна стать очистка всей базы данных.
Для Find: Поиск с пустым условием эквивалентен команде Print.
