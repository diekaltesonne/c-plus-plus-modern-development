#ifndef CONCURRENTMAP
#define CONCURRENTMAP
#pragma once
#include <algorithm>
#include <numeric>
#include <vector>
#include <string>
#include <random>
#include <future>
#include <map>

using namespace std;
template <typename K, typename V>
class ConcurrentMap {
    struct Segment {
        map<K, V> submap;
        mutex m;
    };
    vector<Segment> segments;
    size_t segment(K key) {
        K abs = key >= 0 ? key : -key;
        return abs % segments.size();
    }
public:
  static_assert(is_integral_v<K>, "ConcurrentMap supports only integer keys");
  explicit ConcurrentMap(size_t bucket_count): segments(bucket_count){}

  struct Access {
    lock_guard<mutex> guard;
    V& ref_to_value;
    //unique_lock<mutex>&& lock;
    //lock_guard<mutex> guard;
  };

  Access operator[](const K& key){
      auto &s = segments[segment(key)];
      //unique_lock<mutex> lock(s.m);
      return {lock_guard(s.m),s.submap[key]};
  }

  map<K, V> BuildOrdinaryMap(){
      vector<unique_lock<mutex>> locks;
      for (auto &s : segments) {
          locks.emplace_back(unique_lock<mutex>(s.m));
      }
      map<K, V> res;
      for (auto &s : segments) {
          for (auto&[k, v] : s.submap){
              res[k] = v;
          }
      }
      return res;
  }
};

void RunConcurrentUpdates(ConcurrentMap<int, int>& cm, size_t thread_count, int key_count);

#endif // CONCURRENTMAP

