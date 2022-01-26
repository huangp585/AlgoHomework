#include<bits/stdc++.h>
using namespace std;


vector<long long> v;
long long N;

void LIS(vector<long long>& ans) {
	vector<long long> lis(1, -1);
	long long len = 0;
	lis.push_back(v[0]); len = 1; ans.push_back(1);
	for (int i = 1; i < N; i++) {
		if (v[i] > lis.back()) {
			lis.push_back(v[i]);
			ans.insert(ans.end(), i - ans.size(), len);
			len++;
			ans.push_back(len);
		}
		else {
			vector<long long>::iterator itr = lower_bound(lis.begin(), lis.end(), v[i]);//最接近但比他大的
			*itr = v[i];
		}
	}
	ans.insert(ans.end(), N - ans.size(), len);
	return;
}

void LDS(vector<long long>& ans) {
	vector<long long> lds(1, LONG_MAX);
	long long len = 0;
	lds.push_back(v[0]); len = 1; ans.push_back(1);
	for (int i = 1; i < N; i++) {
		if (v[i] < lds.back()) {
			lds.push_back(v[i]);
			ans.insert(ans.end(), i - ans.size(), len);
			len++;
			ans.push_back(len);
		}
		else {
			vector<long long>::iterator itr = lower_bound(lds.begin(), lds.end(), v[i], greater<long long>());//最接近但比他小
			*itr = v[i];
		}
	}
	ans.insert(ans.end(), N - ans.size(), len);
	return;
}

long long add(vector<long long>& a, vector<long long>& b) {
	long long max_num = 0;
	for (int i = 0; i < N; i++) {
		a[i] += b[i];
		if (a[i] > max_num) {
			max_num = a[i];
		}
	}
	return max_num - 1;
}

int main() {
	cin.tie(0);
	cin.sync_with_stdio(0);

	cin >> N;
	long long input;
	for (int i = 0; i < N; i++) {
		cin >> input;
		v.push_back(input);
	}
	vector<long long> lis1, lis2, lds1, lds2;
	LIS(lis1);
	reverse(v.begin(), v.end());
	LIS(lis2);
	reverse(lis2.begin(), lis2.end());

	reverse(v.begin(), v.end());
	LDS(lds1);
	reverse(v.begin(), v.end());
	LDS(lds2);
	reverse(lds2.begin(), lds2.end());

	cout << max(add(lis1, lis2), add(lds1, lds2));
	return 0;
}