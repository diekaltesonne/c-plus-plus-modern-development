#include <iostream>
#include <string>
#include <vector>

using namespace std;

class Human
{
public:
	Human(const string& name, const string& classname) : Name(name), ClassName(classname){}

	virtual void Walk(const string& destination) const = 0;
	virtual void Check(const Human& h) const {};

	void Log() const;

	const string Name;
	const string ClassName;
};


class Student : public Human
{
public:

	Student(const string& name, const string& favouriteSong)
		: Human(name, "Student"), FavouriteSong(favouriteSong) {}

	void Learn() const
	{
		Log();
		cout << " learns" << endl;
	}

	void Walk(const string& destination) const override
	{
		Log();
		cout << " walks to: " << destination << endl;
		Log();
		cout << " sings a song: " << FavouriteSong << endl;
	}

	void SingSong() const
	{
		Log();
		cout << " sings a song: " << FavouriteSong << endl;
	}

private:
	string FavouriteSong;
};


class Teacher : public Human
{
public:

	Teacher(const string& name, const string& subject)
		: Human(name, "Teacher"), Subject(subject) {}


	void Teach() const
	{
		Log();
		cout << " teaches: " << Subject << endl;
	}

	void Walk(const string& destination) const override
	{
		Log();
		cout << " walks to: " << destination << endl;
	}

private:
	string Subject;
};


class Policeman  : public Human
{
public:
	Policeman(const string& name) : Human(name, "Policeman") {}

	void Check(const Human& h) const override
	{
		Log();
		cout << " checks " << h.ClassName << ". " << h.ClassName << "'s name is: " << h.Name << endl;
	}

	void Walk(const string& destination) const override
	{
		Log();
		cout << " walks to: " << destination << endl;
	}

};


void VisitPlaces(Human& h, vector<string> places)
{
	for (auto p : places)
	{
		h.Walk(p);
	}
}

void Human::Log() const
{
	cout << ClassName << ": " << Name;
}

int main() 
{
	Teacher t("Jim", "Math");
	Student s("Ann", "We will rock you");
	Policeman p("Bob");

	VisitPlaces(t, { "Moscow", "London" });
	p.Check(s);
	VisitPlaces(s, { "Moscow", "London" });
	return 0;
}
