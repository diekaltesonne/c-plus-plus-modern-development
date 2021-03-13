#include <iostream>
using namespace std;
/*
 *Напишите функцию UpdateIfGreater, которая принимает два целочисленных аргумента: first и second.
 *Если first оказался больше second, Ваша функция должна записывать в second значение параметра first.
 * При этом указанная функция не должна ничего возвращать, а изменение параметра second должно быть видно на вызывающей стороне.
 */

//void UpdateIfgreater(int & a, int& b );
int main()
{
    return 0;
}

void UpdateIfGreater(int a, int& b) {
    if (a > b) {
        b = a;
    }
}


