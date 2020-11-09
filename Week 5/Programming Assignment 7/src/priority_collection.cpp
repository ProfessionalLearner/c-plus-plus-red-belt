#include "test_runner.h"
#include <algorithm>
#include <iostream>
#include <iterator>
#include <memory>
#include <set>
#include <utility>
#include <vector>

using namespace std;

template <typename T>
class PriorityCollection {
public:
  using Id = size_t;

  Id Add(T object) {
	  const Id id = items_.size();
	  items_.push_back({move(object)});
	  sorted_items_.insert({0, id});
	  return id;
  }

  template <typename ObjInputIt, typename IdOutputIt>
  void Add(ObjInputIt range_begin, ObjInputIt range_end,
           IdOutputIt ids_begin) {
	  while(range_begin != range_end) {
		  *ids_begin++ = Add(move(*range_begin++));
	  }

  }

  bool IsValid(Id id) const {
	  return id >= 0 && id < items_.size() && items_[id].priority != nprior;
  }

  const T& Get(Id id) const {
      return items_[id].data;

  }


  void Promote(Id id) {
      auto& item = items_[id];
      const size_t old_prior = item.priority;
      const size_t new_prior = ++item.priority;
      sorted_items_.erase({old_prior, id});
      sorted_items_.insert({new_prior, id});
  }


  pair<const T&, int> GetMax() const {
	  const auto& item = items_[prev(sorted_items_.end())->second];
	  return {item.data, item.priority};
  }

  pair<T, int> PopMax() {
	  const auto iter = prev(sorted_items_.end());
	  auto& item = items_[iter->second];
	  sorted_items_.erase(iter);
	  const int prior = item.priority;
	  item.priority = nprior;
	  return {move(item.data), prior};
  }

private:
  static const size_t nprior = -1;

  struct Item {
	  T data;
	  size_t priority = 0;
  };

  vector<Item> items_;
  set<pair<size_t, Id>> sorted_items_;
};


int main() {

  return 0;
}
