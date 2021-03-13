#include <iostream>
#include <string>
#include <deque>
using namespace std;


void Br(deque<string> &exp, char ops, int num, bool cond) {

    string str;
    str.push_back(' ');
    str.push_back(ops);
    str.push_back(' ');

    if (!cond) {
        exp.push_front("(");
        exp.push_back(str);
        exp.push_back(to_string(num));
        exp.push_back(")");
    } else {
        exp.push_back(str);
        exp.push_back(to_string(num));
    }
}

void Br_1(deque<string> &exp, char ops, int num, bool cond) {

    string str;
    str.push_back(' ');
    str.push_back(ops);
    str.push_back(' ');

    if (!cond) {
        exp.push_front("(");
        exp.push_back(")");
        exp.push_back(str);
        exp.push_back(to_string(num));
    } else {
        exp.push_back(str);
        exp.push_back(to_string(num));
    }
}

int Condition_First(){
        int first;
        cin >> first;

        int count;
        cin >> count;

        if (count == 0) {
            cout << first << endl;
            return 0;
        }

        deque<string> exp;
        exp.push_back("(" + to_string(first) + ")");

        for (int i = 1; i <= count; ++i) {

            char ops;
            int num;
            cin >> ops >> num;

            Br(exp, ops, num, i == count);

        }
        for (auto i : exp) {
            cout << i;
        }
        cout << "\n";
        return 0;

}




int Condition_Second(){
  int first;
  cin >> first;

  int count;
  cin >> count;

  if (count == 0) {
      cout << first << endl;
      return 0;
  }

  deque<string> exp;
  exp.push_back(to_string(first));

  char prev;

  for (int i = 1; i <= count; ++i) {

      char ops;
      int num;
      cin >> ops >> num;

      if (i == 1) {
          Br_1(exp, ops, num, true);
      } else if (prev == '-' || prev == '+') {

          if (ops == '*' || ops == '/') {
              Br_1(exp, ops, num, false); //i == count
          } else {
              Br_1(exp, ops, num, true);
          }
      } else {
          Br_1(exp, ops, num, true);
      }

      prev = ops;
  }

  for (auto i : exp) {
      cout << i;
  }
  cout << "\n";
  return 0;
}


int main() {
    //Condition_First();
    Condition_Second();
    return 0;
}
