#include "search_server.h"
#include "iterator_range.h"
#include <numeric>
#include <algorithm>
#include <iterator>
#include <sstream>
#include <iostream>
#include <iterator>

vector<string_view> SplitIntoWords(string_view line) {
	vector<string_view> result;
    size_t pos = line.find_first_not_of(' ');
    line.remove_prefix(pos);

	while(pos != line.npos) {
		pos = line.find(' ');
		result.push_back(line.substr(0, pos));
		pos = line.find_first_not_of(' ', pos);
		line.remove_prefix(pos);
	}

	return result;
}

void InvertedIndex::Add(string&& document) {
	docs.push_back(move(document));

	const size_t docid = docs.size() - 1;

	map<string_view, size_t> word_count;


	for(const auto& word : SplitIntoWords(docs.back())) {
		++word_count[word];
	}

    for(const auto& [word, count] : word_count) {
    	inv_index[word].push_back({docid, count});
    }


}

const vector<pair<size_t, size_t>> InvertedIndex::Lookup(const string_view& word) const {
	if (auto it = inv_index.find(word); it != inv_index.end()) {
		return it->second;
	}
	const vector<pair<size_t, size_t>> result;
	return result;
}



SearchServer::SearchServer(istream& document_input) {
	UpdateDocumentBase(document_input);
}


void SearchServer::UpdateDocumentBase(istream& document_input) {
    auto future = [&document_input, this] {
        InvertedIndex new_index;

        for (string current_document; getline(document_input, current_document); ) {
            new_index.Add(move(current_document));
        }

        auto access = index.GetAccess();
        access.ref_to_value = move(new_index);
    };

    futures_.push_back(async(future));

    if(!is_initiliazed) {
        futures_.back().get();
        is_initiliazed = true;
    }
}


void SearchServer::AddQueriesStream(istream& query_input,
		ostream& search_results_output) {
	// AddQueriesStreamHelper(query_input, search_results_output, index);

    auto future = [&query_input, &search_results_output, this] {
        size_t docs_num;
        {
        	docs_num = index.GetAccess().ref_to_value.GetDocsCount();
        }
        vector<size_t> docid_count(docs_num);

        for (string current_query; getline(query_input, current_query); ) {
            for(const auto& word: SplitIntoWords(current_query)) {
                for(const auto& [docid, qty] : index.GetAccess().ref_to_value.Lookup(word)) {
                    docid_count[docid] += qty;
                }
            }

            vector<pair<size_t, size_t>> search_results(docid_count.size());
            for(size_t i = 0, I = search_results.size(); i < I; ++i) {
                search_results[i] = {i, docid_count[i]};
            }

            partial_sort(begin(search_results), Head(search_results.begin(), search_results.end(),
            		search_results.size(), 5).end(), end(search_results),
                         [](const pair<size_t, size_t>& lhs, const pair<size_t, size_t>& rhs) {
                int64_t lhs_docid = lhs.first;
                int64_t rhs_docid = rhs.first;
                return make_pair(lhs.second, -lhs_docid) > make_pair(rhs.second, -rhs_docid);
            });

            search_results_output << current_query << ':';
            for (const auto& [docid, count] : Head(search_results.begin(), search_results.end(),
            		search_results.size(), 5)) {
                if(count == 0) {
                    break;
                }

                search_results_output << " {"
                                      << "docid: " << docid << ", "
                                      << "hitcount: " << count << '}';
            }
            search_results_output << '\n';

            fill(begin(docid_count), end(docid_count), 0);
        }
    };

    futures_.push_back(async(future));
}
