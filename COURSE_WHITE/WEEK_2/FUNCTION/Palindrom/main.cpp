#include <iostream>
#include <string>
#include <algorithm>
using namespace std;
/*
 * называется IsPalindrom
 * возвращает bool
 * принимает параметр типа string и возвращает, является ли переданная строка палиндромом
 * Палиндром - это слово или фраза, которые одинаково читаются слева направо и справа налево. Пустая строка является палиндромом.
*/

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


bool IsPalindrom(string P){

   unsigned int k = 0;
    for(unsigned int  i = 0; i<P.size(); i++){
        //cout<<P[i]<<" "<< P[P.size()-i -1]<<endl; проверка
        if(P[i] == P[P.size()-i-1]){
            k ++;
        }
    }

    if(k == P.size())return true;
    return false;

}

int main()
{

    return 0;
}

