#include<iostream>
#include<map>
#include<vector>
using namespace std;

/*
 * Слова называются анаграммами друг друга,
 * если одно из них можно получить перестановкой букв в другом. Например, слово «eat» можно получить перестановкой букв слова «tea», поэтому эти слова являются анаграммами друг друга. Даны пары слов, проверьте для каждой из них, являются ли слова этой пары анаграммами друг друга.
 * Указание
 * Один из способов проверки того, являются ли слова анаграммами друг друга, заключается в следующем.
 * Для каждого слова с помощью словаря подсчитаем, сколько раз в нём встречается каждая буква.
 * Если для обоих слов эти словари равны (а это проверяется с помощью обычного оператора ==),
 * то слова являются анаграммами друг друга, в противном случае не являются.
 * При этом построение такого словаря по слову удобно вынести в отдельную функцию BuildCharCounters.
 *
 * Формат ввода
 * Сначала дано число пар слов N, затем в N строках содержатся пары слов, которые необходимо проверить.
 * Гарантируется, что все слова состоят лишь из строчных латинских букв.
 *
 * Формат вывода
 * Выведите N строк: для каждой введённой пары слов YES, если эти слова являются анаграммами, и NO в противном случае.
*/

string BuildCharCounters(const string &word1, const string &word2);

int main(){
    int N;
    string word1, word2;
    vector<string> Answer;
    cin >> N;

    for(int i = 0; i<N; i++ ){
        cin>>word1>>word2;
        Answer.push_back(BuildCharCounters(word1,word2));

    }

    for(string &i : Answer ){

        cout<<i<<endl;
    }

    return 0;
}

string BuildCharCounters(const string &word1, const string &word2 ){
    map<char,int> counter;
    map<char,int> counter1;

    for (const char &i : word1){
       if (counter.count(i) == 0){
            counter[i] = 1;
       }
       else{
           ++counter[i];
       }
    }

    for (const char &i : word2){
       if (counter1.count(i) == 0){
            counter1[i] = 1;
       }
       else{
           ++counter1[i];
       }
    }

    if(counter == counter1){
        return "YES";
    }
    else{
        return "NO";
    }

}
