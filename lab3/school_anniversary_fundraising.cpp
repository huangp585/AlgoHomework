#include<iostream>
#include<map>
#include<utility>
using namespace std;

int N;
long long p, cnt = 0;
pair<int, int> range;
multimap<int, int> m;

long long school_anniversary() {
	int end = range.second;
	multimap<int, int>::iterator itr;
	while (end>range.first) {
		itr = m.lower_bound(end);
		if (itr == m.end()) {
			return 0;
		}
		for (multimap<int, int>::iterator it = itr; it != m.end(); it++) {
			if (it->second < end) {
				end = it->second;
			}
		}
		m.erase(itr, m.end());
		cnt++;
	}
	long long price = cnt * p;
	return price;
}

int main() {
	cin.tie(0);
	cin.sync_with_stdio(0);
	
	cin >> N >> p;
	cin >> range.first >> range.second;
	pair<int, int> s;
	for (int i = 0; i < N; i++) {
		cin >> s.second >> s.first;
		if (s.second >= range.second||s.first<=range.first) {
			continue;
		}
		m.insert(s);
	}
	cout<<school_anniversary();
	return 0;
}