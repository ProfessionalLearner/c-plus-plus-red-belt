#pragma once

#include <algorithm>
using namespace std;

template <typename It>
class IteratorRange {
public:
  IteratorRange(It first, It last) : first(first), last(last) {
  }

  It begin() const {
    return first;
  }

  It end() const {
    return last;
  }

  size_t size() const {
    return last - first;
  }

private:
  It first, last;
};

template <typename Iterator>
auto Head(Iterator first, Iterator last, const size_t& size_, int top) {
  return IteratorRange<Iterator>(first, first + min<size_t>(max(top, 0), size_));
}
