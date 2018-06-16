#include <iostream>
#include <vector>
#include <string>
#include <queue>
using namespace std;
class GeneralTree;
class TreeNode{
public:
    //TreeNode *leftchild;
    //TreeNode *rightchild;
	int ID;
    TreeNode *parent;
	vector<TreeNode*> children;
    
    TreeNode():parent(0),ID(0){};
    TreeNode(int s):parent(0),ID(s){};

    friend class GeneralTree;
};
class GeneralTree{
public:
    TreeNode *root;         // �Hroot�@���s����ʾ𪺰_�I
    GeneralTree():root(0){};
    GeneralTree(TreeNode *node):root(node){};

    void Preorder(TreeNode *current);
    //void Inorder(TreeNode *current);
    void Postorder(TreeNode *current, int N);
    void Levelorder();
};

void GeneralTree::Preorder(TreeNode *current) {
	if (current) {                          // if current != NULL
		cout << current->ID << " ";   
		for (int i = 0; i < current->children.size(); i++) {
			Preorder(current->children[i]);
		}
	}
}

int Count = 1;
void GeneralTree::Postorder(TreeNode *current, int N) {
	
	if (current) {                         // if current != NULL
		for (int i = 0; i < current->children.size(); i++) {
			Postorder(current->children[i], N);
		}
		std::cout << current->ID; 
		if (Count < N) { cout << " "; }
		Count++;
	}
}

void GeneralTree::Levelorder() {

	std::queue<TreeNode*> q;
	q.push(this->root);                     // ��root�@��level-order traversal���_�I
											// ���iqueue��
	while (!q.empty()) {                     // �Yqueue���O�Ū�, ����٦�node�S��visiting

		TreeNode *current = q.front();      // ���X���i�Jqueue��node
		q.pop();
		cout << current->ID ;               // �i��visiting
		for (int i = 0; i < current->children.size(); i++) {
			if (current->children[i] != NULL) {    // �Yleftchild�����, �N����iqueue
				q.push(current->children[i]);
			}
		}
		if (!q.empty()) { cout << " "; }
	}
}

struct NodeDegree{
	int pos;
	int deg;
	NodeDegree(int position, int degree) : pos(position), deg(degree) {};
};

int main() {
	ios_base::sync_with_stdio(false);
	cin.tie(0);
	int testcase, nodeNum;
	cin >> testcase >> nodeNum;

	for (int i = 0; i < testcase; i++) {
		int temp;
		vector<TreeNode*> tree;
		vector<int> degree;
		for (int j = 0; j < nodeNum; j++) {
			cin >> temp;
			tree.push_back(new TreeNode(temp));
		}

		vector<NodeDegree> nodeDeg;
		for (int j = 0; j < nodeNum; j++) {
			cin >> temp;
			if (j == 0) { 
				nodeDeg.push_back(NodeDegree(j, temp)); 
				continue;
			}
			//cout << nodeDeg.back().pos << " ";
			nodeDeg.back().deg--;
			tree[nodeDeg.back().pos]->children.push_back(tree[j]);
			if (nodeDeg.back().deg == 0) { nodeDeg.erase(nodeDeg.end() - 1); }
			if (temp != 0 ) {
				nodeDeg.push_back(NodeDegree(j, temp));
			}
		}
		
		GeneralTree General(tree[0]);
		General.Postorder(General.root, nodeNum);
		cout << '\n';
		General.Levelorder();
		cout << '\n';
		Count = 1;
		
	}

	return 0;
}