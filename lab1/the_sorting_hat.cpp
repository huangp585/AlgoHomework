// Example program
#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

using namespace std;
int a[4][4];

struct Student {
	string name;
	int score[4];
};
int choose;
vector<Student> house[4];
bool cmp(Student s1, Student s2) {
	if (s1.score[a[choose][0]] != s2.score[a[choose][0]]) {
		return s1.score[a[choose][0]] > s2.score[a[choose][0]];
	}
	else {
		if (s1.score[a[choose][1]] != s2.score[a[choose][1]]) {
			return s1.score[a[choose][1]] > s2.score[a[choose][1]];
		}
		else {
			if (s1.score[a[choose][2]] != s2.score[a[choose][2]]) {
				return s1.score[a[choose][2]] > s2.score[a[choose][2]];
			}
			else {
				if (s1.score[a[choose][3]] != s2.score[a[choose][3]]) {
					return s1.score[a[choose][3]] > s2.score[a[choose][3]];
				}
				else {
					return s1.name < s2.name;
				}
			}
		}
	}
}

void ranking(vector<Student>& v, int index) {
	if (v.empty()) {
		return;
	}
	choose = index;
	sort(v.begin(), v.end(), cmp);
}

void result(vector<Student>& v) {
	if (v.empty()) {
		cout << " NO NEW STUDENTS";
		return;
	}
	for (int i = 0; i < v.size(); i++) {
		cout << "\n" << v[i].name;
	}
}

int main() {
	int n;
	string S[4];
	cin.tie(0);
	cin.sync_with_stdio(0);
	cin >> n;
	for (int i = 0; i < 4; i++) {
		cin >> S[i];
		for (int j = 0; j < 4; j++) {
			if (S[i][j] == 'G') {
				a[i][j] = 0;
			}
			else if (S[i][j] == 'H') {
				a[i][j] = 1;
			}
			else if (S[i][j] == 'R') {
				a[i][j] = 2;
			}
			else {
				a[i][j] = 3;
			}
		}
	}
	Student* stu = new Student[n];
	int max;
	for (int i = 0; i < n; i++) {
		cin >> stu[i].name;
		max = 0;
		for (int j = 0; j < 4; j++) {
			cin >> stu[i].score[j];
			if (stu[i].score[j] > stu[i].score[max])
				max = j;
		}
		house[max].push_back(stu[i]);
	}
	string ans[4];
	ans[0] = "GRYFFINDOR:";	ans[1] = "HUFFLEPUFF:";
	ans[2] = "RAVENCLAW:"; ans[3] = "SLYTHERIN:";
	for (int i = 0; i < 4; i++) {
		cout << ans[i];
		ranking(house[i], i);
		result(house[i]);
		cout << "\n";
	}
	return 0;
}