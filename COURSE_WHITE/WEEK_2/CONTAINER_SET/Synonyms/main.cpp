#include <iostream>
#include <map>
#include <vector>
#include <string>
#include <set>
using namespace std;

void Add(map<string,set<string>> &data_base, string &word1, string &word2);
void Count(map<string,set<string>> &data_base,string &word1);
void Check(map<string,set<string>> &data_base,string &word1,string &word2);
int main()
{
    int Q = 0;
    cin >> Q;
    map<string,set<string>> data_base;
    string operation_code;
    string word1;
    string word2;
    for (int i = 0; i < Q; ++i) {
        cin >> operation_code;
        if (operation_code == "ADD"){
            cin >> word1>>word2;
            Add(data_base, word1, word2);
        }
        if (operation_code == "COUNT"){
            cin >> word1;
            Count(data_base, word1);
        }
        if (operation_code == "CHECK"){
            cin >> word1>>word2;
            Check(data_base, word1, word2);
        }

    }
    return 0;
}

void Add(map<string,set<string>> &data_base, string &word1, string &word2){
     data_base[word1].insert(word2);
     data_base[word2].insert(word1);
}
void Count(map<string,set<string>> &data_base,string &word1){
     int k = data_base[word1].size();
     cout<<k<<endl;
}
void Check(map<string,set<string>> &data_base,string &word1,string &word2){
     if(data_base.count(word1)>0){
        if(data_base[word1].count(word2)>0) cout<<"YES"<<endl;
        else cout <<"NO"<<endl;
     }
     else{
        cout<<"NO"<<endl;
     }
}

