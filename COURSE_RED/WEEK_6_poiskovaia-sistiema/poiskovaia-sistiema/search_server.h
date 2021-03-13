#pragma once
#include <istream>
#include <ostream>
#include <set>
#include <list>
#include <vector>
#include <map>
#include <string>
#include <future>
#include "synchronized.h"

using namespace std;
class InvertedIndex {
public:
  void Add(const string& document);
  vector<size_t> Lookup(const string& word) const;
  const string& GetDocument(size_t id) const {
    return docs[id];
  }
  size_t GetDocsNum(){
      return docs.size();
  }

private:
  map<string, vector<size_t>> index;
  vector<string> docs;
};

class SearchServer {
public:
  SearchServer() = default;
  explicit SearchServer(istream& document_input);
  void UpdateDocumentBase(istream& document_input);
  void AddQueriesStream(istream& query_input, ostream& search_results_output);
private:
  Synchronized<InvertedIndex> index;
  vector<future<void>> futures;
};
