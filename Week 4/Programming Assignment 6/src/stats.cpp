#include "stats.h"
#include <iostream>
#include <array>
using namespace std;

Stats::Stats()
: method_stats({{"GET", 0}, {"POST", 0}, {"PUT", 0}, {"DELETE", 0}, {"UNKNOWN", 0}})
, uri_stats({{"/", 0}, {"/order", 0}, {"/product", 0}, {"/basket", 0}, {"/help", 0}, {"unknown", 0}}) {}

void Stats::AddMethod(string_view method) {
	if(method_stats.find(method) != method_stats.end()) {
		method_stats[method]++;
	} else {
		method_stats["UNKNOWN"]++;
	}
}

void Stats::AddUri(string_view uri) {
	if(uri_stats.find(uri) != uri_stats.end()) {
		uri_stats[uri]++;
	} else {
		uri_stats["unknown"]++;
	}
}

const map<string_view, int>& Stats::GetMethodStats() const {
	return method_stats;
}

const map<string_view, int>& Stats::GetUriStats() const {
	return uri_stats;
}

HttpRequest ParseRequest(string_view line) {
	array<string_view, 3> v;
	size_t pos = 0;
	while (line[pos] == ' ' && pos != line.npos) {
	    ++pos;
	}
	line.remove_prefix(pos);
	int i = 0;
	while(true) {
		size_t space = line.find(' ');
		v[i] = line.substr(0, space);

		if(space == line.npos || i == 2) {
			break;
		} else {
			line.remove_prefix(space + 1);
			i++;
		}
	}

	return {v[0], v[1], v[2]};
}
