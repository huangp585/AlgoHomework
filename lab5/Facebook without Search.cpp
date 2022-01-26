#include<bits/stdc++.h>
using namespace std;

//using DSU
int find_root(vector<int>& root, int x) {
    if (root[x] == x) return x;
    else {
        return root[x] = find_root(root, root[x]);
    }
}

void union_edge(vector<int>& root, int x, int y) {
    int root_x = find_root(root, x);
    int root_y = find_root(root, y);
    root[root_x] = root_y;
}

int main() {
    cin.tie(0);
    cin.sync_with_stdio(0);

    int N, M, Q;
    cin >> N >> M >> Q;

    //ªì©l¤Æroot
    vector<int> root(N, 0);
    for (int i = 0; i < N; i++) {
        root[i] = i;
    }

    //read M
    set<pair<int,int>> adj;
    for (int i = 0; i < M; i++) {
        int v, u;
        cin >> v >> u;
        if (v < u) {
            adj.insert({ v,u });
        }
        else {
            adj.insert({ u,v });
        }
    }

    //read Q delete Q from M
    vector<char> v1(Q);
    vector<pair<int, int>> sec;
    for (int i = 0; i < Q; i++) {
        int v, u;
        cin >> v1[i] >> v >> u;
        //construct pair
        pair<int, int> p;
        if (v < u) {
            p = make_pair(v, u);
        }
        else {
            p = make_pair(u, v);
        }
        sec.push_back(p);

        if (v1[i] == 'U') {
            if (adj.count(p)) {
                adj.erase(p);
            }
        }
    }

    //build graph
    for (auto p:adj) {
        int v = p.first;
        int u = p.second;
        union_edge(root, v, u);
    }

    //add Q edge and store to stack
    stack<string> ans;
    while (!sec.empty()) {
        char c = v1.back(); v1.pop_back();
        auto p = sec.back(); sec.pop_back();
        int v = p.first, u = p.second;
        if (c == 'A') {
            int root_v = find_root(root, v);
            int root_u = find_root(root, u);
            if (root_v == root_u) {
                ans.push("YES");
            }
            else {
                ans.push("NO");
            }
        }
        else {
            union_edge(root, u, v);
        }
    }


    //output ans
    while (!ans.empty()) {
        cout << ans.top() << "\n";
        ans.pop();
    }
    return 0;
}
