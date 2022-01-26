#include <iostream>
#include <algorithm>
#include <set>
#include <vector>
#include <map>
using namespace std;

set <pair<int, int>, greater<pair<int, int>>> core;
int pre[500005] = { 0 };
int order[500005] = { 0 }; // executing order
map <int, vector<int>> record; // 

int main(void) {
    cin.tie(0);
    cin.sync_with_stdio(0);
    int n, c, q;
    cin >> n >> c >> q;
    for (int i = 0; i < q; i++) {
        cin >> order[i];
        record[order[i]].emplace_back(i);
    }
    long long int cnt = 0;
    for (int i = 0; i < q; i++) {
        auto next = upper_bound(record[order[i]].begin(), record[order[i]].end(), i);
        if (core.empty()) {
            cnt++;
            if (next == record[order[i]].end()) core.insert(pair<int, int>{1000000007, order[i]});
            else core.insert(pair<int, int>{*next, order[i]});
            pre[order[i]] = i;
            continue;
        }
        //cout << "finding " << order[i] << " " << pre[order[i]] << endl;
        auto it = core.find(pair<int, int>{i, order[i]});
        if (it == core.end()) {
            if (core.size() == c) {
                it = core.begin();
                core.erase(it);
            }
            cnt++;
        }
        else core.erase(it); // it != core.end()

        if (next == record[order[i]].end()) core.insert(pair<int, int>{1000000007, order[i]});
        else core.insert(pair<int, int>{*next, order[i]});
        pre[order[i]] = i;
        //cout << "pre " << order[i] << " = " << pre[order[i]] << endl;
        //cout << "core" << endl;
        //for(auto j = core.begin(); j != core.end(); ++j) cout << j -> first << " " << j -> second << endl;
    }
    cout << cnt << '\n';
    return 0;
}