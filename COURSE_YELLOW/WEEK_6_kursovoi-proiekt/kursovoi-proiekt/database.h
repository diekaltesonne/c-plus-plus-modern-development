#pragma once

#include <date.h>
#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <set>
#include <memory>
#include <algorithm>
#include <iterator>
#include <ostream>
using namespace std;

class Database {
public:
  void Add(const Date &date, const string &event);
  void Print(ostream &stream) const;

  template<class Func>
  int RemoveIf(Func predicate){

      int count = 0;
      auto iter = storage.begin();
      while (iter != storage.end()) {

          auto it = stable_partition(iter->second.begin(), iter->second.end(),
                                              [&](const string str) { return !predicate(iter->first, str); });
          if (it != iter->second.end()) {
                count += distance(it, iter->second.end());
                iter->second.erase(it, iter->second.end());
                storage_Set[iter->first].clear();
                storage_Set[iter->first].insert(iter->second.begin(), iter->second.end());
          };
          if (iter->second.empty()) {
              storage_Set.erase(iter->first);
              iter = storage.erase(iter);
            } else {
                ++iter;
            }
        }
        return count;
  }

  template<class Func>
  vector<pair<Date, string>> FindIf(Func predicate) const {
  \
      vector<pair<Date, string>> Finders;
      auto iter = storage.begin();
      while (iter != storage.end()){
          auto it = iter->second.begin();
          while (it != iter->second.end()){

              it = find_if(it, iter->second.end(),
                                  [&](const string str) { return predicate(iter->first, str); });

              if (it != iter->second.end()) {
                  Finders.emplace_back(iter->first, *it);
                  ++it;

              }
          }
          ++iter;
      }

      return Finders;
  }
  pair<Date, string> Last(const Date &date) const;
private:
  map<Date, vector<string>> storage;
  map<Date, set<string>> storage_Set;
};
ostream &operator << (ostream &stream, const pair<Date, string> &p);
