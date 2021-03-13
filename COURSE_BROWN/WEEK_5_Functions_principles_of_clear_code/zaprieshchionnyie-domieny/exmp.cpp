
#include <algorithm>
#include <iostream>
#include <string>
#include <string_view>
#include <vector>
#include <set>

using namespace std;

bool isGoodDomain(const set<string>&, const string&);

void ReadBannedDomains(set<string>& _banned) {
    std::string input;
    size_t count;
    getline(cin, input);
    count = stoi(input);
    for (size_t i = 0; i < count; i++) {
        string domain;
        getline(cin, domain);
        if (isGoodDomain(_banned, domain)) {
            _banned.insert(domain);
        }
    }
}

bool isGoodDomain(const set<string>& _banned, const string& _domain) {
    if (_banned.empty())
        return true;
    size_t i = _domain.length()-1;
    size_t point_pos;
    bool result = false;
    while (i > 0) {
        point_pos = _domain.rfind('.', i);
        if (point_pos != string::npos) {
            if (_banned.find(_domain.substr(point_pos+1)) != _banned.end())
                return result;
            i = point_pos-1;
        } else {
            if (_banned.find(_domain) != _banned.end())
                return result;
            i = 0;
        }
    }
    result = true;
    return result;
}

int main() {
  set<string> banned_domains;
  ReadBannedDomains(banned_domains);

//  std::string input;
//  size_t count;
//  getline(cin, input);
//  count = stoi(input);

//  //vector<string> domains;
//  for (size_t i = 0; i < count; ++i) {
//    string domain;
//    cin >> domain;
//    if (isGoodDomain(banned_domains, domain)) {
//        cout << "Good" << endl;
//    } else {
//        cout << "Bad" << endl;
//    }
//  }
//  return 0;
}
