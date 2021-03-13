/*
#include <iostream>
#include <string>
#include <vector>

using namespace std;


class Student {
public:

    Student(string name, string favouriteSong) {
        Name = name;
        FavouriteSong = favouriteSong;
    }

    void Learn() {
        cout << "Student: " << Name << " learns" << endl;
    }

    void Walk(string destination) {
        cout << "Student: " << Name << " walks to: " << destination << endl;
        cout << "Student: " << Name << " sings a song: " << FavouriteSong << endl;
    }

    void SingSong() {
        cout << "Student: " << Name << " sings a song: " << FavouriteSong << endl;
    }

public:
    string Name;
    string FavouriteSong;
};


class Teacher {
public:

    Teacher(string name, string subject) {
        Name = name;
        Subject = subject;
    }

    void Teach() {
        cout << "Teacher: " << Name << " teaches: " << Subject << endl;
    }

    void Walk(string destination) {
        cout << "Teacher: " << Name << " walks to: " << destination << endl;
    }

public:
    string Name;
    string Subject;
};


class Policeman {
public:
    Policeman(string name) {
        Name = name;
    }

    void Check(Teacher t) {
        cout << "Policeman: " << Name << " checks Teacher. Teacher's name is: " << t.Name << endl;
    }

    void Check(Student s) {
        cout << "Policeman: " << Name << " checks Student. Student's name is: " << s.Name << endl;
    }

    void Check(Policeman p) {
        cout << "Policeman: " << Name << " checks Policeman. Policeman's name is: " << p.Name << endl;
    }

    void Walk(string destination) {
        cout << "Policeman: " << Name << " walks to: " << destination << endl;
    }

public:
    string Name;
};


void VisitPlaces(Teacher t, vector<string> places) {
    for (auto p : places) {
        t.Walk(p);
    }
}

void VisitPlaces(Student s, vector<string> places) {
    for (auto p : places) {
        s.Walk(p);
    }
}

void VisitPlaces(Policeman pol, vector<string> places) {
    for (auto p : places) {
        pol.Walk(p);
    }
}
*/
/*

#include <iostream>
#include <string>
#include <vector>


using namespace std;

class People{
public:
    People(const string &name,const string & proffesion):Name(name),Proffesion(proffesion){
    }
    virtual void Walk(const string &destination)const{
        cout << Proffesion+": " << Name << " walks to: " << destination << endl;
    }

public:
    const string Name;
    const string Proffesion;

};

class Student: public People {
public:
    Student(const string &name, const string &favouriteSong):People(name,"Student"),FavouriteSong(favouriteSong){
    }

    void Learn() {
        cout << "Student: " << Name << " learns" << endl;
    }

    void Walk(const string &destination) const override {
        cout << "Student: " << Name << " walks to: " << destination << endl;
        cout << "Student: " << Name << " sings a song: " << FavouriteSong << endl;
    }

    void SingSong() {
        cout << "Student: " << Name << " sings a song: " << FavouriteSong << endl;
    }

public:
    const string FavouriteSong;
};


class Teacher: public People {
public:
    Teacher(const string &name, const string &subject):People(name,"Teacher"),Subject(subject){}
    void Teach() {
        cout << "Teacher: " << Name << " teaches: " << Subject << endl;
    }
public:
    const string Subject;
};


class Policeman: public People {
public:
    Policeman(const string &name):People(name,"Policeman"){}

    template <typename Man>
    void Check(Man t){
        string spec = " checks "+t.Proffesion+". "+t.Proffesion+"'s name is: ";
        cout << "Policeman: " << Name << spec << t.Name << endl;
    }
};

template <typename Man>
void VisitPlaces(Man t, vector<string> places){
    for (auto p : places) {
        t.Walk(p);
    }
}

int main() {
    Teacher t("Jim", "Math");
    Student s("Ann", "We will rock you");
    Policeman p("Bob");
    VisitPlaces(t, {"Moscow", "London"});
    p.Check(s);
    VisitPlaces(s, {"Moscow", "London"});
    return 0;
}
*/
