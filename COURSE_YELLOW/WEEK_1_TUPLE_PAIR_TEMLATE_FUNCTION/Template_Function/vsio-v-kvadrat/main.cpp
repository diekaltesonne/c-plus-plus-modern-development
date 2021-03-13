#include <iostream>
#include <vector>
#include <map>
#include <utility>

using namespace std;

// Предварительное объявление шаблонных функций
template <typename First , typename Second >
pair <First , Second> operator * (const pair <First , Second >& p1,
const pair <First , Second >& p2);
template <typename T>
vector <T> operator * (const vector <T>& p1,
const vector <T>& p2);
template <typename KEY , typename VALUE >
map <KEY , VALUE > operator * (const map <KEY , VALUE > &p1,
const map <KEY , VALUE > &p2);
template <typename T>
T Sqr(T x);



int main(){
    // Пример вызова функции
    vector<int> v = {1, 2, 3};
    cout << "vector:";
    for (int x : Sqr(v)) {
      cout << ' ' << x;
    }
    cout << endl;

    map<int, pair<int, int>> map_of_pairs = {
      {4, {2, 2}},
      {7, {4, 3}}
    };
    cout << "map of pairs:" << endl;
    for (const auto& x : Sqr(map_of_pairs)) {
      cout << x.first << ' ' << x.second.first << ' ' << x.second.second << endl;
    }
    return 0;

}

template <typename First , typename Second >
pair <First , Second> operator * (const pair <First , Second >& p1 ,
const pair <First , Second >& p2){
First f = p1.first * p2.first;
Second s = p1.second * p2.second;
return {f, s};
}

template <typename T>
vector <T> operator * (const vector <T>& p1,
const vector <T>& p2){
    vector<T> ans;

    for(size_t i = 0; i <p1.size(); i++){
    ans.push_back(p1[i]*p2[i]);
    }
    return ans;
}

template <typename KEY , typename VALUE >
map <KEY , VALUE > operator * (const map <KEY , VALUE > &p1,
const map <KEY , VALUE > &p2){
    map <KEY , VALUE >ans;
    for(auto i : p1){
        ans[i.first] = i.second * p2.at(i.first);
    }
    return ans;
}

template <typename T>
T Sqr(T x) {
    return x * x;
}
