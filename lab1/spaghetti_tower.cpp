#include<iostream>
#include<algorithm>
using namespace std;

long long n, ko, q;
long long x, l;
long long* first, * last;

bool upper_bound() {
	if ((x * ko) <= l) {
		return true;
	}
	else
		return false;
}

long long breakDown(long long *s,long long x, long long l) {
	long long cnt = 0;
	bool p = upper_bound();
	long long k;
	if (p) {
		k = ko;
	}
	else {
		k = l / x;
	}

	for (long long i = 1; i < k; i++) {
		first = lower_bound(s,s+n,x * i+1);
		last = upper_bound(s,s+n,x * (i + 1) - 1);
		long long length = last-first;
		cnt += length * i;
	}
	if (!p) {
		first = lower_bound(s, s + n, x * k + 1);
		last = upper_bound(s, s + n, l);
		long long length = last - first;
		cnt += length * k;
	}
	for (long long i = 0; i < k; i++) {
		first = lower_bound(s, s + n, x * (i + 1));
		last = upper_bound(s, s + n, x * (i + 1));
		long long length = last-first;
		cnt += length * (i+1);
	}
	return cnt;
}

int main() {
	cin.tie(0);
	cin.sync_with_stdio(0);
	cin >> n >> ko;
	long long* s = new long long[n];
	long long a;
	for (int i = 0; i < n; i++) {
		cin >> s[i];
	}
	sort(s, s + n);
	cin >> q;
	for (int i = 0; i < q; i++) {
		cin >> x >> l;
		cout << breakDown(s,x, l) << "\n";
	}
	return 0;
}