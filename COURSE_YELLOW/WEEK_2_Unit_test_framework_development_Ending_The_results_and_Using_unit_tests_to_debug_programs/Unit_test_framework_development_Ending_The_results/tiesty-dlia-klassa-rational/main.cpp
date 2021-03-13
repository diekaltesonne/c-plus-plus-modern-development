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
/*
class Rational{
public:
  // Вы можете вставлять сюда различные реализации,
  // чтобы проверить, что ваши тесты пропускают корректный код
  // и ловят некорректный
  Rational();
  Rational(int numerator, int denominator) {
  }

  int Numerator() const {
  }

  int Denominator() const {
  }
};
*/

// Конструктор по умолчанию должен создавать дробь с числителем 0 и знаменателем 1.
void Default_construct(){
  Rational x;
  AssertEqual(x.Numerator(),0,
  "numerator 0");
  AssertEqual(x.Denominator(),1,
  "denominator 0");

}

//При конструировании объекта класса Rational с параметрами p и q должно выполняться сокращение дроби p/q.
void Construct_with_paramether_pq(){
  Rational x(5,20);
  Rational x1(3,9);
  Rational x2(2,6);
  AssertEqual(x.Numerator(),1,
  "numerator 1");
  AssertEqual(x.Denominator(),4,
  "denominator 5");

  AssertEqual(x1.Numerator(),1,
  "numerator 1");
  AssertEqual(x1.Denominator(),3,
  "denominator 3");

  AssertEqual(x2.Numerator(),1,
  "numerator 1");
  AssertEqual(x2.Denominator(),3,
  "denominator 3");

}

//Если дробь p/q отрицательная, то объект Rational(p, q) должен иметь отрицательный numerator и положительный denominator.
void Fraction_is_negative(){

  Rational x(2,-3);
  AssertEqual(x.Numerator(),-2,
  "numerator -2");
  AssertEqual(x.Denominator(),3,
  "denominator 3");

  Rational x1(-1,2);
  AssertEqual(x1.Numerator(),-1,
  "numerator -1");
  AssertEqual(x1.Denominator(),2,
  "denominator 2");

}

//Если дробь p/q положительная, то объект Rational(p, q) должен иметь положительные numerator и denominator (обратите внимание на случай Rational(-2, -3)).
void Fraction_is_positive(){

  Rational x(-2,-3);
  AssertEqual(x.Numerator(),2,
  "numerator 2");
  AssertEqual(x.Denominator(),3,
  "denominator 3");

  Rational x1(1,2);
  AssertEqual(x1.Numerator(),1,
  "numerator 1");
  AssertEqual(x1.Denominator(),2,
  "denominator 2");

}

//Если numerator дроби равен нулю, то denominator должен быть равен 1.
void Infinite_exception(){
  Rational x(0,-3);
  AssertEqual(x.Numerator(),0,
  "numerator 0");
  AssertEqual(x.Denominator(),1,
  "denominator 1");

  Rational x1(0,5);

  AssertEqual(x1.Numerator(),0,
  "numerator 0");
  AssertEqual(x1.Denominator(),1,
  "denominator 1");



}


int main() {
  TestRunner runner;
  runner.RunTest(Default_construct,"Default_construct");
  runner.RunTest(Construct_with_paramether_pq,"Construct_with_paramether_pq");
  runner.RunTest(Fraction_is_negative,"Fraction_is_negative");
  runner.RunTest(Fraction_is_positive,"Fraction_is_positive");
  runner.RunTest(Infinite_exception,"Infinite_exception");

  // добавьте сюда свои тесты
  return 0;
}
