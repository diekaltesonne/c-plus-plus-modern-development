#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
using namespace std;
//Реализуйте класс, поддерживающий набор строк в отсортированном порядке.
//Класс должен содержать два публичных метода:
class SortedStrings_proff {
public:
  void AddString(const string& s) {
    data.push_back(s);
  }
  vector<string> GetSortedStrings() {
    sort(begin(data), end(data));
    return data;
  }
private:
  vector<string> data;
};



class SortedStrings {
public:
  void AddString(const string& s) {
    str.push_back(s);
  }
  vector<string> GetSortedStrings() {
      sort(str.begin(),str.end());
      return str;
    // получить набор из всех добавленных строк в отсортированном порядке
  }
private:
  vector<string> str;
};

void PrintSortedStrings(SortedStrings& strings) {
  for (const string& s : strings.GetSortedStrings()) {
    cout << s << " ";
  }
  cout << endl;
}

int main()
{
    SortedStrings strings;
      strings.AddString("first");
      strings.AddString("third");
      strings.AddString("second");
      PrintSortedStrings(strings);

      strings.AddString("second");
      PrintSortedStrings(strings);

      return 0;
}

