#include <iostream>
#include <cmath>
using namespace std;

int NOD_1(int n1, int n2)
{
  int div;
  if (n1 == n2)  return n1;
  int d = n1 - n2;
  if (d < 0) {
    d = -d;  div = NOD_1(n1, d);
  } else
    div = NOD_1(n2, d);
  return div;
}
// Наименьшее общее кратное
int NOK(int n1, int n2)
{
  return n1*n2 / NOD_1(n1, n2);
}

class Rational {
public:

    Rational(){
      num = 0;
      den = 1;

    }
    // Реализуйте конструктор по умолчанию

    Rational(int numerator, int denominator){
        if(numerator== 0){
            num = 0;
            den = 1;

        }
        else{
            int a = NOD_1(abs(numerator),abs(denominator));

            if(numerator < 0 && denominator<0){
                num = (-numerator)/a;
                den = (-denominator)/a;

            }
            if(numerator > 0 && denominator<0){
                num = (-numerator)/a;
                den = (-denominator)/a;


            }
            if(numerator < 0 && denominator>0){
                num = numerator/a;
                den = denominator/a;

            }
            if(numerator > 0 && denominator>0){
                num = numerator/a;
                den = denominator/a;

            }

        }
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


};


int main2() {

    {
        const Rational r(3, 10);
        if (r.Numerator() != 3 || r.Denominator() != 10) {
            cout << "Rational(3, 10) != 3/10" << endl;
            return 1;
        }
    }

    {
        const Rational r(8, 12);
        if (r.Numerator() != 2 || r.Denominator() != 3) {
            cout << "Rational(8, 12) != 2/3" << endl;
            return 2;
        }
    }

    {
        const Rational r(-4, 6);
        if (r.Numerator() != -2 || r.Denominator() != 3) {
            cout << "Rational(-4, 6) != -2/3" << endl;
            return 3;
        }
    }

    {
        const Rational r(4, -6);
        if (r.Numerator() != -2 || r.Denominator() != 3) {
            cout << "Rational(4, -6) != -2/3" << endl;
            return 3;
        }
    }

    {
        const Rational r(0, 15);
        if (r.Numerator() != 0 || r.Denominator() != 1) {
            cout << "Rational(0, 15) != 0/1" << endl;
            return 4;
        }
    }

    {
        const Rational defaultConstructed;
        if (defaultConstructed.Numerator() != 0 || defaultConstructed.Denominator() != 1) {
            cout << "Rational() != 0/1" << endl;
            return 5;
        }
    }

    cout << "OK" << endl;
    return 0;
}
