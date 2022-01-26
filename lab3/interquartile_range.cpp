#include <iostream>
#include <set>
#include <iomanip>

using namespace std;

long long num, ssize=0, sub_size=0;
bool flag = true;
double Q1=0,Q3=0,IQR=0;
multiset<long long> s;
multiset<long long>::iterator itr_s1;
multiset<long long>::iterator itr_s2;

void output() {
    if (ssize == 1) {
        cout << "0\n";
        return;
    }
    sub_size = ssize / 2;
    if (sub_size % 2) {
        Q1 = *itr_s1;
        Q3 = *itr_s2;
    }
    else {
        Q1 = *itr_s1 + *next(itr_s1);
        Q1 = Q1 / 2;
        Q3 = *itr_s2 + *next(itr_s2);
        Q3 = Q3 / 2;
    }
    IQR= Q3 - Q1;
    long long integer = IQR;
    if (!(integer - IQR)) {
        cout << fixed;
        cout << setprecision(0) << IQR << "\n";
    }
    else {
        cout << fixed;
        cout << setprecision(1) << IQR << "\n";
    }
    return;
}

void interquartile_range() {
    if (flag) {
        s.insert(num);
        ssize++;
        itr_s1 = s.begin();
        itr_s2 = itr_s1;
        flag = false;
        return;
    }

    sub_size = ssize / 2;
    if (num<*itr_s1) {
        s.insert(s.begin(),num);
        if (ssize % 2) {
            if (!sub_size)itr_s1--;
            else if (sub_size % 2) {
                itr_s1--;
                itr_s2--;
            }
            else;
        }
        else itr_s1--;
    }
    else if(num>=*itr_s2){
        s.insert(next(itr_s2),num);
        if (ssize % 2) {
            if (!sub_size) itr_s2++;
            else if (!(sub_size % 2)) {
                itr_s1++;
                itr_s2++;
            }
            else;
        }
        else itr_s2++;
    }
    else {
        s.insert(next(itr_s1),num);
        if (ssize % 2) {
            if (sub_size % 2) {
                itr_s2--;
            }
            else itr_s1++;
        }
        else;
    }
    ssize++;
    return;
}

int main() {
    cin.tie(0);
    cin.sync_with_stdio(0);

    while (cin >> num) {
        if (num == 0) return 0;
        else {
            interquartile_range();
            output();
        }
    }
}