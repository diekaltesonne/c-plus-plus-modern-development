#include "test_runner.h"
#include "profile.h"
#include <functional>
#include <future>
#include <map>
#include <string>
#include <sstream>
#include <iterator>
#include <iostream>
using namespace std;

template <typename Iterator>
class IteratorRange {
public:
  IteratorRange(Iterator begin, Iterator end): first(begin) , last(end) , size_(distance(first, last)){}
  Iterator begin() const {
    return first;
  }
  Iterator end() const {
    return last;
  }
  size_t size() const {
    return size_;
  }

private:
  Iterator first, last;
  size_t size_;
};

template <typename Iterator>
class Paginator {
private:
  vector<IteratorRange<Iterator>> pages;
public:

  Paginator(Iterator begin, Iterator end, size_t page_size) {
    for (size_t left = distance(begin, end); left > 0; ) {
      size_t current_page_size = min(page_size, left);
      Iterator current_page_end = next(begin, current_page_size);
      pages.push_back({begin, current_page_end});
      left -= current_page_size;
      begin = current_page_end;
    }
  }

  auto begin() const {
    return pages.begin();
  }

  auto end() const {
    return pages.end();
  }

  size_t size() const {
    return pages.size();
  }

};

template <typename C>
auto Paginate(C& c, size_t page_size) {
  return Paginator(begin(c), end(c), page_size);
}


struct Stats {
    map<string, int> word_frequences;
    void operator += (const Stats& other) {
        for (auto& i : other.word_frequences){
            if(word_frequences.count(i.first)!=0){
                word_frequences.at(i.first) += i.second;
            }
            else{
                word_frequences[i.first] = i.second;
            }
        }
    }
};

vector<string> Split1(const string& line) {
    istringstream is(line);
    vector<string> results((istream_iterator<string>(is)), istream_iterator<string>());
    return results;
}

vector<string> Split(const string& s, char delimiter)
{
   std::vector<std::string> tokens;
   std::string token;
   std::istringstream tokenStream(s);

   while (std::getline(tokenStream, token, delimiter))
   {
      tokens.push_back(token);
   }
   for(auto i :tokens){
       cout<< i<<endl;
   }
   return tokens;
}

Stats ExploreLine(const set<string>& key_words, const string& line) {
    Stats result;
    for (const string& word : Split1(line)) {
        if (key_words.count(word)) {
            ++result.word_frequences[word];
        }
    }
    return result;
}
using VectorRange = vector<string>::iterator;
Stats ExploreKeyWordsSingleThread(const set<string>& key_words, VectorRange begin, VectorRange end) {
    Stats result;
    while(begin!= end){
        begin++;
        result+= ExploreLine(key_words, *begin);

    }
    return result;
}

Stats ExploreKeyWords(const set<string>& key_words, stringstream & input) {
    Stats result;
    vector<future<Stats>> futures;
    vector<string>vect;
    string str;
    while(input>>str) vect.push_back(str);
    for (auto page : Paginate(vect,1000000)){
        futures.push_back(async(ExploreKeyWordsSingleThread,move(key_words),page.begin(),page.end()));
    }
    for (auto& f : futures) {
        result += f.get();
     }
    return result;
}

void TestBasic() {
  const set<string> key_words = {"yangle", "rocks", "sucks", "all"};
  stringstream ss;
  ss << "this new yangle service really rocks\n";
  ss << "It sucks when yangle isn't available\n";
  ss << "10 reasons why yangle is the best IT company\n";
  ss << "yangle rocks others suck\n";
  ss << "Goondex really sucks, but yangle rocks. Use yangle\n";
  const auto stats = ExploreKeyWords(key_words, ss);
  const map<string, int> expected = {
    {"yangle", 6},
    {"rocks", 2},
    {"sucks", 1}
  };
  ASSERT_EQUAL(stats.word_frequences, expected);
}

int main() {
  TestRunner tr;
  RUN_TEST(tr, TestBasic);
}


