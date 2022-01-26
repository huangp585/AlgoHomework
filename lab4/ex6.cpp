#include<bits/stdc++.h>
using namespace std;

long long N, input, Q, record = 0;
vector<long long> dp(1000001, INT_MAX);
void gali(vector<long long>& val, long long biggest) {
	dp[0] = 0;
	for (int j = 1; j <= biggest; j++) {
		for (auto v : val) {
			if (j - v >= 0) {
				dp[j] = min(dp[j], 1 + dp[j - v]);
			}
		}
	}
	return;
}

int main()
{
	cin.tie(0);
	cin.sync_with_stdio(0);
	cin >> N;
	vector<long long> val(N);//not sure whether it needs to be sort
	for (int i = 0; i < N; i++) {
		cin >> input;
		val[i] = input;
	}
	cin >> Q;
	vector<long long> pay(Q);
	long long biggest = 0;
	for (int i = 0; i < Q; i++) {
		long long sum = 0, bill;
		cin >> bill;
		for (int j = 1; j <= N; j++) {
			cin >> input;
			sum += val[j - 1] * input;
		}
		pay[i] = sum - bill;
		if (pay[i] > biggest) {
			biggest = pay[i];
		}
	}
	gali(val, biggest);
	for (int i = 0; i < Q; i++) {
		cout << dp[pay[i]] << "\n";
	}
	return 0;
}