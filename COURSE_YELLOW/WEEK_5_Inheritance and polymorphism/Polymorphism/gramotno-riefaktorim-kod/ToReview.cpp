#include <iostream>
#include <string>
#include <vector>

using namespace std;

class Human {
public:
    Human(const string& name, const string& type) : 
        Name(name),
        Type(type)
    {

    }
    const string& GetName() const {return Name;}
    const string& GetType() const {return Type;}
    virtual void Walk(const string& destination) const
    {
        cout << Type << ": " << Name << " walks to: " << destination << endl;
    }
protected:
    const string Name;
    const string Type;
};

class Student: public Human {
public:

    Student(const string& name, const string& favouriteSong): 
        Human(name, "Student"),
        FavouriteSong(favouriteSong)
    {
    }

    void Learn() const {
        cout << "Student: " << Name << " learns" << endl;
    }

    void Walk(const string& destination) const override {
        Human::Walk(destination);
        SingSong();
    }

    void SingSong() const {
        cout << "Student: " << Name << " sings a song: " << FavouriteSong << endl;
    }
    
    const string& GetFavouriteSong() const { return FavouriteSong;}

private:
    string FavouriteSong;
};


class Teacher : public Human {
public:

    Teacher(const string& name, const string& subject) :
        Human(name, "Teacher"),
        Subject(subject)
    {
    }

    void Teach() const {
        cout << "Teacher: " << Name << " teaches: " << Subject << endl;
    }
    const string& GetSubject() const { return Subject;}


private:
    string Subject;
};


class Policeman : public Human{
public:
    Policeman(const string& name) :
        Human(name, "Policeman")
    {
    }

    void Check(const Human &h) const {
        cout << "Policeman: " << Name << " checks " << h.GetType() << ". " << h.GetType() << "'s name is: " << h.GetName() << endl;
    }

};

void VisitPlaces(const Human& person, const vector<string>& places) {
	for (const auto& p : places) {
		person.Walk(p);
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
