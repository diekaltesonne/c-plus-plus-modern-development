# Решение проблемы с тестом TestLooping
Функция TestLooping в заготовке решения выглядит так

```c++
void TestLooping() {
  vector<int> v(15);
  iota(begin(v), end(v), 1);

  Paginator<vector<int>::iterator> paginate_v(v.begin(), v.end(), 6);
  ostringstream os;
  for (const auto& page : paginate_v) {
    for (int x : page) {
      os << x << ' ';
    }
    os << '\n';
  }

  ASSERT_EQUAL(os.str(), "1 2 3 4 5 6 \n7 8 9 10 11 12 \n13 14 15 \n");
}
```

Давайте заглянем внутрь файла test_runner.h и посмотрим, во что раскроется макрос ASSERT_EQUAL:

```c++
void TestLooping() {
  vector<int> v(15);
  iota(begin(v), end(v), 1);

  Paginator<vector<int>::iterator> paginate_v(v.begin(), v.end(), 6);
  ostringstream os;
  for (const auto& page : paginate_v) {
    for (int x : page) {
      os << x << ' ';
    }
    os << '\n';
  }

  // ASSERT_EQUAL(os.str(), "1 2 3 4 5 6 \n7 8 9 10 11 12 \n13 14 15 \n");
  // раскроется в код ниже:
  {
    ostringstream os;
    os << os.str() << " != " << "1 2 3 4 5 6 \n7 8 9 10 11 12 \n13 14 15 \n" << ", "
       << "[здесь будет имя вашего файла]" << ":" << 45;
    AssertEqual(os.str(), "1 2 3 4 5 6 \n7 8 9 10 11 12 \n13 14 15 \n", os.str())   ;
  }
}
```

Теперь становится понятно, почему TestLooping может вести себя неадекватно: переменная os, объявленная в теле макроса, перекрывает переменную os из функции TestLooping. Решить эту проблему несложно — надо в теле макроса выбрать такое имя переменной, которое с малой вероятностью будет использоваться в пользовательском коде:

```c++
#define ASSERT_EQUAL(x, y) {                          \
  ostringstream __assert_equal_private_os;            \
  __assert_equal_private_os                           \
    << #x << " != " << #y << ", "                     \
    << __FILE__ << ":" << __LINE__;                   \
  AssertEqual(x, y, __assert_equal_private_os.str()); \
}
```
