1. Если в структуре Access сначала хранить ссылку на V , а потом lock_guard , то при ее инициализации будет момент когда ссылка уже передалась ,а lock еще нет. И потоки получат запрет доступа постфактум. Решение - правильная последовательность полей в Access и инициализация через Copy Elision
```
{lock_guard,data}
```
2. В BuildOrdinaryMap стоит делать lock_guard в цикле.Что важно - не забудьте сохранить lock_guard в переменную (вспомните про время жизни объектов)
3. Задачу можно решить не нагородив огород из vector<mutex> , list<lock_guard> гениальных блокировочных структур и тому подобного. Решение может быть простым и изящным . Не тратьте на это 3 дня , как сделал я.
4. Следует придумать способ преобразования любого ключа (целого числа) в номер одного из кусков. Если у вас 100 кусков, то вам нужно преобразовать ключ в число от 0 до 99.
5. Учтите, что ключи могут быть отрицательными
6. Если вы хотите, чтобы обьект конструировался сразу в структуре Access, то тут нужно использовать copy elision. Для этого используйте список инициализации {object} (То есть через конструктор Access copy elision не получится сделать. Поэтому конструктора там не должно быть, если вы планируете использовать copy elision)


1. Проблема: Из разных потоков мы не можем обращаться к одной map.
Путь к решению: Мы можем разбить исходную map на несколько и контролировать, чтобы только к каждой из них обращались по очереди (Тут нам и понадобится bucket_count). Для этого, заведем для каждой такой map’ы свой mutex. И теперь перед тем, как брать значение из map будем делать блокировку на соответствующем ей mutex.

2. Проблема: Как тогда можно передать lock_guard, созданный на этапе 1 в Access?
Путь к решению: Тут уже есть варианты, как это можно сделать. Я решил, что будет понятней, если мы сделаем еще один lock_guard, но уже внутри Access. Как мне кажется, это и идеологически правильней – все-таки тут эти lock_guard используются для разных задач. (Авторы делают этот шаг по-другому, объединяя мой пункт 1 и 2 в один)

3. Проблема: На каком mutex мы должны замкнуть lock_guard из пункта 2?
Путь у решению: Кажется очевидным, что мы должны использовать тот же mutex, что и в пункте 1, но тут есть проблема – тот lock_guard, что мы создали в пункте 1 еще живет => еще держит этот mutex, поэтому при конструировании нового lock_guard и попытки захватить этот mutex нас ждет dead lock. Поэтому можно создать еще один набор mutex, элементы которого мы уже будем использовать для передачи в Access. Не очень красиво, но зато последовательно. (Для авторского решения этой проблемы нет)

4. Проблема: Каким образом в таком случае реализовать BuildOrdinaryMap?
Путь у решению: Мы должны синхронизироваться на обоих mutex перед тем как достанем все ключ-значения из очередного map.