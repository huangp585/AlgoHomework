#include <iostream>
#include <vector> 
#include <algorithm>
using namespace std;
vector<int> v;

long long num_oper(int left, int right) {
	vector<int> tmp1, tmp2;
	long long tmp_cnt = 0;
	int mid = (right + left) / 2;
	for (int i = left; i <= mid; i++) {
		tmp1.push_back(v[i]);
	}
	for (int i = mid+1; i <= right; i++) {
		tmp2.push_back(v[i]);
	}

	for (int i = right; i >= left; i--) {
		if (tmp1.empty()) {
			v[i] = tmp2.back();
			tmp2.pop_back();
		}
		else if (tmp2.empty()) {
			v[i] = tmp1.back();
			tmp1.pop_back();
		}
		else if (tmp1.back() >= tmp2.back()) {
			v[i] = tmp1.back();
			tmp1.pop_back();
		}
		else{
			v[i] = tmp2.back();
			tmp2.pop_back();
		}
	}

	while (left <= right) {
		tmp_cnt += v[right--] - v[left++];
	}
	return tmp_cnt;
}

long long goodSequence(int start, int end) {
	if (end-start < 2) {
		return 0;
	}
	int mid = (end+start) / 2;
	long long left_final = goodSequence(start, mid);
	long long right_final = goodSequence(mid + 1, end);
	long long left_cnt = num_oper(start,mid);
	long long right_cnt = num_oper(mid + 1, end);
	return min(left_final + right_cnt, right_final + left_cnt);
}

int main() {
	cin.tie(0);
	cin.sync_with_stdio(0);
	int N, input;
	cin >> N;
	for (int i = 0; i < N; i++) {
		cin >> input;
		v.push_back(input);
	}
	cout<<goodSequence(0,N-1);
	return 0;
}