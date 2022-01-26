#include<bits/stdc++.h>
using namespace std;

class Graph {
private:

    int num_vertex;
    vector<vector<int>> adj, adj_rev, adj_SCC;
    vector<int> roots, component, dp;
	//正走
    void dfs1(vector<bool>& visited, stack<int>& s, int v) {
        visited[v] = true;
        for (auto u : adj[v]) {
            if (!visited[u]) {
                dfs1(visited, s, u);
            }
        }
        s.push(v);
        return;
    }
	//倒走
    void dfs2(vector<bool>& visited, int v) {
        visited[v] = true;
        component.push_back(v);
        for (auto u : adj_rev[v]) {
            if (!visited[u]) {
                dfs2(visited, u);
            }
        }
        return;
    }
	//正走SCC，找dp
    void dfs(vector<bool>& visited, int v) {
        visited[v] = true;
        int scc_num = dp[v];
        for (auto u : adj_SCC[v]) {
            if (!visited[u]) {
                dfs(visited, u);
            }
            dp[v] = max(dp[v], dp[u] + scc_num);
        }
    }

public:

    Graph(int n) :num_vertex(n), adj(n), adj_rev(n), adj_SCC(n), roots(n), dp(n) {};

    void addEdge(int v, int u) {
        adj[v].push_back(u);
        adj_rev[u].push_back(v);
    }

    void SCC() {
        vector<bool> visited(num_vertex, false);
        stack<int> s;
        for (int i = 0; i < num_vertex; i++) {
            if (!visited[i]) {
                dfs1(visited, s, i);
            }
        }

        visited.assign(num_vertex, false);
        while (!s.empty()) {
            int v = s.top(); s.pop();
            if (!visited[v]) {
                dfs2(visited, v);
                int root = component.front();
                dp[root] = component.size();
                for (auto u : component) {
                    roots[u] = root;
                }
                component.clear();
            }
        }

        for (int v = 0; v < num_vertex; v++) {
            for (auto u : adj[v]) {
                int root_v = roots[v];
                int root_u = roots[u];

                if (root_u != root_v) {
                    adj_SCC[root_v].push_back(root_u);
                }
            }
        }
        return;
    }

    int findLongestPath() {
        SCC();//做完SCC後，正走SCC graph
        vector<bool> visited(num_vertex, false);
        for (int i = 0; i < num_vertex; i++) {
            if (!visited[i]) {
                dfs(visited, i);
            }
        }
        int ans = 0;
        for (int i = 0; i < num_vertex; i++) {
            ans = max(ans, dp[i]);
        }
        return ans;
    }
};

int main() {

    cin.tie(0);
    cin.sync_with_stdio(0);

    int N, M;
    cin >> N >> M;

    Graph g(N);
    for (int i = 0; i < M; i++) {
        int v, u;
        cin >> v >> u;
        g.addEdge(v, u);
    }

    cout << g.findLongestPath();

    return 0;
}



