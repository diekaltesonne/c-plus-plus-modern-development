#include <iostream>

using namespace std;
/*
 * В случае, если строка left не равна строке right,
 * функция должна выбрасывать исключение runtime_error с содержанием "<l> != <r>", где <l> и <r> - строки,
 * которые хранятся в переменных left и right соответственно. Обратите внимание, что вокруг знака неравенства в строке,
 * которая помещается в исключение, должно быть ровно по одному пробелу.
 * Если left == right, функция должна корректно завершаться.
*/

void EnsureEqual(const string& left, const string& right);
int main() {
  try {
    EnsureEqual("C++ White", "C++ White");
    EnsureEqual("C++ White", "C++ Yellow");
  } catch (runtime_error& e) {
    cout << e.what() << endl;
  }
  return 0;
}

void EnsureEqual(const string& s, const string& t) {
    if (s != t) {
        throw runtime_error(s + " != " + t);
    }
}
