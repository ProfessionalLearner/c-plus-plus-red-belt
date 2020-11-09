#pragma once

#include <cstdlib>


template <typename T>
class SimpleVector {
public:
  SimpleVector() {
	  data_ = nullptr;
	  end_ = data_;
	  size_ = 0;
	  cap_ = 0;
  }

  explicit SimpleVector(size_t size) {
	  size_ = size;
	  cap_ = size;
	  data_ = new T[cap_];
	  end_ = data_ + size_;
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
	  return end_;
  }

  size_t Size() const {
	  return size_;
  }

  size_t Capacity() const {
	  return cap_;
  }

  void PushBack(const T& value) {
	  if(size_ >= cap_) {
		 if(cap_ == 0) {
			 cap_ = 1;
		 } else {
			 cap_ *= 2;
		 }

		 T* new_data = new T[cap_];
		 for(size_t i = 0; i < size_; i++) {
			 new_data[i] = data_[i];
		 }

		 delete [] data_;
		 new_data[size_++] = value;
		 data_ = new_data;
		 end_ = data_ + size_;
	  } else {
		data_[size_++] = value;
		end_ = data_ + size_;
	  }
  }

private:
  T* data_;
  T* end_;
  size_t size_;
  size_t cap_;
};
