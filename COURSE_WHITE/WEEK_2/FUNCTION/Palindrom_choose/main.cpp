#include<iostream>
#include<string>
#include<vector>

using namespace std;
/*
 * называется PalindromFilter
 * возвращает vector<string>
 * принимает vector<string> words и int minLength и возвращает все строки
 * из вектора words, которые являются палиндромами и имеют длину не меньше minLength
*/

bool IsPalindrom_proff (string line);
vector<string> PalindromFilter (vector<string> words, int minLenght);


int main()
{
    vector<string> myV = { "abacaba", "aba","weew", "bro", "code" };

    int minLength;

    cin >> minLength;

    for (auto counter : PalindromFilter(myV, minLength)){

        cout << counter <<endl;
    }
        return 0;

}


bool IsPalindrom_proff(string s) {
    // Замечание: более правильным было бы использовать здесь тип size_t вместо int
    // О причинах Вы узнаете на Жёлтом поясе
    for (int i = 0; i < s.size() / 2; ++i) {
        if (s[i] != s[s.size() - i - 1]) {
            return false;
        }
    }
    return true;
}

vector<string> PalindromFilter (vector<string> words, int minLength){
    vector<string> words2;
    for (auto i:words){
        if(IsPalindrom_proff(i) == true && i.size()>= minLength){
            words2.push_back(i);
        }
    }
    return words2;
}


