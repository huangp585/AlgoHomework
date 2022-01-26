#include<bits/stdc++.h>

using namespace std;

struct Edge {
    int src, dst, wt;
};

vector<vector<pair<long long, int>>> adj, radj;
vector<long long> dist, rdist;
vector<Edge> edges;
int N, M, u, v, wt;

void dijkstra(vector<vector<pair<long long, int>>>& g, vector<long long> &d, int src, int dst) {
    set<pair<long long, int>> s;
    s.insert({ 0, src });
    d[src] = 0;

    while (!s.empty()) {
        auto p = s.begin();
        int u = p->second;
        s.erase(s.begin());
        for (auto& e : g[u]) {
            int v = e.second, l = e.first;
            if(d[v]==-1){
                d[v] = d[u] + l;
                s.insert({ d[v],v });
            }
            else if (d[u] + l < d[v]) {
                s.erase({ d[v],v });
                d[v] = d[u] + l;
                s.insert({ d[v],v });
            }
        }
    }
}

int main() {

    cin >> N >> M;
    adj.resize(N + 1); dist.assign(N + 1, -1);
    radj.resize(N + 1); rdist.assign(N + 1, -1);
    for (int i = 0; i < M; i++) {
        cin >> u >> v >> wt;
        adj[u].push_back({ wt, v });
        radj[v].push_back({ wt, u });
        edges.push_back({ u, v, wt });
    }

    dijkstra(adj, dist, 1, N);
    dijkstra(radj, rdist, N, 1);
    long long len = dist[N];

    long long deduct;
    for (auto& e : edges) {
        int u = e.src, v = e.dst;
        if (dist[u]==-1 || rdist[v]==-1) {
            cout << "-1\n";
        }
        else{
            long long l = e.wt;
            long long cur = dist[u] + rdist[v] + l;
            deduct = cur-len;
            if(deduct > l){
                cout << "-1\n";
            }
            else {
                cout << deduct << "\n";
            }
        }
    }

    return 0;
}
