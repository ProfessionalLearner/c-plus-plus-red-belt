#include <iomanip>
#include <iostream>
#include <vector>
#include <set>
#include <map>
#include <utility>
#include <algorithm>

using namespace std;

class ReadingManager {
public:
  ReadingManager()
      : pages_(MAX_PAGE_COUNT + 1) {}

  void Read(int user_id, int page_count) {
	  if(users_pages_.count(user_id) == 0) {
		  AddUser(user_id, page_count);
	  } else {
		  pages_[users_pages_[user_id]].erase(user_id);
		  AddUser(user_id, page_count);
	  }
  }

  double Cheer(int user_id) const {
	  if(users_pages_.count(user_id) == 0) {
		  return 0;
	  } else if (users_pages_.size() == 1) {
		  return 1;
	  } else {
		  int total_count = 0;
		  int page_num = users_pages_.at(user_id);
		  for(int i = 1; i < page_num; i++) {
			  total_count += (int) pages_[i].size();
		  }

		  return total_count / (GetSize() - 1.0);
	  }
  }

private:
  static const int MAX_PAGE_COUNT = 1000;

  map<int, int> users_pages_;
  vector<set<int>> pages_;

  void AddUser(const int& user_id, const int& page_count) {
    pages_[page_count].insert(user_id);
    users_pages_[user_id] = page_count;
  }

  double GetSize() const {
	  return users_pages_.size();
  }
};


int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);

  ReadingManager manager;

  int query_count;
  cin >> query_count;

  for (int query_id = 0; query_id < query_count; ++query_id) {
    string query_type;
    cin >> query_type;
    int user_id;
    cin >> user_id;

    if (query_type == "READ") {
      int page_count;
      cin >> page_count;
      manager.Read(user_id, page_count);
    } else if (query_type == "CHEER") {
      cout << setprecision(6) << manager.Cheer(user_id) << "\n";
    }
  }

  return 0;
}
