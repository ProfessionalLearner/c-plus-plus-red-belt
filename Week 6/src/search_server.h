#pragma once
#include "synchronized.h"
#include <istream>
#include <ostream>
#include <set>
#include <list>
#include <vector>
#include <unordered_map>
#include <map>
#include <future>
#include <mutex>
#include <string>
#include <deque>
#include <string_view>
using namespace std;

class InvertedIndex {
public:
  InvertedIndex() = default;
  explicit InvertedIndex(istream& document_input);
  void Add(string&& document);
  const vector<pair<size_t, size_t>> Lookup(const string_view& word) const;
  size_t GetDocsCount() const {
    return docs.size();
  }

private:
  // each pair represents docid and num of occurences of given string.
  unordered_map<string_view, vector<pair<size_t, size_t>>> inv_index;
  deque<string> docs;
};

class SearchServer {
public:
  SearchServer() = default;
  explicit SearchServer(istream& document_input);
  void UpdateDocumentBase(istream& document_input);
  void AddQueriesStream(istream& query_input, ostream& search_results_output);

private:
  Synchronized<InvertedIndex> index;
  vector<future<void>> futures_;
  bool is_initiliazed = false;
};
