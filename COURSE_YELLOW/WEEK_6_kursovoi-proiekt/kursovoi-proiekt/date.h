#pragma  once
#include <stdexcept>
#include <sstream>
#include <string>

#include <iostream>
#include <iomanip>
#include <vector>
#include <tuple>
using namespace std;

class Date {
public:
  // конструктор выбрасывает исключение, если его аргументы некорректны
  Date(int new_year, int new_month, int new_day) {
    year = new_year;
    if (new_month > 12 || new_month < 1) {
      throw logic_error("Month value is invalid: " + to_string(new_month));
    }
    month = new_month;
    if (new_day > 31 || new_day < 1) {
      throw logic_error("Day value is invalid: " + to_string(new_day));
    }
    day = new_day;
  }
  int GetYear() const;
  int GetMonth() const;
  int GetDay() const;
private:
   int year;
   int month;
   int day;
};

bool operator < (const Date& lhs, const Date& rhs);
bool operator <= (const Date& lhs, const Date& rhs);
bool operator > (const Date& lhs, const Date& rhs);
bool operator >= (const Date& lhs, const Date& rhs);
bool operator == (const Date& lhs, const Date& rhs);
bool operator != (const Date& lhs, const Date& rhs);

ostream& operator << (ostream& stream, const Date& date);
Date ParseDate(istream& is);
