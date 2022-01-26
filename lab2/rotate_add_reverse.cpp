#include <iostream>
#include <vector>
#include <algorithm>
#include <cmath>

using namespace std;
vector<int> a, b, output;
vector<int>& Rotate(int n);

vector<int>& Reverse(int n) {
	a=Rotate(n);
	reverse(a.begin(), a.end());
	return a;
}

vector<int>& add(int n) {
	b = Rotate(n);
	int num = pow(2, n);
	int s = b.size();
	for (int i = 0; i < s; i++) {
		b[i] += num;
	}
	return b;
}

vector<int>& Rotate(int n) {
	vector<int> tmp,a1,b2;
	if (n == 0) {
		tmp.push_back(1);
		output = tmp;
		return output;
	}
	a1 = Reverse(n - 1);
	b2 = add(n - 1);
	output = a1;
	output.insert(output.end(), b2.begin(), b2.end());
	int num;
	num = pow(2, n - 1);
	rotate(output.begin(), output.begin() + num, output.end());
	return output;
}

int main() {
	int N;
	cin >> N;

	Rotate(N);
	int s = output.size();
	for (int i = 0; i < s; i++) {
		cout << output[i] << " ";
	}
	return 0;
}