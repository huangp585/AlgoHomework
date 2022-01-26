// Example program
#include <iostream>
#include <map>
using namespace std;
map<long long, long long> m;
int n;

void permutation(map<long long, long long>& m) {
	long long pre = 0, cur, ans = 1;
	for (int i = n; i > 0; i--) {//從範圍大的開始放，下縮時不影響擺放選擇
		cur = (m[i] + pre) % 1000000007;
		ans *= cur;
		ans %= 1000000007;
		pre = cur % 1000000007 - 1;
	}
	cout << ans;
}

int main() {
	cin.tie(0);
	cin.sync_with_stdio(0);
	cin >> n;
	long long input;
	for (int i = 0; i < n; i++) {
		cin >> input;
		if (input > n) {//排序，同時過濾掉比n大的輸入
			if (m.count(n)) {
				m[n]++;
			}
			else {
				m.insert({ n,1 });
			}
		}
		else if (m.count(input)) {
			m[input]++;
		}
		else {
			m.insert({ input,1 });
		}
	}
	permutation(m);
	return 0;
}