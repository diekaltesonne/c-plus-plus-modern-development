#include<iostream>
#include<string>
#include<vector>
using namespace std;

/*
 * Реализуйте функцию void Reverse(vector<int>& v),
 * которая переставляет элементы вектора в обратном порядке..
*/


void Reverse(vector<int>& v);

int main()
{

    vector<int> numbers = {1, 5, 3, 4, 2};
    Reverse(numbers);

    for (auto i : numbers){

        cout<< i<<endl;

    }
    return 0;
}

void Reverse(vector<int>& P){
    int k =P.size();
    vector<int> L;
    for(unsigned int  i = 0; i < k; i++){
        L.push_back(P[k-i -1]);
    }
    P = L;

}

void Reverse_proff(vector<int>& v) {
  int n = v.size();  // для удобства сохраним размер вектора в переменную n
  for (int i = 0; i < n / 2; ++i) {
    // элемент с индексом i симметричен элементу с индексом n - 1 - i
    // поменяем их местами с помощью временной переменной tmp
    int tmp = v[i];
    v[i] = v[n - 1 - i];
    v[n - 1 - i] = tmp;
  }
}
