#include<bits/stdc++.h>
using namespace std;

int main() {
    cin.tie(0);
    cin.sync_with_stdio(0);

    long long N,T,input;
    cin>>N>>T;
    vector<vector<long long>> v(T);
    vector<vector<long long>> dp(T,vector<long long> (N,0));

    for(int i=0;i<T;i++){
        for(int j=0;j<N;j++){
            cin>>input;
            v[i].push_back(input);
        }
    }

    for(int i=0;i<N;i++){
        dp[T-1][i]=v[T-1][i];
    }

    for(int i=T-2;i>=0;i--){
        for(int j=0;j<N;j++){
            if(j==0){
                if (j + 1 > N - 1) {
                    dp[i][j] = v[i][j] + dp[i+1][j];
                }
                else {
                    dp[i][j] = v[i][j] + max(dp[i + 1][j], dp[i + 1][j + 1]);
                }
            }
            else if(j==N-1){
                dp[i][j]=v[i][j]+max(dp[i+1][j],dp[i+1][j-1]);
            }
            else{
                long long tmp=max(dp[i+1][j-1],dp[i+1][j]);
                tmp=max(dp[i+1][j+1],tmp);
                dp[i][j]=v[i][j]+tmp;
            }
        }
    }

    for(int i=0;i<N;i++){
        cout<<dp[0][i]<<" ";
    }
    return 0;
}
