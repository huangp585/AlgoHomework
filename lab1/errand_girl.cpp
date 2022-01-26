// Example program
#include <iostream>
#include <deque>
#include <algorithm>
using namespace std;



long long countTimes(deque<long long>& d,long long l) {
	long long sum;
	long long times = 0;
	while (!d.empty()) {
		if (d.size() == 1) {
			times++;
			return times;
		}
		sum = d.front() + d.back();
		if (sum > l) {
			times++;
			d.pop_back();
			continue;
		}
		times++;
		d.pop_front();
		d.pop_back();
	}
	return times;
}

int main(){
	deque<long long> d;
	long long n, l, k,book;
	cin >> n >> l >> k;
	for (int i = 0; i < n; i++) {
		cin >> book;
		d.push_back(book);
	}
	sort(d.begin(),d.end());
	long long cost=countTimes(d,l)*k*2;
	cout << cost;
	return 0;
}
