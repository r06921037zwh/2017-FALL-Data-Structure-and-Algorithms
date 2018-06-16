#include <iostream>
#include <algorithm>
#include <cmath>
#include <unordered_map>
#include <vector>
#include <string>
#include <queue>
using namespace std;

class GeneralTree;
class TreeNode {
public:
	int ID;
	int pos;
	TreeNode *parent;
	vector<TreeNode*> children;
	TreeNode() :parent(0), ID(0) {};
	TreeNode(int s, int Pos) :parent(0), ID(s), pos(Pos) {};

	friend class GeneralTree;
};
class GeneralTree {
public:
	TreeNode *root;         // 以root作為存取整棵樹的起點
	GeneralTree() :root(0) {};
	GeneralTree(TreeNode *node) :root(node) {};

	void Preorder(TreeNode *current, int N);
	//void Inorder(TreeNode *current);
	void Postorder(TreeNode *current, int N);
	void Levelorder();
};

void GeneralTree::Preorder(TreeNode *current, int N) {
	if (current) {                          // if current != NULL
		cout << current->ID << " ";
		for (int i = 0; i < current->children.size(); i++) {
			Preorder(current->children[i], N);
		}		
	}
}

int PostCount = 1;
void GeneralTree::Postorder(TreeNode *current, int N) {
	if (current) {                         // if current != NULL
		for (int i = 0; i < current->children.size(); i++) {
			Postorder(current->children[i], N);
		}
		std::cout << current->ID;
		if (PostCount < N) { cout << " "; }
		PostCount++;
	}
}

void GeneralTree::Levelorder() {
	std::queue<TreeNode*> q;
	q.push(this->root);                                     // 把root作為level-order traversal之起點
											                // 推進queue中
	while (!q.empty()) {                                    // 若queue不是空的, 表示還有node沒有visiting

		TreeNode *current = q.front();                      // 取出先進入queue的node
		q.pop();
		cout << current->ID << " ";                         // 進行visiting
		for (int i = 0; i < current->children.size(); i++) {
			if (current->children[i] != NULL) {             // 若leftchild有資料, 將其推進queue
				q.push(current->children[i]);
			}
		}
	}
}
bool compare(TreeNode* lhs, TreeNode* rhs) { 
	return lhs->pos < rhs->pos; 
}

int main() {
	ios_base::sync_with_stdio(false);
	cin.tie(0);
	int H;
	cin >> H;

	unordered_map<int, TreeNode*>::const_iterator parent;
	unordered_map<int, TreeNode*>::const_iterator son;
	unordered_map<int, TreeNode*>::const_iterator root;
	while (H != 0) {
		int nodeCount = 0;
		unordered_map<int, TreeNode*> record;
		for (int i = 0; i < pow(2, H) - 1;i++) {
			int ID;
			cin >> ID;
			if (ID != -1) {
				record.insert(make_pair(i + 1, new TreeNode(ID, i + 1)));
				nodeCount++;
			}
		}
		
		root = record.find(1);
		unordered_map<int, TreeNode*>::const_iterator iter = record.begin();
		for (iter; iter != record.end(); ++iter) {
			if (iter != root) {
				int index = iter->first;
				while (index % 2 != 0) {
					if (index == 3) { break; }
					index /= 2;
				}
				index /= 2;

				parent = record.find(index);
				(parent->second)->children.push_back(iter->second);
			}		
		}

		unordered_map<int, TreeNode*>::const_iterator it = record.begin();
		for (it; it != record.end(); ++it) {
			sort(it->second->children.begin(),it->second->children.end(), compare);
		}
		
		GeneralTree General(root->second);
		cout << "preorder: ";
		General.Preorder(General.root, nodeCount);
		cout << '\n';
		cout << "postorder: ";
		General.Postorder(General.root, nodeCount);
		cout << '\n';
		cout << "level order: ";
		General.Levelorder();
		cout << '\n'<<'\n';
		PostCount = 1;
		
		
		iter = record.begin();
		for (iter; iter != record.end(); ++iter) {
			delete iter->second;
		}
		record.clear();
		cin >> H;
	}
	
	//system("pause");
	return 0;
}