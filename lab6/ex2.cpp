#include<bits/stdc++.h>

using namespace std;

struct Edge{
    int v;//準備送往的點
    long long flow, C, rev;
};

vector<vector<Edge>> adj;
vector<int> level, start;
int N,s,t, num_Nodes;

void addEdge(int u, int v, long long c){
    Edge a={ v, 0, c, adj[v].size()};
    Edge b={ u, 0, 0, adj[u].size()};

    adj[u].push_back(a);
    adj[v].push_back(b);
}

bool bfs(){
    level.assign(num_Nodes, -1);
    level[s]=0;
    queue<int> q;
    q.push(s);
    while(!q.empty()){
        int u=q.front(); q.pop();
        for(auto &e:adj[u]){
            if(level[e.v]<0 && e.flow<e.C){
                level[e.v]=level[u]+1;
                q.push(e.v);
            }
        }
    }
    return level[t]<0?false:true;
}

long long sendFlow(int u, long long flow){
    if(u==t){
        return flow;
    }
    for(; start[u]<adj[u].size(); start[u]++){
        Edge &e=adj[u][start[u]];
        if(level[e.v]==level[u]+1 && e.flow<e.C){
            long long curr_flow=min(flow, e.C-e.flow);
            long long tmp_flow=sendFlow(e.v, curr_flow);

            if(tmp_flow>0){
                e.flow+=tmp_flow;
                adj[e.v][e.rev].flow-=tmp_flow;
                return tmp_flow;
            }
        }
    }
    return 0;
}

long long dinicMaxFlow(){
    long long total=0, flow;
    while(bfs()){
        start.assign(num_Nodes,0);
        while(flow=sendFlow(s, LONG_MAX)){
            total+=flow;
        }
    }
    return total;
}

int main(){
    cin.tie(0);
    cin.sync_with_stdio(0);

    cin>>N;
    num_Nodes=N+2;
    adj.resize(num_Nodes);
    s=0; t=num_Nodes-1;
    int capacity;
    for(int i=1;i<=N;i++){
        cin>>capacity;
        addEdge(s, i, capacity);
    }

    for(int i=1;i<=N;i++){
        cin>>capacity;
        addEdge(i, t, capacity);
    }

    int M;
    cin>>M;
    int x,y;
    for(int i=1;i<=M;i++){
        cin>>x>>y>>capacity;
        addEdge(x, y, capacity);
        addEdge(y, x, capacity);
    }

    long long min_cut=dinicMaxFlow();
    cout<<min_cut;

    return 0;
}
