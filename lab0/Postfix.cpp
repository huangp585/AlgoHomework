// Example program
#include <iostream>
#include <vector>
#include <string>

using namespace std;

long long a;//operands
vector<long long> v1;//operands

void calculation(string& op) {
	int num = v1.size() - 2;
	if (op == "+") {
		a = (v1[num] + v1[num + 1]) % 1000000007;
		v1.pop_back();
		v1.pop_back();
		v1.push_back(a);
		return;
	}
	a = (v1[num] % 1000000007) * (v1[num + 1] % 1000000007);
	v1.pop_back();
	v1.pop_back();
	v1.push_back(a);
}

int main() {
	string s;
	while (cin >> s) {//using while(cin) cause " " is a split
		if (s == "+" || s == "*") {
			calculation(s);
		}
		else {
			a = stoi(s);
			v1.push_back(a);
		}
	}
	cout << v1[0] % 1000000007;
	return 0;
}