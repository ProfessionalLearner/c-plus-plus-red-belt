#include <algorithm>
using namespace std;

template <typename T>
class SimpleVector {
public:
  SimpleVector() = default;
  explicit SimpleVector(size_t size) {
		data_ = new T[size];
		size_ = size;
		capacity_ = size;
  }
  SimpleVector(const SimpleVector& rhs) {
		data_ = new T[rhs.capacity_];
		size_ = rhs.size_;
		capacity_ = rhs.size_;
		copy(rhs.begin(), rhs.end(), begin());
  }

  ~SimpleVector() {
	  delete[] data_;
	  size_ = 0;
	  capacity_ = 0;
  }

  void operator=(const SimpleVector& rhs) {
	  if(rhs.size_ <= capacity_) {
		  copy(rhs.begin(), rhs.end(), begin());
		  size_ = rhs.size_;
	  } else {
		  SimpleVector<T> temp(rhs);
		  swap(temp.data_, data_);
		  swap(temp.size_, size_);
		  swap(temp.capacity_, capacity_);
	  }
  }

  T& operator[](size_t index) {
	  return data_[index];
  }

  const T* begin() const {
	  return data_;
  }

  const T* end() const {
	  return data_ + size_;
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
	  return capacity_;
  }

  void PushBack(const T& value) {
	  if(size_ >= capacity_) {
		 if(capacity_ == 0) {
			 capacity_ = 1;
		 } else {
			 capacity_ *= 2;
		 }

		 T* new_data = new T[capacity_];
		 for(size_t i = 0; i < size_; i++) {
			 new_data[i] = data_[i];
		 }

		 delete [] data_;
		 new_data[size_++] = value;
		 data_ = new_data;
	  } else {
		data_[size_++] = value;
	  }
  }

private:
  T* data_ = nullptr;
  size_t size_ = 0;
  size_t capacity_ = 0;
};
