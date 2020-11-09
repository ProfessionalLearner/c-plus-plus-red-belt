#include <list>
#include <vector>
#include <array>
#include <iostream>
using namespace std;

array<int, 3> foo(int i) {
	array<int, 3> v = {i + 1, i + 2, i + 3};
	return v;
}

int main() {
	array<int, 3> v = foo(1);
	array<int, 3> g = foo(2);
	cout << v.data() << endl;
	cout << v[0] << endl;
	cout << g.data() << endl;
	cout << g[0] << endl;
	const int MAX_NUM_ATHLETES = 100000;

	int n;
	cin >> n;
	list<int> formation;
	vector<list<int>::iterator> athletes_pos(MAX_NUM_ATHLETES + 1, formation.end());

	for (int i = 0; i < n; i++) {
		int curr_athlete, next_athlete;
		cin >> curr_athlete >> next_athlete;
		athletes_pos[curr_athlete] = formation.insert(athletes_pos[next_athlete], curr_athlete);
	}

	for (const auto& x : formation) {
		cout << x << "\n";
	}
	return 0;
}
