
#include <list>
#include <iostream>
#include <cstdint>
#include <iterator>
#include <numeric>
#include <vector>
#include <algorithm>
using namespace std;


template <typename RandomIt>
void MakeJosephusPermutation(RandomIt first, RandomIt last, uint32_t step_size) {
  list<typename RandomIt::value_type> pool;
  move(first, last, back_inserter(pool));
  auto pool_iter = pool.begin();

  while (!pool.empty()) {
		*(first++) = move(*pool_iter);
		pool_iter = pool.erase(move(pool_iter));

		if (pool.empty()) {
			break;
		}

		if (pool_iter == pool.end()) {
			pool_iter = pool.begin();
		}

		for(uint32_t i = 0; i < step_size - 1; ++i) {
		    if (pool_iter == pool.end()) {
				pool_iter = pool.begin();
		    }
			pool_iter = move(next(pool_iter));
			if (pool_iter == pool.end()) {
				pool_iter = pool.begin();
			}
		}
  }
}




int main() {
	return 0;
}
