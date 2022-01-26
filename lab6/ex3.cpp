#include<bits/stdc++.h>

using namespace std;

struct Edge {
    long long v;
    long long flow, C, rev;
};

long long s, t, n;
vector<long long> level, start;
vector<vector<Edge>> adj;

void addEdge(long long u, long long v, long long c) {
    Edge a = { v, 0, c, adj[v].size() };
    Edge b = { u, 0, 0, adj[u].size() };

    adj[u].push_back(a);
    adj[v].push_back(b);
}

bool bfs() {
    level.assign(n, -1);
    level[s] = 0;
    queue<long long> q;
    q.push(s);
    while (!q.empty()) {
        long long u = q.front(); q.pop();
        for (auto& e : adj[u]) {
            if (level[e.v] < 0 && e.flow < e.C) {
                level[e.v] = level[u] + 1;
                q.push(e.v);
            }
        }
    }
    return level[t] < 0 ? false : true;
}

long long sendFlow(long long u, long long flow) {
    if (u == t) {
        return flow;
    }

    for (; start[u] < adj[u].size(); start[u]++) {
        Edge& e = adj[u][start[u]];
        if (level[e.v] == level[u] + 1 && e.flow < e.C) {
            long long curr_flow = min(flow, e.C - e.flow);
            long long temp_flow = sendFlow(e.v, curr_flow);

            if (temp_flow > 0) {
                e.flow += temp_flow;
                adj[e.v][e.rev].flow -= temp_flow;
                return temp_flow;
            }
        }
    }
    return 0;
}


long long dinicMaxFlow() {
    long long total = 0, flow;
    while (bfs()) {
        start.assign(n, 0);
        while (flow = sendFlow(s, LONG_MAX)) {
            total += flow;
        }
    }
    return total;
}

int main() {
    cin.tie(0);
    cin.sync_with_stdio(0);

    long long F, N, M;
    cin >> F >> N >> M;
    n = 1 + F + 2 * N + M + 1;
    adj.resize(n); s = 0; t = n - 1;

    //點與點之間，非車
    long long start_index = 1;
    long long inter_index = 1 + F + N + M;
    long long capacity;
    for (long long i = 0; i < F; i++) {
        cin >> capacity;
        addEdge(0, i + start_index, capacity);
    }
    start_index += F;
    for (long long i = 0; i < N; i++) {
        cin >> capacity;
        addEdge(i + start_index, i + inter_index, capacity);
    }

    start_index += N;
    for (long long i = 0; i < M; i++) {
        cin >> capacity;
        addEdge(i + start_index, n - 1, capacity);
    }

    long long C, T, a, b, flow;
    cin >> C;
    for (long long i = 0; i < C; i++) {
        cin >> a >> b >> flow;
        b += F;
        addEdge(a, b, flow);
    }

    cin >> T;
    for (int i = 0; i < T; i++) {
        cin >> a >> b >> flow;
        a += (F + N + M); b += (F + N);
        addEdge(a, b, flow);
    }

    long long limit;
    cin >> limit;
    long long ans = dinicMaxFlow();
    cout << min(limit, ans);

    return 0;
}
