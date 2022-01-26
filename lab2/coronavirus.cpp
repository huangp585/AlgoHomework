#include <iostream>

using namespace std;
long long a, b;

long long binpow(long long a, long long p) {
	if (p == 0) {
		return 1;
	}
	long long res = (binpow(a, p / 2)) % 1000000007;
	if (p % 2) {
		long long tmp = (res * res) % 1000000007;
		tmp = (tmp * a) % 1000000007;
		return tmp;
	}
	else {
		long long tmp = (res * res) % 1000000007;
		return tmp;
	}
}

long long covid(long long input) {
	long long output, index_a, power;
	index_a = input - 1;
	power = binpow(a, index_a);
	output = ((power*(((1-a-b) % 1000000007)/(1-a))) % 1000000007 +(b/(1-a))) % 1000000007;

	return (output+ 1000000007) % 1000000007;
}

int main() {
	cin.tie(0);
	cin.sync_with_stdio(0);
	int N;
	cin >> a >> b >> N;
	a = a % 1000000007;
	b = b % 1000000007;
	long long date;
	for (int i = 0; i < N; i++) {
		cin >> date;
		cout << covid(date) << "\n";
	}

	return 0;
}