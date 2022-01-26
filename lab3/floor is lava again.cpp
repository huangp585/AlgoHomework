#include <iostream>
#include <vector>
#include <map>
#include <iomanip>

using namespace std;

vector<double> c1, p;
int N, k;
multimap<double, int> m;
multimap<double, int>::iterator itr;
vector<double> kp(5000005, 0);

void lava() {
    double sum = 0;
    for (int i = 0; i < k; i++) {
        itr = m.end();
        itr--;
        int index = itr->second;
        sum += itr->first;
        p[index]++; kp[index]++;
        double new_cost = c1[index] / (p[index] + 1);
        new_cost=(new_cost/p[index])*(p[index]-kp[index]);
        m.insert({ new_cost, itr->second });
        m.erase(itr);
    }
    cout << fixed;
    cout << setprecision(6) << sum<<"\n";
    return;
}

int main() {
    cin.tie(0);
    cin.sync_with_stdio(0);

    cin >> N >> k;
    double input1, input2;
    double earn;
    for (int i = 0; i < N; i++) {
        cin >> input1 >> input2;
        c1.push_back(input1);
        p.push_back(input2);
        earn = input1 / (input2 + 1);
        m.insert({ earn, i });
    }
    lava();
    return 0;
}