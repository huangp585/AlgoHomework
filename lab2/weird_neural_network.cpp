#include <iostream>
#include <vector>

using namespace std;


struct node {
	long long c = -1;
	vector<long long> preNode;
};
vector<node> v;

long long neural(node start) {
	if (!start.preNode.size()) {
		return start.c % 1000000007;
	}

	long long pre1, pre2;
	pre1 = neural(v[start.preNode[0]]) % 1000000007;
	pre2 = neural(v[start.preNode[1]]) % 1000000007;
	start.c = start.c * (pre1 + pre2) % 1000000007;
	return start.c;
}

int main() {
	int N;
	cin >> N;
	node cur;
	v.push_back(cur);
	for (int i = 1; i <= N; i++) {
		cin >> cur.c;
		v.push_back(cur);
	}
	for (int i = 2; i < N + 1; i++) {
		long long num;
		cin >> num;
		v[num].preNode.push_back(i);
	}


	cout << neural(v[1]);
	return 0;
}