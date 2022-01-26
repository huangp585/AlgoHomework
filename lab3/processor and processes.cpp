#include<iostream>
#include<set>
#include<map>
#include<queue>
#include<deque>
#include<vector>
#include<algorithm>
#include<unordered_map>

using namespace std;
int N, C, q;
unordered_map<int, deque<int>> m;
queue<int> process;
set<int> core;
int zero = 500002;
map<int,int> core_index;
set<int>::iterator itr;

int mini_switch = 0;

int processor(set<int>&c) {
	for (int i = 0; i < q; i++) {
		int cur = process.front();
		itr = core.find(cur);
		if (core.size()!=C&&itr==core.end()) {
			core.insert(cur);
			mini_switch++;
		}
		else {
			if (itr != core.end());
			else {
				map<int, int>::reverse_iterator last = core_index.rbegin();
				core.erase(last->second);
				core_index.erase(last->first);
				core.insert(cur);
				mini_switch++;
			}
		}
		m[cur].pop_front();
		if (m[cur].empty()) {
			core_index[zero++] = cur;
		}
		else {
			core_index[m[cur].front()] = cur;
		}
		process.pop();
	}
	return mini_switch;
}

int main() {
	cin.tie(0);
	cin.sync_with_stdio(0);

	cin >> N >> C >> q;
	int k;
	for (int i = 0; i < q; i++) {
		cin >> k;
		process.push(k);
		m[k].push_back(i);
	}
	cout << processor(core);
	return 0;
}