#include<iostream>
#include<string>
#include<vector>
using namespace std;

/*
 *Напишите функцию MoveStrings, которая принимает два вектора строк, source и destination,
 *и дописывает все строки из первого вектора в конец второго.
 *После выполнения функции вектор source должен оказаться пустым.
*/

void MoveStrings(vector<string> &a,vector<string> &b);

int main()
{
    vector<string> source = {"a", "b", "c"};
    vector<string> destination = {"z"};
    MoveStrings(source, destination);
    for (auto i : destination) {
        cout << i << endl;
    }

    return 0;
}

void MoveStrings(vector<string> &a,vector<string> &b){
    for (auto i : a) {
        b.push_back(i);
    }
    a.clear();
}

void MoveStrings_proff(vector<string>& source, vector<string>& destination) {
  for (auto w : source) {
    destination.push_back(w);
  }
  source.clear();
}

