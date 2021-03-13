#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
using namespace std;
vector<string> SplitIntoWords(string &s);


int main() {
  string s = "C Cpp Java Python";

  vector<string> words = SplitIntoWords(s);
  cout << words.size() << " ";
  for (auto it = begin(words); it != end(words); ++it) {
    if (it != begin(words)) {
      cout << "/";
    }
    cout << *it;
  }
  cout << endl;
  return 0;

}


vector<string>SplitIntoWords(string &s){
    vector<string> result;
    auto it_1 = s.begin();
    while (it_1!=s.end()) {
        auto it_2 = find(it_1, s.end(), ' ');
        result.push_back({it_1, it_2});
        if (it_2 != s.end()) {
            it_1 = it_2 + 1;
        } else {
            it_1 = it_2;
        }
    }
    return result;
}
