#include<iostream>
#include<queue>
#include<string>
#include<sstream>
#include<map>
#include<math.h>
#include<iomanip>

using namespace std;

class node {
public:
	node* left_children = NULL,
		* right_children = NULL;
	int freq = 0, code = 0;
	string content;
	bool visited = false;
	bool operator<(const node & n1) const{
		if (freq != n1.freq)return (freq > n1.freq);
		else return content > n1.content;
	}
};

int N; 
vector<vector<string>> paragraph;
map<string, node> table;
priority_queue<node,vector<node>,cmp> leaf;

node* construct_node() {
	node *cur=new node;
	node *n1 = new node; node* n2 = new node;
	*n1 = leaf.top(); leaf.pop();  
	*n2 = leaf.top(); leaf.pop(); 
	if (table.count(n1->content)&&!table[n1->content].visited) {
		cur->left_children = &table[n1->content];
		table[n1->content].visited = true;
	}
	else cur->left_children = n1;
	if (table.count(n2->content)&&!table[n2->content].visited) {
		cur->right_children = &table[n2->content];
		table[n2->content].visited = true;
	}
	else cur->right_children = n2;

	if (n1->content < n2->content)cur->content = n1->content;
	else cur->content = n2->content;
	cur->freq = cur->left_children->freq + cur->right_children->freq;
	return cur;
}

void compress() {
	double before=0, after=0;
	double be_bit = ceil(log2(table.size()));
	for (int i = 0; i < N; i++) {
		before = 0, after = 0;
		for (int j = 0; j < paragraph[i].size(); j++) {
			after += table[paragraph[i][j]].code;
			before += be_bit;
		}
		double rate = after / before;
		cout << fixed;
		cout << setprecision(6) << rate << "\n";
	}
	return;
}

int cnt = 0;
void DFS(node *rear) {
	if (rear == NULL) return;
	cnt++;
	DFS(rear->left_children);
	cnt--;
	rear->code = cnt;
	cnt++;
	DFS(rear->right_children);
	cnt--;
}

void huffman() {
	while (leaf.size() != 1) {
		node* newNode = new node;
		newNode=construct_node();
		leaf.push(*newNode);
	}
	node* start = new node;
	*start=leaf.top();
	DFS(start);
	compress();
	return;
}

int main() {
	cin.tie(0);
	cin.sync_with_stdio(0);

	string s, word; 
	cin >> N;
	getline(cin, s);
	for (int i = 0; i < N; i++) {
		getline(cin, s);
		istringstream iss(s);
		vector<string> v;
		while (iss>>word) {
			v.push_back(word);
			if (!table.count(word)) {
				node cur;
				cur.freq++; cur.content = word;
				table.insert({ word,cur });
			}
			else {
				table[word].freq++;
			}
		}
		paragraph.push_back(v);
	}
	
	for (map<string, node>::iterator itr=table.begin();itr != table.end();itr++) {
		leaf.push(itr->second);
	}
	huffman();
	return 0;
}