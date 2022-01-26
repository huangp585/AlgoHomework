// Example program
#include <iostream>
#include <map>
using namespace std;

map<int, int> m;

void search(int n) {
	if (!m.count(n)) {
		cout << "-1" << "\n";
		return;
	}
	cout << m[n] << "\n";
}

int main(){
	
	int N, M,input;
	cin >> N >> M;

	for (int i = 0; i < N; i++) {
		cin >> input;
		m.insert({ input,i });
	}

	for (int i = 0; i < M; i++){
		cin >> input;
		search(input);
	}
	return 0;
}
