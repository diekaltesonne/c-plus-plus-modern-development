#include <iostream>
#include <fstream>
#include <string>
using namespace std;

int main() {
  ifstream f("input.txt");
  //ofstream of("output.txt");
  string s;
  while(getline(f, s))
  {
      cout << s << endl;
  }
  return 0;
}

