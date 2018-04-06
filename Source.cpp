#include <iostream>
#include <set>
#include <vector>
#include <algorithm>

using namespace std;

int change_money(const int64_t &M, const set<int64_t> &coin_list, vector <int64_t> &min_coints, vector <int64_t> &coin_used);

auto main()->int {
	int64_t M;
	cout << "Money to change: ";
	cin >> M;
	cout << "Coins list (CTRL + Q to stop input): ";
	int64_t x;
	set <int64_t> coins_list;
	while (cin >> x) {
		coins_list.insert(x);
	}
	vector <int64_t> min_coints;
	vector <int64_t> coin_used;
	cout << "Min notes used: " << change_money(M, coins_list, min_coints, coin_used) << endl;
	cout << "List: " << endl;
	while (M > 0) {
		cout << coin_used[M] << " ";
		M = M - coin_used[M];
	}
	return EXIT_SUCCESS;
}

int change_money(const int64_t &M, const set<int64_t> &coin_list, vector <int64_t> &min_coints, vector <int64_t> &coin_used) {
	min_coints.clear();
	coin_used.clear();
	for (int64_t i = 0; i < M + 1; ++i) {
		min_coints.push_back(INT64_MAX);
		coin_used.push_back(0);
	}

	for (auto&& i : coin_list) {
		min_coints[i] = 1;
		coin_used[i] = i;
	}

	int64_t total_money = 0;
	int64_t coin_count = 0;
	for (auto&& i : coin_list) {
		for (auto&& j : coin_list) {
			total_money = i;
			coin_count = 1;
			while (total_money <= M) {
				total_money += j;
				++coin_count;
				if (total_money <= M) {
					if (min_coints[total_money] > coin_count) {
						min_coints[total_money] = coin_count;
						coin_used[total_money] = j;
					}
				}
			}
		}
	}
	return min_coints[M];
}