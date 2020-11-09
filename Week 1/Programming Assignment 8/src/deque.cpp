#include <string>
#include <iostream>
#include <cstddef>
#include <stdexcept>
#include <utility>
#include <vector>

using namespace std;


template <typename T>
class Deque {

public:
	Deque() = default;
	bool Empty() const {
		return front_.empty() && back_.empty();
	}

	const T& operator [] (size_t index) const {
		return index < front_.size() ? front_[front_.size() - 1 - index] : back_[index - front_.size()];
	}

	T& operator [] (size_t index) {
		return index < front_.size() ? front_[front_.size() - 1 - index] : back_[index - front_.size()];
	}

	size_t Size() const {
		return front_.size() + back_.size();
	}

	T& At(size_t index) {
		CheckIndex(index);
		return (*this)[index];
	}

	const T& At(size_t index) const {
		CheckIndex(index);
		return (*this)[index];
	}

	const T& Front() const {
		return front_.empty() ? back_.front() : front_.back();
	}

	T& Front() {
		return front_.empty() ? back_.front() : front_.back();
	}

	const T& Back() const {
		return back_.empty() ? front_.front() : back_.back();
	}

	T& Back() {
		return back_.empty() ? front_.front() : back_.back();
	}

	void PushFront(const T& element) {
		front_.push_back(element);
	}

	void PushBack(const T& element) {
		back_.push_back(element);
	}

private:
	void CheckIndex(size_t index) const {
		if(index >= Size()) {
			throw out_of_range("Index is out of range");
		}
	}

	vector<T> front_;
	vector<T> back_;
};
