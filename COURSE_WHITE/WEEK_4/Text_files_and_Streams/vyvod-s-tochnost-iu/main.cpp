#include <iostream>
#include <fstream>
#include <string>
#include <iomanip>

using namespace std;
/*
 * В файле input.txt записаны вещественные числа, по одному на строчку.
 * На стандартный вывод напечатайте эти числа в том же порядке, по одному на строке, но сделайте так,
 * чтобы у каждого из них было ровно три знака после десятичной точки.
*/

int main() {
    ifstream input("input.txt");
    double a;
    cout << fixed << setprecision(3);
    while (input >> a) {
        cout << a << endl;
    }
    return 0;
}
