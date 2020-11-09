#include <algorithm>
#include <string>
#include <vector>
#include <iostream>
#include <map>
using namespace std;


template <typename String>
using Group = vector<String>;

template <typename String>
using Char = typename String::value_type;

template <typename String>
String StringChars(const String& s) {
	String chars = s;
	sort(begin(chars), end(chars));
	chars.erase(unique(begin(chars), end(chars)), end(chars));
	return chars;
}

template <typename String>
vector<Group<String>> GroupHeavyStrings(vector<String> strings) {
	map<String, Group<String>> groups;
	vector<Group<String>> result;
	for(String& s : strings) {
		groups[StringChars(s)].push_back(move(s));
	}

	for(auto& [key, group] : groups) {
		result.push_back(move(group));
	}

	return result;
}


int main() {

	return 0;
}
