#include <algorithm>
#include <string>
#include <vector>
#include <sstream>
#include <iostream>
#include <set>

using namespace std;

class Learner {
 private:
  vector<string> dict;
  set<string> set_;

 public:
  int Learn(const vector<string>& words) {
	  int init_size = set_.size();
	  set_.insert(words.begin(), words.end());
	  int new_words = set_.size() - init_size;

	  return new_words;
  }
  vector<string> KnownWords() {
	dict.assign(set_.begin(), set_.end());
    return dict;
  }
};

int main() {

  Learner learner;
  string line;
  while (getline(cin, line)) {
    vector<string> words;
    stringstream ss(line);
    string word;
    while (ss >> word) {
      words.push_back(word);
    }
    cout << learner.Learn(words) << "\n";
  }
  cout << "=== known words ===\n";
  for (auto word : learner.KnownWords()) {
    cout << word << "\n";
  }
}
