// sort algorithm example
#include <iostream>     // std::cout
#include <algorithm>    // std::sort
#include <vector>       // std::vector
#include <string>
#include <locale>
using namespace std;


/*
 * Условие
 * В стандартном потоке дана одна строка, состоящая из числа N и следующих за ним N строк S. Между собой число и строки разделены пробелом.
 * Отсортируйте строки S в лексикографическом порядке по возрастанию, игнорируя регистр букв, и выведите их в стандартный поток вывода.
*/
bool myfunction (const string &i, const string &j){
    string a =i;
    string b =j;
    for(auto &k:a){
        k = tolower(k);
    }
    for(auto &k: b){
        k = tolower(k);
    }
    return (a < b);
}

int main()
{
    int N  = 0;
    string Z;
    vector<string>A;
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

