#include<bits/stdc++.h>
using namespace std;

//照i-1列的可能討論
vector<long long> dp1(10000005,0);
vector<long long> dp2(10000005,0);
vector<long long> dp3(10000005,0);

void totem(long long n){
    //dp1:A, 2:B, 3:C
    dp1[1]=1;
    dp1[2]=1; dp2[2]=1; dp3[2]=1;

    for(int i=3;i<=n;i++){
        dp1[i]=(dp1[i-1]%1000000007+(dp2[i-1]%1000000007+dp3[i-1]%1000000007)%1000000007)%1000000007;
        dp2[i]=(dp1[i-1]%1000000007+dp3[i-1]%1000000007)%1000000007;
        dp3[i]=dp1[i-1]%1000000007;
    }
    return;
}

int main() {
    cin.tie(0);
    cin.sync_with_stdio(0);

    long long T;
    vector<long long> N;
    cin>>T;
    long long max_input=0;
    for(int i=0;i<T;i++){
        long long input; cin>>input;
        N.push_back(input);
        if(input>max_input){
            max_input=input;
        }
    }
    totem(max_input);

    for(int i=0;i<T;i++){
        long long cur=N[i];
        long long ans=(dp1[cur]%1000000007+(dp2[cur]%1000000007+dp3[cur]%1000000007)%1000000007)%1000000007;
        ans=(ans*4)%1000000007-3;
        cout<<ans<<"\n";
    }
    return 0;
}
