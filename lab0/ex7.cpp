// Example program
#include <iostream>
#include <vector>

using namespace std;

struct tax {
	int least;
	float rate;
};
vector<tax> v;
vector<int> s;

void split() {
	for (int i = 0; i < v.size()-1; i++) {
		s.push_back(v[i + 1].least - v[i].least);
	}
}

void pay_tax(int &income) {
	int f = 0;
	int i = 0;
	int l = 0;
	while (f <= income) {
		l = i;
		f += s[i];
		i++;
	}

	float sum = 0;
	for (int i = 0; i < l; i++) {
		sum += s[i] * v[i].rate;
	}
	sum += (income - v[l].least + 1) * v[l].rate;
	cout << sum << "\n";
}

int main(){
	int N, M;
	tax t;
	cin >> N;
	for (int i = 0; i < N; i++) {
		cin >> t.least >> t.rate;
		v.push_back(t);
	}

	split();

	cin >> M;
	int income;
	for (int i = 0; i < M; i++) {
		cin >> income;
		pay_tax(income);
	}
	return 0;
}
