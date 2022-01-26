// Example program
#include <iostream>
#include <queue>

using namespace std;
struct inf{
	int id,p;
};
queue<inf> q;

void sign() {
	cout << q.front().id << "\n";
	q.front().p--;
	if (q.front().p > 0) {
		q.push(q.front());
		q.pop();
		return;
	}
	q.pop();
}

int main(){
	int N;
	inf b;
	cin >> N;
	for (int i = 0; i < N; i++) {
		cin >> b.id >> b.p;
		q.push(b);
	}
	while (!q.empty()) {
		sign();
	}
	return 0;
}
