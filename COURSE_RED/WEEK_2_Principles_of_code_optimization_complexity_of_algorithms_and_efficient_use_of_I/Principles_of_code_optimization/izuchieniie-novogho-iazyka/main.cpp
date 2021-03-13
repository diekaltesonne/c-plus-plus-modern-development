#include <iostream>
#include <algorithm>
#include <string>
#include <vector>
#include <set>
#include "profile.h"
#include <sstream>

using namespace std;
class Learner {
 private:
  vector<string> dict;

  set<string> dict_spec;
  size_t size = 0;
 public://dict_spec.insert(words.begin(),words.end())
    int Learn(const vector<string>& words) {
      size = dict_spec.size();
      dict_spec.insert(words.begin(),words.end());
      return (dict_spec.size()-size);
    }
  vector<string> KnownWords(){
    dict.insert(dict.begin(),dict_spec.begin(),dict_spec.end());
    return dict;
  }
};


int main() {
  Learner learner;
  string line;
  int i =0;
  while (i<5){
    getline(cin, line);
    vector<string> words;
    stringstream ss(line);
    string word;
    while (ss >> word) {
      words.push_back(word);
    }
    {
        LOG_DURATION("MAIN");
        cout << learner.Learn(words) << "\n";
    }
    i++;
  }

  cout << "=== known words ===\n";

  for (auto word : learner.KnownWords()) {
    LOG_DURATION("MAIN_2")
    cout << word << "\n";
  }
}
