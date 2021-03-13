#include <iostream>
#include <vector>
#include <memory>
#include <string>
#include <cmath>
#include <sstream>
#include <iomanip>

using namespace std;


double getPi() {
    return 3.14;
}


class Figure {
public:
    Figure(const string &name) : name_(name) {};

    virtual string Name() = 0;

    virtual double Perimeter() = 0;

    virtual double Area() = 0;

protected:
    const string name_;
};


class Rect : public Figure {
public:
    Rect(const int width, const int height)
            : Figure("RECT"), width_(width), height_(height) {};

    virtual string Name() { return name_; }

    virtual double Perimeter() { return 2.0 * (width_ + height_); }

    virtual double Area() { return width_ * height_ * 1.0; }
    //free line
private:
    const int width_;
    const int height_;
};

class Triangle : public Figure {
public:
    Triangle(const int a, const int b, const int c)
            : Figure("TRIANGLE"), a_(a), b_(b), c_(c) {};

    virtual string Name() { return name_; }

    virtual double Perimeter() { return 1.0 * (a_ + b_ + c_); }

    virtual double Area() {
        double p = this->Perimeter() / 2;
        return sqrt(p * (p - a_) * (p - b_) * (p - c_));
    }
    //free line
private:
    const int a_;
    const int b_;
    const int c_;
};

class Circle : public Figure {
public:
    Circle(int radius)
            : Figure("CIRCLE"), radius_(radius) {};

    virtual string Name() { return name_; }

    virtual double Perimeter() { return 2 * getPi() * radius_; }

    virtual double Area() { return getPi() * radius_ * radius_; }
    //free line
private:
    const int radius_;
};

shared_ptr<Figure> CreateFigure(istringstream &stream) {
    string figure;
    stream >> figure;

    if (figure == "RECT") {

        int a, b;
        stream >> a >> b;
        return make_shared<Rect>(a, b);

    } else if (figure == "TRIANGLE") {

        int a, b, c;
        stream >> a >> b >> c;
        return make_shared<Triangle>(a, b, c);

    } else {

        int r;
        stream >> r;
        return make_shared<Circle>(r);

    }
}




int main() {
  
  vector<shared_ptr<Figure>> figures;
  for (string line; getline(cin, line); ) {
    istringstream is(line);
    string command;
    is >> command;
    if (command == "ADD") {
      figures.push_back(CreateFigure(is));
    } else if (command == "PRINT") {
      for (const auto& current_figure : figures) {
        cout << fixed << setprecision(3)
             << current_figure->Name() << " "
             << current_figure->Perimeter() << " "
             << current_figure->Area() << endl;
      }
    }
  }
  return 0;
}
