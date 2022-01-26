#include <iostream>
#include <iomanip>
#include <algorithm>
#include <queue>
using namespace std;
class Game {
public:
    double c, p, inside, add;
    bool operator<(const Game&) const;
}tmp;
bool Game::operator<(const Game& x)const {
    if (this->add < x.add) return true;
    else return false;
}
priority_queue<Game, vector<Game>, less<Game>>fur;
double e = 0.000001;
int main(void) {
    cin.tie(0);
    cin.sync_with_stdio(0);
    int n, k;
    cin >> n >> k;
    for (int i = 0; i < n; i++) {
        int C, P;
        cin >> C >> P;
        tmp.c = (double)C;
        tmp.p = (double)P;
        tmp.inside = 0.0;
        double score;
        if (P == 0) score = tmp.c;
        else score = tmp.c / tmp.p;
        tmp.add = (tmp.inside + 1.0) * (tmp.c / (tmp.p + 1.0)) - (tmp.inside) * score;
        fur.push(tmp);
    }
    // 對 每站上去一個人所能增加的分數 Greedy
    int i = 0;
    double cur = 0.0;
    while (i < k) {
        tmp = fur.top();
        fur.pop();
        cur += tmp.add;
        tmp.p += 1.0;
        tmp.inside += 1.0;
        double score;
        if (tmp.p - 0.0 < e) score = tmp.c;
        else score = tmp.c / tmp.p;
        tmp.add = (tmp.inside + 1.0) * (tmp.c / (tmp.p + 1.0)) - (tmp.inside) * score;
        fur.push(tmp);
        i++;
    }
    cout << setprecision(10) << cur << '\n';
    return 0;
}