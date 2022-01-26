// Example program
#include <iostream>
#include <iomanip>
#include <vector>

using namespace std;
double n, k;
double x, m;
int p = 0;
vector<double> a1;
vector<double> a2;

void binary_search(double left, double right) {
	p = 0;
	if (right - left < 0.0000005) {
		cout << fixed;
		cout << setprecision(6) << right;
		return;
	}
	x = (left+right) / 2;
	for (int i = 0; i < n; i++) {
		double pi = (a1[i] / x) - a2[i];
		if (pi < 1) {
			continue;
		}
		p += pi;
	}
	if (p>= k) {
		binary_search(x, right);
	}
	else {
		binary_search(left, x);
	}
}

int main() {
	cin.tie(0);
	cin.sync_with_stdio(0);
	cin >> n >> k;
	double A, B;
	for (int i = 0; i < n; i++) {
		cin >> A >> B;
		a1.push_back(A);
		a2.push_back(B);
	}
	m = a1[0] / (a2[0]+1);
	for (int i = 1; i < n; i++) {
		if (m < a1[i] / (a2[i]+1)) {
			m = a1[i] / (a2[i]+1);
		}
	}
	binary_search(0, m);

	return 0;
}