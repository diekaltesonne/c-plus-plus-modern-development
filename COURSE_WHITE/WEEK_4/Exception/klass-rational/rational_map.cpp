#include <iostream>
#include <cmath>
#include <sstream>
#include <vector>
#include <map>
#include <set>
#include <string>
using namespace std;

class Rational {
public:

    Rational(){
      num = 0;
      den = 1;

    }
    // Реализуйте конструктор по умолчанию

    Rational(int numerator, int denominator) {
        if(numerator== 0){
            num = 0;
            den = 1;

        }
        else{
            if(numerator<0 && denominator<0){
                num = abs(numerator) ;
                den = abs(denominator);

            }
            if(numerator >0 && denominator<0){
                num = - numerator;
                den = abs(denominator);

            }
            if(numerator <0 && denominator>0){
                num = numerator;
                den = abs(denominator);

            }
            if(numerator >0 && denominator>0){
                num = numerator;
                den = denominator;

            }

        }

        NOD_spec();
        // Реализуйте конструктор
    }

    int Numerator() const {
        return num;
        // Реализуйте этот метод
    }

    int Denominator() const {
        return den;
        // Реализуйте этот метод
    }
private:
    // Добавьте поля
    int num = 0 ;
    int den = 1;

    void NOD_spec(){
        int a = num;
        int b = den;
        //cout<< a<<" "<<b<<endl;
        while(a > 0 && b > 0){
                if(a > b)
                    a %= b;

                else
                    b %= a;
        }
        //cout<< (a+b);
        num = num/(a+b);
        den = den/(a+b);

    }
};

int NOD(int n1, int n2)
{
  int div;
  if (n1 == n2)  return n1;
  int d = n1 - n2;
  if (d < 0) {
    d = -d;  div = NOD(n1, d);
  } else
    div = NOD(n2, d);
  return div;
}
// Наименьшее общее кратное
int NOK(int n1, int n2)
{
  return n1*n2 / NOD(n1, n2);
}

//Реализуйте для класса Rational операторы ==, + и - так, чтобы операции с дробями можно было
//Записывать естественным образом. Например, следующий код должен быть валидным:
bool operator== (const Rational &r1,const Rational &r2){
        return (r1.Numerator() == r2.Numerator())? true:false;


}

Rational operator+(const Rational &r1, const Rational &r2){
    int x = NOK(r1.Denominator(),r2.Denominator());
    int a = r1.Numerator()*(x/r1.Denominator())+r2.Numerator()*(x/r2.Denominator());
    return {a,x};
}

Rational operator-(const Rational &r1, const Rational &r2){
    int x = NOK(r1.Denominator(),r2.Denominator());
    int a = r1.Numerator()*(x/r1.Denominator())-r2.Numerator()*(x/r2.Denominator());
    return {a,x};
}

//Аналогично предыдущей части, реализуйте операторы * и /.
Rational operator* (const Rational &r1, const Rational &r2){
    return {r1.Numerator()*r2.Numerator(),r1.Denominator()*r2.Denominator()};
}

Rational operator/ (const Rational &r1, const Rational &r2){
    return {r1.Numerator()*r2.Denominator(),r1.Denominator()*r2.Numerator()};
}

//В этой части вам нужно реализовать операторы ввода и вывода для класса Rational.
ostream& operator<<(ostream& stream,const Rational &r1){
    stream << r1.Numerator()<<"/"<<r1.Denominator();
    return stream;
}
bool operator<(const Rational& r1, const Rational& r2){
     int x = NOK(r1.Denominator(),r2.Denominator());
     return (r1.Numerator()*(x/r1.Denominator()))<(r2.Numerator()*(x/r2.Denominator())) ;
}

istringstream& operator>> (istringstream& stream, Rational &r1){
    if (stream){
        int a =0;
        int b =0;
        stream >> a;
        stream.ignore(1);
        stream >> b;
        if(b==0)
            return stream;
        else
            r1 = {a,b};
    }
    return stream;

}

int main4() {
    {
        const set<Rational> rs = {{1, 2}, {1, 25}, {3, 4}, {3, 4}, {1, 2}};
        if (rs.size() != 3) {
            cout << "Wrong amount of items in the set" << endl;
            return 1;
        }

        vector<Rational> v;
        for (auto x : rs) {
            v.push_back(x);
        }
        if (v != vector<Rational>{{1, 25}, {1, 2}, {3, 4}}) {
            cout << "Rationals comparison works incorrectly" << endl;
            return 2;
        }
    }

    {
        map<Rational, int> count;
        ++count[{1, 2}];
        ++count[{1, 2}];

        ++count[{2, 3}];

        if (count.size() != 2) {
            cout << "Wrong amount of items in the map" << endl;
            return 3;
        }
    }

    cout << "OK" << endl;
    return 0;
}

