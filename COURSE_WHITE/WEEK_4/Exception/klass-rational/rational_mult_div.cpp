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
    return {r1.Numerator()*r2.Numerator(), r1.Denominator()*r2.Denominator()};
}

Rational operator/ (const Rational &r1, const Rational &r2){
    return {r1.Numerator()*r2.Denominator(),r1.Denominator()*r2.Numerator()};
}

int main5() {
    {
        Rational a(2, 3);
        Rational b(4, 3);
        Rational c = a * b;
        bool equal = c == Rational(8, 9);
        if (!equal) {
            cout << "2/3 * 4/3 != 8/9" << endl;
            return 1;
        }
    }

    {
        Rational a(5, 4);
        Rational b(15, 8);
        Rational c = a / b;
        bool equal = c == Rational(2, 3);
        if (!equal) {
            cout << "5/4 / 15/8 != 2/3" << endl;
            return 2;
        }
    }

    cout << "OK" << endl;
    return 0;
}

