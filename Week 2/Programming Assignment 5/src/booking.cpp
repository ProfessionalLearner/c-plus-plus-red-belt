#include <iomanip>
#include <iostream>
#include <vector>
#include <set>
#include <map>
#include <queue>
#include <utility>
#include <algorithm>

using namespace std;

struct BookInfo {
	int64_t time;
	string hotel_name;
	unsigned int client_id;
	int room_count;
};

class HotelManager {
public:
	void AddBooking(const int64_t& time, const string& hotel_name,
			const unsigned int& client_id, const int& room_count) {

		bookings_.push({time, hotel_name, client_id, room_count});
		clients_[hotel_name][client_id] += room_count;
		rooms_[hotel_name] += room_count;
		Adjust(time);
	}

	uint64_t GetClients(const string& hotel_name) {
		return clients_[hotel_name].size();
	}

	uint64_t GetRooms(const string& hotel_name) {
		return rooms_[hotel_name];
	}
private:
	void Adjust(const int64_t& current_time) {
		while(!bookings_.empty() &&
				bookings_.front().time + 86400 <= current_time) {
			auto info = bookings_.front();
			clients_[info.hotel_name][info.client_id] -= info.room_count;
			if(clients_[info.hotel_name][info.client_id] == 0) {
				clients_[info.hotel_name].erase(info.client_id);
			}
			rooms_[info.hotel_name] -= info.room_count;
			bookings_.pop();

		}
	}

	queue<BookInfo> bookings_;
	map<string, map<int64_t, int64_t>> clients_;
	map<string, uint64_t> rooms_;
};

int main() {
	  ios::sync_with_stdio(false);
	  cin.tie(nullptr);

	  HotelManager manager;

	  int query_count;
	  cin >> query_count;

	  for (int query_id = 0; query_id < query_count; ++query_id) {
			string query_type;
			cin >> query_type;
			if (query_type == "BOOK") {
				int64_t time;
				string hotel_name;
				unsigned int client_id;
				int room_count;
				cin >> time >> hotel_name >> client_id >> room_count;
				manager.AddBooking(time, hotel_name, client_id, room_count);
			} else if (query_type == "CLIENTS") {
				string hotel_name;
				cin >> hotel_name;
				cout << manager.GetClients(hotel_name) << "\n";
			} else if (query_type == "ROOMS") {
				string hotel_name;
				cin >> hotel_name;
				cout << manager.GetRooms(hotel_name) << "\n";
			}
	  }

	  return 0;
}
