#include<bits/stdc++.h>
using namespace std;

vector<vector<pair<long long, long long>>> adj;
vector<long long> dp, siz,uset;

struct Edge {
    long long u, v, wt;
    friend bool operator<(const Edge& e1, const Edge& e2) {
        return e1.wt < e2.wt;
    }
};

long long findSet(long long u) {
    if (uset[u] == -1) return u;
    return uset[u] = findSet(uset[u]);
}

bool kruskal(const vector<Edge>& edges, long long n) {
    uset.assign(n + 1, -1);
    vector<Edge> spanTree;
    long long cost = 0, root1, root2;
    for (auto e : edges) {
        root1 = findSet(e.u);
        root2 = findSet(e.v);
        if (root1 != root2) {
            cost = (cost + e.wt) % 1000000007;
            uset[root1] = root2;
            adj[e.u].push_back({ e.v,e.wt });
            adj[e.v].push_back({ e.u,e.wt });
            spanTree.push_back(e);
        }
    }

    if (spanTree.size() != n - 1) {
        cout << "-1";
        return false;
    }
    else {
        cost = (cost * 2) % 1000000007;
        cout << cost << " ";
    }
    return true;
}

void dfs1(long long u, long long f) {
    for (auto p : adj[u]) {
        long long v = p.first, l = p.second;
        if (v == f) continue;
        dfs1(v, u);
        dp[u] = (dp[u] + (dp[v] + (siz[v] * l) % 1000000007) % 1000000007) % 1000000007;
        siz[u] += siz[v];
    }
    return;
}

void dfs2(long long u, long long f, long long n) {
    for (auto p : adj[u]) {
        long long v = p.first, l = p.second;
        if (v == f) continue;
        dp[v] = (dp[u] + (l * (n - 2 * siz[v] % 1000000007)) % 1000000007) % 1000000007;
        dfs2(v, u, n);
    }
    return;
}

void sumOfDistance(long long n) {
    dp.resize(n + 1, 0);
    siz.resize(n + 1, 1);
    dfs1(1, -1);
    dfs2(1, -1, n);

    long long sum = 0;
    for (auto i : dp) {
        sum = (sum + i) % 1000000007;
    }
    cout << sum;
    return;
}

int main() {

    cin.tie(0);
    cin.sync_with_stdio(0);

    long long N, M;
    cin >> N >> M;

    vector<Edge> edges(M);

    for (int i = 0; i < M; i++) {
        cin >> edges[i].u >> edges[i].v >> edges[i].wt;
    }
    sort(edges.begin(), edges.end());
    adj.resize(N + 1);
    if (!kruskal(edges, N)) {
        return 0;
    }
    else {
        sumOfDistance(N);
    }
    return 0;
}



