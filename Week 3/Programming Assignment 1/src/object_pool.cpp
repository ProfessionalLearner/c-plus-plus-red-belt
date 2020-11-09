#include <algorithm>
#include <iostream>
#include <string>
#include <queue>
#include <memory>
#include <stdexcept>
#include <set>
using namespace std;

template <class T>
class ObjectPool {
public:
  T* Allocate() {
	  if(deallocated_.empty()) {
		  T* new_alloc = new T;
		  allocated_.insert(new_alloc);
		  return new_alloc;
	  } else {
		  auto old_alloc = deallocated_.front();
		  deallocated_.pop();
		  allocated_.insert(old_alloc);
		  return old_alloc;
	  }
  }
  T* TryAllocate() {
	  if(deallocated_.empty()) {
		  return nullptr;
	  } else {
		  auto old_alloc = deallocated_.front();
		  deallocated_.pop();
		  allocated_.insert(old_alloc);
		  return old_alloc;
	  }
  }

  void Deallocate(T* object) {
	  const bool is_in = allocated_.find(object) != allocated_.end();

	  if(is_in) {
		  deallocated_.push(object);
		  allocated_.erase(object);
	  } else {
		  throw invalid_argument("No such allocated object");
	  }
  }

  ~ObjectPool() {
	  for(auto& item : allocated_) {
		  delete item;
	  }

	  while(!deallocated_.empty()) {
		  delete deallocated_.front();
		  deallocated_.pop();
	  }
  }

private:
  set<T*> allocated_;
  queue<T*> deallocated_;
};


int main() {
	return 0;
}
