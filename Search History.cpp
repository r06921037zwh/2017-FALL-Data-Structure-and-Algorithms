#include <iostream>
#include <algorithm>
#include <vector>
#include <stack>
#include <map>
#include <string>
using namespace std;
vector<string> results;
class Node {
public:
    Node() { mContent = ' '; mMarker = false; }
    ~Node() {}
    char content() { return mContent; }
    void setContent(char c) { mContent = c; }
    bool wordMarker() { return mMarker; }
    void setWordMarker() { mMarker = true; }
    Node* findChild(char c);
    void appendChild(Node* child) { mChildren.push_back(child); }
    vector<Node*> children() { return mChildren; }
private:
    char mContent;
    bool mMarker;
    vector<Node*> mChildren;
};
 
class Trie {
public:
    Trie();
    ~Trie();
    void addWord(string &s);
    bool searchWord(string s);
    void suggestedWord(string &s);
    void printTopToBottomPath(Node* &curr, map<Node*, Node*> &parent);
    void printRootToLeaf(Node* root, vector<Node*> childs);
private:
    Node* root;
};
 
Node* Node::findChild(char c) {
    for (int i = 0; i < mChildren.size(); i++) {
        Node* tmp = mChildren.at(i);
        if (tmp->content() == c)
            return tmp;
    }
    return NULL;
}
 
Trie::Trie() {
    root = new Node();
}
 
Trie::~Trie() {    // Free memory
}
 
void Trie::addWord(string &s) {
    Node* current = root;
 
    if (s.length() == 0) {
        current->setWordMarker(); // an empty word
        return;
    }
 
    for (int i = 0; i < s.length(); i++) {
        Node* child = current->findChild(s[i]);
        if (child != NULL)
            current = child;
        else {
            Node* tmp = new Node();
            tmp->setContent(s[i]);
            current->appendChild(tmp);
            current = tmp;
        }
        if (i == s.length() - 1)
            current->setWordMarker();
    }
}
 
bool Trie::searchWord(string s) {
    Node* current = root;
 
    while (current != NULL) {
        for (int i = 0; i < s.length(); i++) {
            Node* tmp = current->findChild(s[i]);
            if (tmp == NULL)
                return false;
            current = tmp;
        }
        if (current->wordMarker())
            return true;
        else
            return false;
    }
    return false;
}
 
void Trie::suggestedWord(string &s) {
    Node* current = root;
    string str = s;
    while (current != NULL) {
        for (int i = 0; i < s.length(); i++) {
            Node* tmp = current->findChild(s[i]);
            if (tmp == NULL)
                return;
            current = tmp;
        }
        printRootToLeaf(current, current->children());
        break;
    }
    return;
}
 
void Trie::printTopToBottomPath(Node* &curr, map<Node*, Node*> &parent ) {
    stack<Node*> stk;
    string str = "";
    while (curr) {
        stk.push(curr);
        curr = parent[curr];
    }
 
    int count = 0;
    while (!stk.empty()) {
        curr = stk.top();
        stk.pop();
        if (count == 0) {
            count++;
            continue;
        }
        str += curr->content();
    }
    results.push_back(str);
}
 
void Trie::printRootToLeaf(Node* root, vector<Node*> childs)
{
    if (root == NULL)
        return;
 
    stack<Node*> nodeStack;
    nodeStack.push(root);
 
    map<Node*, Node*> parent;
    parent[root] = NULL;
 
    while (!nodeStack.empty()) {
        Node* current = nodeStack.top();
        nodeStack.pop();
 
        if (current->wordMarker() == true) {
            printTopToBottomPath(current, parent);
        }
        for (int i = 0; i < current->children().size(); i++) {
            parent[current->children().at(i)] = current;
            nodeStack.push(current->children().at(i));
        }
    }
}
 
int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0);
 
    int N;
    cin >> N;
    Trie* trie = new Trie();
 
    for (int i = 0; i < N; i++) {
        string temp;
        cin >> temp;
        trie->addWord(temp);
    }
    int nKeyWord;
    cin >> nKeyWord;
    for (int i = 0; i < nKeyWord; i++) {
        string temp;
        cin >> temp;       
        trie->suggestedWord(temp);
        sort(results.begin(), results.end());
        results.erase(unique(results.begin(), results.end()), results.end());
        if (results.empty()) {
            cout << "NO MATCHING!" <<'\n';
            continue;
        }
        for (int j = 0; j < results.size(); j++) {
            cout << temp + results[j] << '\n';
        }
        results.clear();
    }
 
    delete trie;
    //system("pause");
    return 0;
}