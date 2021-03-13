#include <iostream>
#include <map>
#include <set>
#include <sstream>
#include <stdexcept>
#include <string>
#include <vector>

using namespace std;

template <class T>
ostream& operator << (ostream& os, const vector<T>& s) {
  os << "{";
  bool first = true;
  for (const auto& x : s) {
    if (!first) {
      os << ", ";
    }
    first = false;
    os << x;
  }
  return os << "}";
}

template <class T>
ostream& operator << (ostream& os, const set<T>& s) {
  os << "{";
  bool first = true;
  for (const auto& x : s) {
    if (!first) {
      os << ", ";
    }
    first = false;
    os << x;
  }
  return os << "}";
}

template <class K, class V>
ostream& operator << (ostream& os, const map<K, V>& m) {
  os << "{";
  bool first = true;
  for (const auto& kv : m) {
    if (!first) {
      os << ", ";
    }
    first = false;
    os << kv.first << ": " << kv.second;
  }
  return os << "}";
}

template<class T, class U>
void AssertEqual(const T& t, const U& u, const string& hint = {}) {
  if (t != u) {
    ostringstream os;
    os << "Assertion failed: " << t << " != " << u;
    if (!hint.empty()) {
       os << " hint: " << hint;
    }
    throw runtime_error(os.str());
  }
}

void Assert(bool b, const string& hint) {
  AssertEqual(b, true, hint);
}

class TestRunner {
public:
  template <class TestFunc>
  void RunTest(TestFunc func, const string& test_name) {
    try {
      func();
      cerr << test_name << " OK" << endl;
    } catch (exception& e) {
      ++fail_count;
      cerr << test_name << " fail: " << e.what() << endl;
    } catch (...) {
      ++fail_count;
      cerr << "Unknown exception caught" << endl;
    }
  }

  ~TestRunner() {
    if (fail_count > 0) {
      cerr << fail_count << " unit tests failed. Terminate" << endl;
      exit(1);
    }
  }

private:
  int fail_count = 0;
};

bool IsPalindrom(const string& str) {
  // Вы можете вставлять сюда различные реализации функции,
  // чтобы проверить, что ваши тесты пропускают корректный код
  // и ловят некорректный
  return true;
}

void TestPredefined() {
  /*
считает пустую строку палиндромом;
считает строку из одного символа палиндромом;
осуществляет обычное сравнение символов на равенство, не игнорируя никакие символы, в том числе пробельные.
При разработке тестов подумайте, какие ошибки можно допустить при реализации функции IsPalindrom. Примеры ошибок:
игнорируется первый или последний символ;
сравнение соответствующих символов завершается не в середине строки, а раньше;
игнорируются пробелы
  */
        AssertEqual(IsPalindrom("madam"), true);



        AssertEqual(IsPalindrom("level"), true);



        AssertEqual(IsPalindrom("wasitacaroracatisaw"), true);



        AssertEqual(IsPalindrom("gentleman"), false);


        AssertEqual(IsPalindrom("abcca"), false);

        AssertEqual(IsPalindrom("abcbc"), false);



        AssertEqual(IsPalindrom("abba"), true);

        AssertEqual(IsPalindrom("ab"), false);


        AssertEqual(IsPalindrom("abcdefghijklmnopqrstuvwxyzzyxwvutsrqponmlkjihgfedcba"), true);

        AssertEqual(IsPalindrom("abcdefghijklnopqrstuvwxyzzyxwvutsrqponmlkjihgfedcba"), false);


        AssertEqual(IsPalindrom("aA"), false);

        AssertEqual(IsPalindrom("asitacaroracatisaw"), false);

        AssertEqual(IsPalindrom("wasitacaroracatisa"), false);

        AssertEqual(IsPalindrom("sitacaroracatisaw"), false);


        AssertEqual(IsPalindrom("wasitacaroracatis"), false);


        AssertEqual(IsPalindrom(""), true);

        AssertEqual(IsPalindrom("a"), true);

        AssertEqual(IsPalindrom("kay ak"), false);

        AssertEqual(IsPalindrom("kay\tak"), false);

        AssertEqual(IsPalindrom(" kayak"), false);
        AssertEqual(IsPalindrom("\t\n  \n\t"), true);
    AssertEqual(IsPalindrom(""), true,"q");
    AssertEqual(IsPalindrom("a"), true,"w");
    AssertEqual(IsPalindrom("a b a"), true,"e");
    AssertEqual(IsPalindrom("amadam"), false,"r");
    AssertEqual(IsPalindrom("madama"), false,"r1");
    AssertEqual(IsPalindrom("madxama"), false,"r3");
    AssertEqual(IsPalindrom("wasitacaroracatisaw"),true,"t");
}

int main() {
  TestRunner runner;

  runner.RunTest(TestPredefined, "TestPredefined");
  return 0;
}
