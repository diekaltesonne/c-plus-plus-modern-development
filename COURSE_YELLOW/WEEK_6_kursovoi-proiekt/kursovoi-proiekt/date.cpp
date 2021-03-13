#include <date.h>

using namespace std;

int Date::GetYear() const {
    return year;
}

int Date::GetMonth() const {
    return month;
}

int Date::GetDay() const {
    return day;
}


Date ParseDate(istream& is){
     int year;
     is >> year;

     is.ignore();

     int month;
     is >> month;
     is.ignore();

     int day;
     is >> day;

     return {year, month, day};

 /*
  if (!ok) {
    throw logic_error("Wrong date format: " + date);
  }
  return Date(year, month, day);
*/
}

bool operator < (const Date& lhs, const Date& rhs) {
  return make_tuple(lhs.GetYear(), lhs.GetMonth(), lhs.GetDay()) <
      make_tuple(rhs.GetYear(), rhs.GetMonth(), rhs.GetDay());
}
bool operator <= (const Date& lhs, const Date& rhs) {

    return make_tuple(lhs.GetYear(), lhs.GetMonth(), lhs.GetDay())<=
        make_tuple(rhs.GetYear(), rhs.GetMonth(), rhs.GetDay());
}
bool operator > (const Date& lhs, const Date& rhs) {
    return make_tuple(lhs.GetYear(), lhs.GetMonth(), lhs.GetDay()) >
        make_tuple(rhs.GetYear(), rhs.GetMonth(), rhs.GetDay());

}

bool operator >= (const Date& lhs, const Date& rhs) {

    return make_tuple(lhs.GetYear(), lhs.GetMonth(), lhs.GetDay())>=
        make_tuple(rhs.GetYear(), rhs.GetMonth(), rhs.GetDay());
}

bool operator == (const Date& lhs, const Date& rhs) {

  return make_tuple(lhs.GetYear(), lhs.GetMonth(), lhs.GetDay()) ==
      make_tuple(rhs.GetYear(), rhs.GetMonth(), rhs.GetDay());
}

bool operator != (const Date& lhs, const Date& rhs) {

  return make_tuple(lhs.GetYear(), lhs.GetMonth(), lhs.GetDay()) !=
     make_tuple(rhs.GetYear(), rhs.GetMonth(), rhs.GetDay());
}

// даты будут по умолчанию выводиться в нужном формате
ostream& operator<<(ostream& stream, const Date& date) {

  stream << setw(4) << setfill('0') << date.GetYear() <<
      "-" << setw(2) << setfill('0') << date.GetMonth() <<
      "-" << setw(2) << setfill('0') << date.GetDay();

  return stream;
}
