#include <iostream>
#include <string>
using namespace std;

//структуры Specialization, Course, Week
struct Specialization {
    explicit Specialization(const string & name){value =name;}
    string value;
};
struct Course {
    explicit Course(const string & name){value =name;}
    string value;

};
struct Week {
    explicit Week(const string & name){value =name;}
    string value;

};

struct LectureTitle {
    LectureTitle(const Specialization &num1, const Course &num2,const  Week  &num3){
        specialization = num1.value;
        course = num2.value;
        week = num3.value;
    }
    string specialization;
    string course;
    string week;
};


