#include<iostream>
#include<string>
#include<vector>

using namespace std;
/*
 * Реализуйте функцию vector<int> Reversed(const vector<int>& v)
 * возвращающую копию вектора v
 * в которой числа переставлены в обратном порядке.
*/
//vector<int> Reversed(const vector<int>& v);
//int main(){

//    vector<int> numbers = {1, 5, 3, 4, 2};
//    v = Reversed(numbers);

//    for (auto i : v){

//        cout<< i<<endl;

//    }
//    return 0;
//}

vector<int> Reversed(const vector<int>& input)
{
    vector<int> result;
    for (int i = input.size() - 1; i >= 0; --i) {
        result.push_back(input[i]);
    }
    return result;
}
