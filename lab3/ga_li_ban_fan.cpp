#include<iostream>
#include<vector>
#include<algorithm>

using namespace std;

long long value[7] = { 1000,500,100,50,10,5,1 };
long long table[7] = { 0 };
long long change[1000001] = { 0 };

string ga_li_ban_fan(long long& num) {
	sort(change, change + num);
	for (int y = num - 1; y >= 0; y--) {
		for (int i = 0; i < 7; i++) {
			while (change[y] >= value[i] && table[i]) {
				change[y] -= value[i];
				table[i]--;
			}
		}
		if (change[y]) {
			return "No\n";
		}
	}
	return "Yes\n";
}

int main() {
	cin.tie(0);
	cin.sync_with_stdio(0);

	int T, N;
	cin >> T;
	for (int i = 0; i < T; i++) {
		for (int k = 0; k < 7; k++) {
			table[k] = 0;
		}
		//reset
		long long payment;
		long long num = 0;
		cin >> N;
		for (int j = 0; j < N; j++) {
			cin >> payment;
			long long num_coin;
			for (int k = 0; k < 7; k++) {
				cin >> num_coin;
				if (num_coin) {
					payment -= num_coin * value[k];
					table[k] += num_coin;
				}
			}
			if (payment) {
				change[num++] = -payment;
			}
		}
		cout << ga_li_ban_fan(num);
	}
	return 0;
}