#include "search_server.h"
#include "iterator_range.h"
#include "profile.h"
#include <algorithm>
#include <iterator>
#include <sstream>


vector<string> SplitIntoWords(const string& line) {
  istringstream words_input(line);
  return {istream_iterator<string>(words_input), istream_iterator<string>()};
}

void InvertedIndex::Add(const string& document) {
  docs.push_back(document);
  const size_t docid = docs.size() - 1;
  for (const auto& word : SplitIntoWords(document)) {
    index[word].push_back(docid);
  }
}

vector<size_t> InvertedIndex::Lookup(const string& word) const {
  if (auto it = index.find(word); it != index.end()) {
    return it->second;
  } else {
    return {};
  }
}



void UpdateDocumentBaseAsync(istream& document_input, Synchronized<InvertedIndex>& index){
    InvertedIndex new_index;
    for (string current_document; getline(document_input, current_document);){
        new_index.Add(move(current_document));
    }
    swap(index.GetAccess().ref_to_value, new_index);
}


void AddQueriesStreamAsync(istream& query_input, ostream& search_results_output,Synchronized<InvertedIndex>& index){
  vector<pair<size_t, size_t>> docid_count( index.GetAccess().ref_to_value.GetDocsNum(), make_pair(0,0));
  map<string, vector<pair<size_t,size_t>>> orig_index;
  map<string, map<size_t,size_t>> indexator;
  pair<size_t,size_t> ab = {0,0};
  int i = 0;
  for (string current_query; getline(query_input, current_query);){
    const auto words = SplitIntoWords(current_query);
    for (const auto& word : words){
        if(orig_index.count(word)==0){
            for (const size_t docid : index.GetAccess().ref_to_value.Lookup(word)) {
                if(indexator[word].count(docid)==0){
                    indexator[word][docid] = i;
                    orig_index[word].push_back({docid,1});
                    i++;
                }else{
                    orig_index[word][indexator[word][docid]].second+=1;
                }
            }
            i = 0;
            for(const auto& spec :orig_index[word]){
                docid_count[spec.first].first = spec.first;
                docid_count[spec.first].second+= spec.second;
            }

        }else{
            for(const auto& spec :orig_index[word]){
                docid_count[spec.first].first = spec.first;
                docid_count[spec.first].second+= spec.second;
            }
        }
    }
    vector<pair<size_t, size_t>> search_results(docid_count.begin(), docid_count.end());
    if(search_results.size()<5){
        sort(
              begin(search_results),
              end(search_results),
              [](pair<size_t, size_t> lhs, pair<size_t, size_t> rhs) {
                int64_t lhs_docid = lhs.first;
                auto lhs_hit_count = lhs.second;
                int64_t rhs_docid = rhs.first;
                auto rhs_hit_count = rhs.second;
                return make_pair(lhs_hit_count, -lhs_docid) > make_pair(rhs_hit_count, -rhs_docid);
              }
            );
        while(*search_results.rbegin() == ab){
            search_results.pop_back();

        }
    }else{
        partial_sort(
          begin(search_results),begin(search_results)+5,
          end(search_results),
          [](pair<size_t, size_t> lhs, pair<size_t, size_t> rhs) {
            int64_t lhs_docid = lhs.first;
            auto lhs_hit_count = lhs.second;
            int64_t rhs_docid = rhs.first;
            auto rhs_hit_count = rhs.second;
            return make_pair(lhs_hit_count, -lhs_docid) > make_pair(rhs_hit_count, -rhs_docid);
          }
        );
        while(*search_results.rbegin() == ab){
            search_results.pop_back();

        }
    }
    search_results_output << current_query << ':';
    for (auto [docid, hitcount] : Head(search_results, 5)) {
      search_results_output << " {"
        << "docid: " << docid << ", "
        << "hitcount: " << hitcount << '}';
    }
    search_results_output << endl;
    docid_count.assign( index.GetAccess().ref_to_value.GetDocsNum(), make_pair(0,0));
  }
}
SearchServer::SearchServer(istream& document_input) {
    //base_update_future.push_back(async(launch::async, &SearchServer::UpdateDocumentBaseAsync, this, ref(document_input)));
    UpdateDocumentBaseAsync(document_input,index);
}
void SearchServer::UpdateDocumentBase(istream& document_input) {
    futures.push_back(async(UpdateDocumentBaseAsync, ref(document_input), ref(index)));
}

void SearchServer::AddQueriesStream(istream& query_input, ostream& search_results_output) {
    futures.push_back(async(AddQueriesStreamAsync, ref(query_input), ref(search_results_output), ref(index))
    );
}



