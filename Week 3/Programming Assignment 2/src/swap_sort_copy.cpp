#include <vector>
#include <algorithm>
#include <memory>
#include <numeric>
using namespace std;

template <typename T>
void Swap(T* first, T* second) {
	auto temp = *first;
	*first = *second;
	*second = temp;
}

template <typename T>
void SortPointers(vector<T*>& pointers) {
	sort(begin(pointers), end(pointers), [](T* lhs, T* rhs) {
		return *lhs < *rhs;
	});
}

template <typename T>
void ReversedCopy(T* source, size_t count, T* destination) {
	auto src_begin = source;
	auto src_end = source + count;
	auto dst_begin = destination;
	auto dst_end = destination + count;
	if(dst_end <= src_begin || src_end <= dst_begin) {
		reverse_copy(src_begin, src_end, dst_begin);
	} else if(dst_begin > src_begin) {
		for (size_t i = 0; src_begin + i < dst_begin; i++) {
			*(dst_end - 1 - i) = *(src_begin + i);
		}
		reverse(dst_begin, src_end);
	} else {
		for(size_t i = 0; src_end - 1 - i >= dst_end; i++) {
			*(dst_begin + i) = *(src_end - 1 - i);
		}
		reverse(src_begin, dst_end);
	}
}

int main() {
	return 0;
}
