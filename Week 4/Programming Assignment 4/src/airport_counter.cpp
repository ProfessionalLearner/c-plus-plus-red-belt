#include <algorithm>
#include <array>
#include <iostream>
#include <random>
#include <vector>

using namespace std;

template <typename TAirport>
class AirportCounter {
public:
  AirportCounter() {
	  data_.fill(0);
  }

  template <typename TIterator>
  AirportCounter(TIterator begin, TIterator end) {
	  data_.fill(0);
	  for(auto iter = begin; iter < end; iter++) {
		  ++data_[static_cast<size_t>(*iter)];
	  }
  }

  size_t Get(TAirport airport) const {
	  return data_[static_cast<size_t>(airport)];
  }

  void Insert(TAirport airport) {
	  ++data_[static_cast<size_t>(airport)];
  }

  void EraseOne(TAirport airport) {
	  if(data_[static_cast<size_t>(airport)] > 0) {
		 --data_[static_cast<size_t>(airport)];
	  }
  }

  void EraseAll(TAirport airport) {
	  data_[static_cast<size_t>(airport)] = 0;
  }

  using Item = pair<TAirport, size_t>;
  using Items = array<Item, static_cast<size_t>(TAirport::Last_)>;


  Items GetItems() const {
	  Items items;
	  for(int i = 0; i < size_; i++) {
		  items[i] = make_pair(static_cast<TAirport>(i), data_[i]);
	  }
	  return items;
  }

private:
  array<size_t, static_cast<size_t>(TAirport::Last_)> data_;
  const size_t size_ = static_cast<size_t>(TAirport::Last_);
};


int main() {
	return 0;
}
