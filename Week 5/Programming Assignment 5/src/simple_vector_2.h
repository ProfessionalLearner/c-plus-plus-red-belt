#include <algorithm>
#include <cstdint>

using namespace std;

template <typename T>
class SimpleVector {
public:
  SimpleVector() = default;

  explicit SimpleVector(size_t size) {
	  size_ = size;
	  cap_ = size;
	  data_ = new T[cap_];
  }

  ~SimpleVector() {
	  if(data_ != nullptr) {
		  delete [] data_;
	  }
	  size_ = 0;
	  cap_ = 0;
  }

  T& operator[](size_t index) {
	  return data_[index];
  }

  T* begin() {
	  return data_;
  }

  T* end() {
	  return data_ + size_;
  }

  size_t Size() const {
	  return size_;
  }

  size_t Capacity() const {
	  return cap_;
  }

  void PushBack(T value) {
	  if(size_ >= cap_) {
		 if(cap_ == 0) {
			 cap_ = 1;
		 } else {
			 cap_ *= 2;
		 }

		 T* new_data = new T[cap_];
		 move(begin(), end(), new_data);

		 delete [] data_;
		 data_ = new_data;
		 data_[size_++] = move(value);
	  } else {
		data_[size_++] = move(value);
	  }
  }



private:
  T* data_ = nullptr;
  size_t size_ = 0;
  size_t cap_ = 0;
};
