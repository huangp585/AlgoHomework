#include<bits/stdc++.h>

using namespace std;

int N, M;
vector<vector<long long>> dp;

void floydWarshall(){
    for(int k=0;k<N;k++){
        for(int i=0;i<N;i++){
            for(int j=0;j<N;j++){
                if(dp[i][k]!=LONG_MAX && dp[k][j]!=LONG_MAX
                   && dp[i][k]+dp[k][j]<dp[i][j]){
                    dp[i][j]=dp[i][k]+dp[k][j];
                }
            }
        }
    }
    return;
}

int main(){
    cin.tie(0);
    cin.sync_with_stdio(0);

    cin>>N>>M;
    dp.resize(N, vector<long long>(N,LONG_MAX));
    for(int i=0;i<M;i++){
        int u,v,wt;
        cin>>u>>v>>wt;
        if(dp[u][v]>wt){
            dp[u][v]=wt;
        }
    }

    floydWarshall();
    int K;
    cin>>K;
    for(int i=0;i<K;i++){
        cin>>N>>M;
        if(dp[N][M]!=LONG_MAX){
            cout<<dp[N][M]<<"\n";
        }
        else{
            cout<<"-1\n";
        }
    }
    return 0;
}
