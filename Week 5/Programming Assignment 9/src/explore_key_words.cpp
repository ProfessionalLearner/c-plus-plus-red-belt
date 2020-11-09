
#include <iostream>
#include <map>
#include <string>
#include <set>
#include <sstream>
#include <algorithm>
#include <string_view>
#include <iterator>
#include <future>
#include <functional>
using namespace std;

struct Stats {
  map<string, int> word_frequences;

  void operator += (const Stats& other) {
	  for(const auto& item : other.word_frequences) {
		  word_frequences[item.first] += item.second;
	  }
  }
};


Stats ExploreLine(const set<string>& key_words, const string& line) {
	Stats result;
	auto first = line.begin();
	auto last = line.end();
	while(true) {
		auto iter = find(first, last, ' ');
		string s(first, iter);
		auto iter2  = key_words.lower_bound(s);
		if(*iter2 == s) {
			result.word_frequences[s]++;
		}


		if(iter == last) {
			break;
		}

		first = iter + 1;
	}

	return result;
}


Stats ExploreKeyWordsSingleThread(
  const set<string>& key_words, istream& input
) {
  Stats result;
  for (string line; getline(input, line); ) {
    result += ExploreLine(key_words, line);
  }
  return result;
}

Stats ExploreKeyWords(const set<string>& key_words, istream& input) {
	vector<future<Stats>> total_stats;
	Stats result;
	while(!input.eof()) {
		string words;

		for(size_t i = 0; i < 5000; i++) {
			string word;
			input >> word;
			words += move(word) + " ";
		}

		total_stats.push_back(async(ExploreLine, ref(key_words), ref(words)));
	}

	for (auto& f : total_stats) {
		result += f.get();
	}

	return result;
}



int main() {
	return 0;
}
