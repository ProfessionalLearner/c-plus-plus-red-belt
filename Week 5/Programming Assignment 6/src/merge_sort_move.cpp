#include <iostream>
#include <vector>
#include <algorithm>
#include <string>
using namespace std;

/*template <typename RandomIt>
void MergeSort(RandomIt range_begin, RandomIt range_end) {
	int range = range_end - range_begin;
	if(range < 2) {
		return;
	} else {
		auto iter1 = range_begin + range / 3;
		auto iter2 = range_begin + range * 2 / 3;

		MergeSort(range_begin, iter1);
		MergeSort(iter1, iter2);
		MergeSort(iter2, range_end);

		inplace_merge(range_begin, iter1, iter2);
		inplace_merge(range_begin, iter2, range_end);
	}
}*/

template <typename RandomIt>
void MergeSort(RandomIt range_begin, RandomIt range_end) {
	int range = range_end - range_begin;
	if(range < 2) {
		return;
	} else {
		vector<typename RandomIt::value_type> elements(make_move_iterator(range_begin), make_move_iterator(range_end));
		auto iter1 = elements.begin() + range / 3;
		auto iter2 = elements.begin() + range * 2 / 3;

		MergeSort(elements.begin(), iter1);
		MergeSort(iter1, iter2);
		MergeSort(iter2, elements.end());

		vector<typename RandomIt::value_type> inter_elements;

		merge(make_move_iterator(elements.begin()), make_move_iterator(iter1),
				make_move_iterator(iter1), make_move_iterator(iter2),
				back_inserter(inter_elements));
		merge(make_move_iterator(inter_elements.begin()), make_move_iterator(inter_elements.end()),
				make_move_iterator(iter2), make_move_iterator(elements.end()), range_begin);
	}
}
int main() {
	return 0;
}
