#include<bits/stdc++.h>
using namespace std;

long long T,N,M,K,F,S,f_lower,f_upper,s_lower,s_upper;
vector<long long> uset;
struct Edge{
    long long u,v;
};

long long findSet(long long u){
    if(uset[u]==-1) return u;
    return uset[u]=findSet(uset[u]);
}

long long spanningTree(vector<Edge> &edges){
    uset.assign(N,-1);
    long long cnt=0, root1, root2;
    for(auto e:edges){
        root1=findSet(e.u);
        root2=findSet(e.v);
        if(root1!=root2){
            uset[root1]=root2;
            cnt++;
        }
    }
    return cnt;
}

void checking(){
    for(int i=f_upper;i>=f_lower;i--){
        int j=N-1-i;
        long long tmp=i*F+j*S;
        if(tmp==K && j>=s_lower && j<= s_upper){
            cout<<"Yes\n";
            return;
        }
    }
    cout<<"No\n";
    return;
}

int main(){
    cin.tie(0);
    cin.sync_with_stdio(0);

    cin>>T;
    for(int i=0;i<T;i++){
        vector<Edge> adj, adj_f, adj_s;
        cin>>N>>M>>K>>F>>S;
        for(int j=0; j<M;j++){
            Edge e; char c;
            cin>>e.u>>e.v>>c;
            adj.push_back(e);
            if(c=='F') adj_f.push_back(e);
            else adj_s.push_back(e);
        }
        if(spanningTree(adj)!=N-1){
            cout<<"No\n";
        }
        else{
            f_upper=0,f_lower=0,s_lower=0,s_upper=0;
            f_upper=spanningTree(adj_f);
            s_upper=spanningTree(adj_s);
            f_lower=N-1-s_upper;
            s_lower=N-1-f_upper;
            if(f_upper<f_lower) swap(f_upper, f_lower);
            if(s_upper<s_lower) swap(s_upper, s_lower);
            checking();
        }
    }
    return 0;
}
