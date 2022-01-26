#include<bits/stdc++.h>
using namespace std;

/*找出三個區間，return最大reward*/


long long N;
vector<long long> sum;//sub-array sum
vector<long long> v;
vector<vector<long long>> dp;

long long reward(int left, int right) {
    if (dp[left][right] != LONG_MIN) {
        return dp[left][right];
    }
    long long max_re = LONG_MIN;
    for (int i = left; i < right - 1; i += 2) {//i和j都指到區間內最後一元素
        for (int j = i + 1; j < right; j += 2) {
            long long left_sub, mid_sub, right_sub;
            long long past_reward, cur_reward, total_reward;
            left_sub = reward(left, i);
            mid_sub = reward(i + 1, j);
            right_sub = reward(j + 1, right);
            past_reward = left_sub + mid_sub + right_sub;

            long long left_val, mid_val, right_val;
            left_val = sum[i + 1] - sum[left];
            mid_val = sum[j + 1] - sum[i + 1];
            right_val = sum[right + 1]-sum[j+1];
            cur_reward = left_val * right_val - mid_val;

            total_reward = past_reward + cur_reward;
            if (total_reward > max_re) {
                max_re = total_reward;
            }
        }
    }
    dp[left][right] = max_re;

    return dp[left][right];
}

void initialization() {
    sum.push_back(0);
    for (int i = 0; i < N; i++) {
        sum.push_back(sum.back() + v[i]);
    }

    vector<long long> tmp(N, LONG_MIN);
    for (int i = 0; i < N; i++) {
        dp.push_back(tmp);
    }
    for (int i = 0; i < N; i++) {
        dp[i][i] = 0;
    }

    return;
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
    initialization();
    cout << reward(0, N - 1);
    return 0;
}
