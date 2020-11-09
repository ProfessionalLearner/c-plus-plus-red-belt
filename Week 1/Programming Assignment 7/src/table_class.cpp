#include <string>
#include <iostream>
#include <vector>

using namespace std;

template <typename T>
class Table {
public:
	  Table(size_t num_rows, size_t num_cols) {
	    Resize(num_rows, num_cols);
	  }

	  void Resize(size_t num_rows, size_t num_cols) {
	    data.resize(num_rows);
	    for (auto& item : data) {
	      item.resize(num_cols);
	    }
	  }

	  const vector<T>& operator [] (size_t index) const {
		  return data[index];
	  }

	  vector<T>& operator [] (size_t index) {
		  return data[index];
	  }

	  pair<size_t, size_t> Size() const {
		    return {data.size(), (data.empty() ? 0 : data[0].size())};
	  }
private:
	vector<vector<T>> data;
};
