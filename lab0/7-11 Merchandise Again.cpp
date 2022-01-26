// Example program
#include <iostream>
#include <map>
#include <queue>


using namespace std;

map<int,priority_queue<int,vector<int>,greater<int>>> m;

void add_element(int& a, int& x) {
    priority_queue<int, vector<int>, greater<int>> q;
    if (m[a].empty()) {
        m.insert({ a,q });
        m[a].push(x);
        return;
    }
    m[a].push(x);
}

void check_date(int& a) {
    if (m[a].empty()) {
        cout << "-1\n";
        return;
    }
    cout << m[a].top() << "\n";
    m[a].pop();
}

int main()
{
    cin.tie(0);
    cin.sync_with_stdio(0);
    int Q;
    int choose, a, x;//"choose" is a or b

    cin >> Q;
    for (int i = 0; i < Q; i++) {
        cin >> choose;
        if (choose == 1) {
            cin >> a >> x;
            add_element(a, x);
        }
        else {
            cin >> a;
            check_date(a);
        }

    }
}
