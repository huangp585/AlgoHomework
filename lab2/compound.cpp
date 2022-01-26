#include <iostream>
#include <ctype.h>
#include <map>
#include <string>
using namespace std;

map<string, long long> one, two;
map<string, long long>::iterator itr;
string s;
int index = 0;

int check_num(int inStart) {
	int count_num = 1;
	int cnt_num = 0;
	string num;
	if (isdigit(s[inStart + cnt_num])) {
		while (isdigit(s[inStart + cnt_num])) {
			num += s[inStart + cnt_num];
			cnt_num++;
		}
		count_num = stoi(num);
		index = index + cnt_num;
	}
	return count_num;
}

string check_chemical(int inStart) {
	int cnt_num = 0;
	string che;
	che += s[inStart + cnt_num];
	cnt_num++;
	while (islower(s[inStart + cnt_num])) {
		che += s[inStart + cnt_num];
		cnt_num++;
	}
	index += cnt_num;
	return che;
}

void compound(int inStart, int end,int pre) {
	index = inStart + 1;
	int first = s.find("(", inStart+1);
	int last = s.rfind(")", end-1);
	long long brace_num; int cnt_brace=1; string brace;
	if (isdigit(s[end + cnt_brace])) {
		while (isdigit(s[end + cnt_brace])) {
			brace += s[end + cnt_brace];
			cnt_brace++;
		}
		brace_num = stoi(brace)*pre;
	}
	else {
		brace_num = 1*pre;
	}

	if (first == -1) {
		while (index < end) {
			string str; long long num;
			str = check_chemical(index);
			num = check_num(index);
			if (str.length() == 1) {
				one[str] += num * brace_num;
			}
			else {
				two[str] += num * brace_num;
			}
		}
		return;
	}

	else{
		string str; long long num;
		while (index < first) {
			str = check_chemical(index);
			num = check_num(index);
			if (str.length() == 1) {
				one[str] += num * brace_num;
			}
			else {
				two[str] += num * brace_num;
			}
		}

		compound(first, last,brace_num);

		while (!isalpha(s[index])) {
			index++;
			continue;
		}
		while (index < end) {
			str = check_chemical(index);
			num = check_num(index);
			if (str.length() == 1) {
				one[str] += num * brace_num;
			}
			else {
				two[str] += num * brace_num;
			}
		}
		return;
	}
	
}

void output() {
	long long cnt=0;
	cout << one.size() << "\n";
	for (itr = one.begin(); itr != one.end(); itr++) {
		cout << itr->first << ":" << itr->second << "\n";
		cnt++;
	}
	cout << two.size() << "\n";
	for (itr = two.begin(); itr != two.end(); itr++) {
		cout << itr->first << ":" << itr->second << "\n";
		cnt++;
	}
}

int main() {
	cin >> s;
	s = "(" + s + ")";
	compound(0,s.length()-1,1);//count chemical elements;
	output();//output ans
}
