#include <iostream>
#include <string>
#include <vector>

using namespace std;

class Person {
public:
	Person(const string& name, const string& type)
		: type_(type),
		  name_(name) {}

	virtual void Walk(const string& destination) const {
		cout << type_ << " " << name_ << " walks to " << destination << endl;
	}

	string Type() const {
		return type_;
	}

	string Name() const {
		return name_;
	}

protected:
	const string type_;
	const string name_;
};

class Student : public Person {
public:
    Student(const string& name, const string& favourite_song)
		: Person(name, "Student"),
		  favourite_song_(favourite_song) {}

    void Learn() const {
        cout << "Student " << name_ << " learns" << endl;
    }

    void Walk(const string& destination) const override {
    	cout << type_ << " " << name_ << " walks to " << destination << endl;
    	SingSong();
    }

    void SingSong() const {
        cout << "Student " << name_ << " sings a song \"" << favourite_song_ << "\"" << endl;
    }

private:
    const string favourite_song_;
};


class Teacher : public Person {
public:
    Teacher(const string& name, const string& subject)
		: Person(name, "Teacher"),
		  subject_(subject) {}

    void Teach() const {
        cout << "Teacher " << name_ << " teaches " << subject_ << endl;
    }

private:
    const string subject_;
};


class Policeman : public Person {
public:
    Policeman(const string& name)
		: Person(name, "Policeman") {}

    void Check(const Person& t) const {
        cout << "Policeman " << name_ << " checks " << t.Type() << ". " << t.Type() << "'s name is " << t.Name() << endl;
    }

};


void VisitPlaces(const Person& person, const vector<string>& places) {
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
