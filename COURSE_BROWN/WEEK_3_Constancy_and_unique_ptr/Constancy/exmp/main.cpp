#include <iostream>
#include <string>
#include <map>
using namespace std;

int main()
{
    map<string, string> cont;
    // ...
    map<string, string>::const_iterator it = cont.begin();
    const string& key = it->first;
    const string& value = it->second;

}

