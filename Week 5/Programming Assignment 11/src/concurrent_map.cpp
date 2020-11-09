#include <algorithm>
#include <numeric>
#include <vector>
#include <string>
#include <random>
#include <map>
#include <mutex>
using namespace std;

template <typename K, typename V>
class ConcurrentMap {
public:
  static_assert(is_integral<K>::value, "ConcurrentMap supports only integer keys");

  struct Access {
	lock_guard<mutex> guard;
    V& ref_to_value;
  };

  explicit ConcurrentMap(size_t bucket_count)
  : guards_(bucket_count)
  , data_(bucket_count) {}

  Access operator[](const K& key) {
	auto key_id = key > 0 ? key : -key;
	key_id = key_id % data_.size();
	return {lock_guard<mutex>(guards_[key_id]), data_[key_id][key]};
  }

  map<K, V> BuildOrdinaryMap() {
	  map<K, V> result;

	  for(size_t i = 0, I = data_.size(); i < I; ++i) {
		  lock_guard<mutex> guard(guards_[i]);
		  result.insert(data_[i].begin(), data_[i].end());
	  }

	  return result;
  }

private:
  vector<mutex> guards_;
  vector<map<K, V>> data_;
};


int main() {
	return 0;
}
