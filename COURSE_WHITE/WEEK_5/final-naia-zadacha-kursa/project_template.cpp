// Реализуйте функции и методы классов и при необходимости добавьте свои
#include <iostream>
#include <map>
#include <string>
#include <vector>
#include <set>
#include <ostream>

using namespace std;

class Date {
public:
  int GetYear() const;
  int GetMonth() const;
  int GetDay() const;
};

bool operator<(const Date& lhs, const Date& rhs);

class Database {
public:
  void AddEvent(const Date& date, const string& event);
  bool DeleteEvent(const Date& date, const string& event);
  int  DeleteDate(const Date& date);

  /* ??? */ bool Find(const Date& date) const;
  
  void Print() const;
};
