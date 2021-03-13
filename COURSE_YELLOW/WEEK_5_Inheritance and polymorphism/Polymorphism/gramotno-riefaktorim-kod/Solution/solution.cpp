
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
