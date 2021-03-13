// sort algorithm example
#include <iostream>     // std::cout
#include <algorithm>    // std::sort
#include <vector>       // std::vector
#include <cmath>
using namespace std;

/*
 * Условие
 * В стандартном потоке дана одна строка, состоящая из N + 1 целых чисел.
 * Первым числом идёт само число N. Далее следуют ещё N чисел, обозначим их за массив A.
 * Между собой числа разделены пробелом.
 * Отсортируйте массив А по модулю и выведите его в стандартный поток.
*/

bool myfunction (int i,int j){
    return (abs(i)<abs(j));
}

int main(){
    int N  = 0;
    int Z = 0;
    vector<int>A;
    cin>>N;
    for(int i =0; i<N; i++){
        cin>>Z;
        A.push_back(Z);
    }

    sort(A.begin(),A.end(),myfunction);

    for (const auto &i:A){
        cout<< i<<' ';
    }
    return 0;
}

