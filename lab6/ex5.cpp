#include<bits/stdc++.h>

using namespace std;

struct Edge {
    int src, dst;
    long long wt;
    friend bool operator<(Edge e1, Edge e2) {
        return e1.wt < e2.wt;
    }
};

int N, M, negcnt = 0;
vector<Edge> edges;

bool bellmanFord(int k) {//小於等於k
    vector<long long> dist(N, 1e18);
    bool updated;
    for (int i = 0; i < N - 1; i++) {
        updated = false;
        for (int j = k + 1; j < M; j++) {
            int src = edges[j].src, dst = edges[j].dst;
            long long wt = edges[j].wt;
            if (dist[src] + wt < dist[dst]) {
                dist[dst] = dist[src] + wt;
                updated = true;
            }
        }
        if (!updated) return false;//no negative cycle
    }

    for (int i = k + 1; i < M && updated == true; i++) {
        int src = edges[i].src, dst = edges[i].dst;
        long long wt = edges[i].wt;
        if (dist[src] + wt < dist[dst]) {
            return true;
        }
    }
    return false;
}

int binarySearch(int left, int right) {
    int middle = (left + right) / 2;
    if (left > right) {
        return left;
    }
    if (!bellmanFord(middle)) {//no negative cycle
        return binarySearch(left, middle - 1);
    }
    else {
        return binarySearch(middle + 1, right);
    }
}

int main() {
    cin.tie(0);
    cin.sync_with_stdio(0);

    cin >> N >> M;
    for (int i = 0; i < M; i++) {
        Edge e;
        cin >> e.src >> e.dst >> e.wt;
        edges.push_back(e);
        if (e.wt < 0) {
            negcnt++;
        }
    }
    sort(edges.begin(), edges.end());

    if (bellmanFord(-1)) {
        int index = binarySearch(0, negcnt - 1);
        if (edges[index].wt == edges[negcnt - 1].wt) {
            cout << "NO WAY BACK";
        }
        else {
            cout << edges[index].wt;
        }
    }
    else {
        cout << "GO AHEAD";
    }

    return 0;
}
