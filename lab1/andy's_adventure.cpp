// Example program
#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;
int n, t, s;
vector<int> w;

bool binary_search(int a,int p,int r) {
	if (p <= r) {
		int mid = (p + r) / 2;
		if (w[mid] == a) {
			return true;
		}
		else if (w[mid] > a) {
			return binary_search(a, p, mid - 1);
		}
		else {
			return binary_search(a, mid + 1, r);
		}
	}
	return false;
}

void combination() {
	int sum, count = 0;
	for (int i = 0; i < n - 2; i++) {
		if (i > 0 && w[i] == w[i - 1]) {
			continue;
		}
		for (int j = i + 1; j < n - 1; j++) {
			if (j>i+1 && w[j] == w[j - 1]) {
				continue;
			}
			int a = t - w[i] - w[j];
			if (binary_search(a, j + 1, n - 1)) {
				count++;
			}
		}
	}
	if (count) {
		cout << count;
	}
	else {
		cout << "FeiDooDoo_Zuo_Wei_Men";
	}
	return;
}

int main() {
	cin.tie(0);
	cin.sync_with_stdio(0);
	cin >> n >> t;
	for (int i = 0; i < n; i++) {
		cin >> s;
		w.push_back(s);
	}
	sort(w.begin(), w.end());
	combination();
	return 0;
}