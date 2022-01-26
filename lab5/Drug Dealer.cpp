#include<bits/stdc++.h>
using namespace std;

int T, N, M, S;
vector<vector<int>> adj;
vector<int> cop_pos, hide_pos, dist;
vector<bool> status, visited;

void bfs(queue<int> &q) {
    int cnt = 0;
    while (!q.empty()) {
        int q_size = q.size();
        for (int i = 0; i < q_size; i++) {
            int u = q.front(); q.pop();
            if (cnt < dist[u]) {
                dist[u] = cnt; status[u] = !status[u];
            }
            for (auto v : adj[u]) {
                if (!visited[v]) {
                    visited[v] = true;
                    q.push(v);
                }
            }
        }
        cnt++;
    }
}

void escape() {
    status.assign(N + 1, true);
    visited.assign(N + 1, false);
    dist.assign(N + 1, INT_MAX);

    //do cop's bfs
    queue<int> q;
    for (auto u : cop_pos) {
        visited[u]=true;
        q.push(u);
    }
    bfs(q);
    //thief bfs
    visited.assign(N + 1, false);
    visited[S]=true;
    q.push(S);
    bfs(q);

    //check
    for (auto u : hide_pos) {
        if (status[u]) {
            cout << "Yes\n";
            return;
        }
    }
    cout << "No\n";
    return;
}

int main() {
    cin.tie(0);
    cin.sync_with_stdio(0);

    cin >> T;
    for (int i = 0; i < T; i++) {
        cin >> N >> M >> S;
        adj.assign(N + 1,vector<int>());
        //read M edges
        for (int j = 0; j < M; j++) {
            int u, v;
            cin >> u >> v;
            adj[u].push_back(v);
            adj[v].push_back(u);
        }

        //read cop's pos
        int cop_num;
        cin >> cop_num;
        cop_pos.assign(cop_num,0);
        for (int j = 0; j < cop_num; j++) {
            cin >> cop_pos[j];
        }
        //read hideouts
        int hide_num;
        cin >> hide_num;
        hide_pos.assign(hide_num,0);
        for (int j = 0; j < hide_num; j++) {
            cin >> hide_pos[j];
        }
        //go into counting
        escape();
    }
    return 0;
}
