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

class Person{
public:
  void ChangeFirstName(int year, const string& first_name) {
      fnames_of_person[year] = first_name;
      // добавить факт изменения имени на first_name в год year
  }
  void ChangeLastName(int year, const string& last_name) {
      lnames_of_person[year] =last_name;
  }
  string GetFullName(int year) {

      int a = sorted(fnames_of_person,year);
      int b = sorted(lnames_of_person,year);

      if(a==0&&b==0){
          return "Incognito";
      }
      if(a==0&&b!=0){
        return  lnames_of_person[b] + " with unknown first name";
      }
      else if(a!=0&&b==0){
        return  fnames_of_person[a] +" with unknown last name";
      }
      else{
        return fnames_of_person[a]+" "+lnames_of_person[b];
      }
      return "Наебнулось";

  }
private:

    int sorted(map<int,string> &sort,int&year){
        int k = 0;
        for(auto i:sort){
            if(i.first <=year){
                if(i.first >= k){
                    k = i.first;
                }
            }
        }
        return k;
    }

    map<int,string> fnames_of_person;
    map<int,string> lnames_of_person;
  // приватные поля
};

void first_name_with_last_name_response() {
  Person person;
  person.ChangeFirstName(1965, "Polina");
  person.ChangeLastName(1967, "Sergeeva");

  AssertEqual(person.GetFullName(1990),"Polina Sergeeva",
  	"first_name_with_last_name_response");

  person.ChangeFirstName(1970, "Appolinaria");

  AssertEqual(person.GetFullName(1969),"Polina Sergeeva",
    	"first_name_with_last_name_response");

  AssertEqual(person.GetFullName(1970),"Appolinaria Sergeeva",
      "first_name_with_last_name_response");
}

void first_name_with_unknown_last_name_response() {
  Person person;

  person.ChangeFirstName(1965, "Polina");

  AssertEqual(person.GetFullName(1965),"Polina with unknown last name",
  	"first_name_with_unknown_last_name");

}

void last_name_with_unknown_first_name_response() {
  Person person;
  person.ChangeLastName(1967, "Sergeeva");
  AssertEqual(person.GetFullName(1969),"Sergeeva with unknown first name",
  	"last_name_with_unknown_first_name");
}

void Incognito_response () {
   Person person;
   person.ChangeFirstName(1965, "Polina");
   person.ChangeLastName(1967, "Sergeeva");

   AssertEqual(person.GetFullName(1900),"Incognito",
  	"Incognito_before_naming");
}


int main() {


  TestRunner runner;

  runner.RunTest(first_name_with_last_name_response, "first_name_with_last_name_response");
  runner.RunTest(first_name_with_unknown_last_name_response, "first_name_with_unknown_last_name_response");
  runner.RunTest(last_name_with_unknown_first_name_response, "last_name_with_unknown_first_name_response");
  runner.RunTest(Incognito_response, "Incognito_response");
  return 0;
}
