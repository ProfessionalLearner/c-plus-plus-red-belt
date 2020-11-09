#include <string_view>
#include <vector>
#include <map>
#include <string>
#include <queue>
#include <iostream>
#include <deque>
using namespace std;

class Translator {
public:
  void Add(string_view source, string_view target) {
	  words.emplace(source, target);
	  source_target[words.back().first] = words.back().second;
	  target_source[words.back().second] = words.back().first;
  }
  string_view TranslateForward(string_view source) const {
	  auto iter = source_target.lower_bound(source);
	  if((*iter).first != source ) {
		  return string("");
	  } else {
		  return iter->second;
	  }

  }
  string_view TranslateBackward(string_view target) const {
	  auto iter = target_source.lower_bound(target);
	  if((*iter).first != target) {
		  return string("");
	  } else {
		  return iter->second;
	  }
  }

private:
  map<string_view, string_view> source_target;
  map<string_view, string_view> target_source;
  queue<pair<string, string>> words;
};

/*class Translator {
public:
  void Add(string_view source, string_view target) {
    const string_view source_view = CloneView(source);
    const string_view target_view = CloneView(target);
    source_target[source_view] = target_view;
    target_source[target_view] = source_view;
  }
  string_view TranslateForward(string_view source) const {
    return TranslateWord(source_target, source);
  }
  string_view TranslateBackward(string_view target) const {
    return TranslateWord(target_source, target);
  }

private:
  string_view CloneView(string_view s) {
    for (const auto* map_ptr : {&source_target, &target_source}) {
      const auto it = map_ptr->find(s);
      if (it != map_ptr->end()) {
        return it->first;
      }
    }
    return data.emplace_back(s);
  }

  string_view TranslateWord(const map<string_view, string_view>& dict, string_view s) const {
    if (const auto it = dict.find(s); it != dict.end()) {
      return it->second;
    } else {
      return {};
    }
  }


  map<string_view, string_view> source_target;
  map<string_view, string_view> target_source;
  deque<string> data;
};*/

int main(){
	return 0;
}
