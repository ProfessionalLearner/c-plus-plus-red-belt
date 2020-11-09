#include <algorithm>
#include <iostream>
using namespace std;

template<typename ForwardIterator, typename UnaryPredicate>
ForwardIterator max_element_if(
  ForwardIterator first, ForwardIterator last, UnaryPredicate pred) {
	ForwardIterator max_element  = find_if(first, last, pred);
	for(ForwardIterator curr = max_element; curr != last; ++curr) {
		if(curr != max_element && pred(*curr) && *max_element < *curr) {
			max_element = curr;
		}
	}
	return max_element;
}
