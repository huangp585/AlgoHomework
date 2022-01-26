#include <iostream>
#include <vector>

using namespace std;

vector<int> inorder, postorder, sen;
vector<int> inorder_map;
int N, cnt = 0, postIndex;

struct TreeNode {
	int seniority;
	TreeNode* left;
	TreeNode* right;
	TreeNode(int n) {
		seniority = n;
		left = NULL;
		right = NULL;
	}
};

TreeNode* buildtree(int inStart, int end) {
	if (inStart > end) {
		return NULL;
	}
	int s = postorder[postIndex--];
	TreeNode* node = new TreeNode(sen[s]);
	int index = inorder_map[s];
	node->right = buildtree(index + 1, end);
	node->left = buildtree(inStart, index - 1);

	if (node->left) {
		int left_s = node->left->seniority;
		if (node->seniority < left_s) {
			cnt++;
		}
	}
	if (node->right) {
		int right_s = node->right->seniority;
		if (node->seniority < right_s) {
			cnt++;
		}
	}
	return node;
}

void getData(vector<int>& v) {
	int input;
	if (v == inorder_map) {
		for (int i = 0; i < N + 1; i++) {
			inorder_map.push_back(-1);
		}
	}
	else if (v == inorder) {
		for (int i = 0; i < N; i++) {
			cin >> input;
			inorder.push_back(input);
			inorder_map[input] = i;
		}
	}
	else {
		for (int i = 0; i < N; i++) {
			cin >> input;
			v.push_back(input);
		}
	}
}

int main() {
	cin.tie(0);
	cin.sync_with_stdio(0);
	cin >> N;
	postIndex = N - 1;
	sen.push_back(0);
	getData(inorder_map);
	getData(sen);
	getData(inorder);
	getData(postorder);
	buildtree(0, N - 1);
	cout << cnt;
	return 0;
}