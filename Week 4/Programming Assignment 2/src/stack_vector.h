#pragma once

#include <array>
#include <stdexcept>
using namespace std;

template <typename T, size_t N>
class StackVector {
public:
  explicit StackVector(size_t a_size = 0) : size_(a_size) {
	  if(a_size > N) {
		  throw invalid_argument("Size cannot exceed capacity");
	  }
  }

  T& operator[](size_t index) {
	  return data_[index];
  }

  const T& operator[](size_t index) const {
	  return data_[index];
  }

  auto begin() {
	  return data_.begin();
  }

  auto end() {
	  return data_.begin() + size_;
  }

  auto begin() const {
	  return data_.begin();
  }

  auto end() const {
	  return data_.begin() + size_;
  }

  size_t Size() const {
	  return size_;
  }
  size_t Capacity() const {
	  return N;
  }

  void PushBack(const T& value) {
	  if(size_ >= N) {
		  throw overflow_error("Stack is full");
	  } else {
		  data_[size_++] = value;
	  }
  }
  T PopBack() {
	  if(size_ == 0) {
		  throw underflow_error("Stack is empty");
	  } else {
		  --size_;
		  return data_[size_];
	  }
  }

private:
  array<T, N> data_;
  size_t size_;
};

