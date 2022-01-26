// Example program
#include <iostream>
#include <vector>
using namespace std;

vector<vector<int>> v;

void add_element(int& a, int& x) {
    v[a].push_back(x);
    return;
}

void check_date(int& a, int& y) {
    if (y >= v[a].size()) {
        cout << "-1\n";
        return;
    }
    cout << v[a][y] << "\n";
}

void operation(int choice, int& a, int& x, int& y) {

    if (choice == 1) {
        cin >> a >> x;
        add_element(a, x);
    }
    else {
        cin >> a >> y;
        check_date(a, y);
    }

}

int main()
{
    cin.tie(0);
    cin.sync_with_stdio(0);
    int N, Q;
    int choose, a, x, y;//"choose" is a or b
    vector<int> vv;

    cin >> N >> Q;

    for (int i = 0; i < N; i++) {
        v.push_back(vv);
    }

    for (int i = 0; i < Q; i++) {
        cin >> choose;
        operation(choose, a, x, y);
    }
}
