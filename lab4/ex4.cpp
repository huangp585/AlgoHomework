#include<bits/stdc++.h>
using namespace std;

vector<long long> val(1,0);
vector<long long> cost(1,0);

long long Cipmylo(long long num_sci) {
    vector<vector<long long>> dp(2, vector<long long>(num_sci + 1, 0));
    long long n = val.size()-1;
    for (int i = 1; i <= n;i++) {
        int row;
        if (i % 2) {
            row = 1;
        }
        else row = 0;

        for (int j = 1; j <= num_sci; j++) {
            if (cost[i] <= j) {
                dp[row][j] = max(dp[!row][j], dp[!row][j - cost[i]] + val[i]);
            }
            else {
                dp[row][j] = dp[!row][j];
            }
        }
    }
    if (n % 2) {
        return dp[1][num_sci];
    }
    else return dp[0][num_sci];
}

int main() {
    cin.tie(0);
    cin.sync_with_stdio(0);

    long long N, M, S, input;
    cin >> N >> M >> S;

    vector<long long> tmp;
    for (int i = 0; i < N; i++) {
        cin >> input;
        tmp.push_back(input);
    }
    sort(tmp.begin(), tmp.end());


    long long sta, fin, num, max_year = 0, num_virus = 0;
    for (int i = 0; i < M; i++) {
        vector<long long> v(3, 0);
        cin >> sta >> fin >> num;
        v[0] = sta; v[1] = fin; v[2] = num;
        vector<long long>::iterator left_itr = lower_bound(tmp.begin(), tmp.end(), v[0]);
        vector<long long>::iterator right_itr = upper_bound(tmp.begin(), tmp.end(), v[1]);

        long long len = right_itr-left_itr;
        if (len == 0) continue;
        val.push_back(len);
        cost.push_back(v[2]);
        max_year += len;
        num_virus += v[2];
    }

    long long no_virus_years = tmp.size() - max_year;
    S = min(S, num_virus);
    cout << Cipmylo(S) + no_virus_years;
    return 0;
}
