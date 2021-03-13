#include <iostream>
#include <utility>
#include <algorithm>
#include <vector>
#include <string>

using namespace std;
template<typename RandomIt>


pair<RandomIt, RandomIt> FindStartsWith_first(RandomIt range_begin, RandomIt range_end, char prefix) {

   string lower(1, prefix);
   string upper(1, (++prefix));

   auto Low = lower_bound(range_begin, range_end, lower);
   auto Upper = lower_bound(range_begin, range_end, upper);

   return make_pair(Low, Upper);
}

bool stringComparator(const string &lhs, string rhs) {
    ++rhs.back();
    return (rhs > lhs.substr(0, rhs.length()));
  }



template<typename RandomIt>
pair<RandomIt, RandomIt> FindStartsWith(RandomIt range_begin, RandomIt range_end, const string &prefix) {

    auto itLow = lower_bound(range_begin, range_end, prefix);
    auto itUpper = lower_bound(range_begin, range_end, prefix, stringComparator);
    return make_pair(itLow, itUpper);
}



int main() {

 const vector<string> sorted_strings = {"moscow", "murmansk", "vologda"};

 const auto m_result =
     FindStartsWith_first(begin(sorted_strings), end(sorted_strings), 'm');
 for (auto it = m_result.first; it != m_result.second; ++it) {
   cout << *it << " ";
 }
 cout << endl;

 const auto p_result =
     FindStartsWith_first(begin(sorted_strings), end(sorted_strings), 'p');
 cout << (p_result.first - begin(sorted_strings)) << " " <<
     (p_result.second - begin(sorted_strings)) << endl;

 const auto z_result =
     FindStartsWith_first(begin(sorted_strings), end(sorted_strings), 'z');
 cout << (z_result.first - begin(sorted_strings)) << " " <<
     (z_result.second - begin(sorted_strings)) << endl;




  const vector<string> sorted_strings_1 = {"moscow", "motovilikha", "murmansk"};

  const auto mo_result =
      FindStartsWith(begin(sorted_strings_1), end(sorted_strings_1), "mo");
  for (auto it = mo_result.first; it != mo_result.second; ++it) {
    cout << *it << " ";
  }
  cout << endl;

  const auto mt_result =
      FindStartsWith(begin(sorted_strings_1), end(sorted_strings_1), "mt");
  cout << (mt_result.first - begin(sorted_strings_1)) << " " <<
      (mt_result.second - begin(sorted_strings_1)) << endl;

  const auto na_result =
      FindStartsWith(begin(sorted_strings_1), end(sorted_strings_1), "na");
  cout << (na_result.first - begin(sorted_strings_1)) << " " <<
      (na_result.second - begin(sorted_strings_1)) << endl;

  return 0;
}
