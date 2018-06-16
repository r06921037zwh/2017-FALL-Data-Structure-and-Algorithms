#include <iostream>
#include <algorithm>
#include <vector>
#include <stack>
using namespace std;
 
struct node {
    node(int key_value) : key(key_value) {};
    int key;
    int parent;
};
 
void findKillNode(vector<node> &Nodes, stack<node> killNodes, vector<int> &results, const node &a) {
    vector<node> killtemp;
    vector<int> visitedIndex;
    for (int i = 0; i < Nodes.size(); i++) {
        if (Nodes[i].parent == a.key) {
            killNodes.push(Nodes[i]);
            results.push_back(Nodes[i].key);
            killtemp.push_back(Nodes[i]);
            visitedIndex.push_back(i);
        }
    }
    for (int i = visitedIndex.size() - 1; i >= 0; i--) {
        Nodes.erase(Nodes.begin() + visitedIndex[i]);
    }
    for (int j = 0; j < killtemp.size(); j++) {
        findKillNode(Nodes, killNodes, results, killtemp[j]);
    }
}
 
int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0);
 
    int N;
    cin >> N;
    vector<node> Nodes;
    for (int i = 0; i < N; i++) {
        int ID;
        cin >> ID;
        node temp(ID);
        Nodes.push_back(temp);
    }
    for (int i = 0; i < N; i++) {
        int parent_ID;
        cin >> parent_ID;
        Nodes[i].parent = parent_ID;
    }
    int killed_ID;
    cin >> killed_ID;
    stack<node> killNodes;
    vector<int> results;
    results.push_back(killed_ID);
 
    vector<int> visitedIndex;
    for (int i = 0; i < Nodes.size(); i++) {
        if (Nodes[i].parent == killed_ID) {
            killNodes.push(Nodes[i]);
            results.push_back(Nodes[i].key);
            visitedIndex.push_back(i);
        }
    }
    for (int i = visitedIndex.size() - 1; i >= 0; i--) {
        Nodes.erase(Nodes.begin() + visitedIndex[i]);
    }
 
    while (!killNodes.empty()) {
        node temp = killNodes.top();
        killNodes.pop();
        findKillNode(Nodes, killNodes, results, temp);
    }
 
    /*
    for (int i = 0; i < Nodes.size(); i++) {
        cout << Nodes[i].key << " " << Nodes[i].parent << '\n';
    }*/
 
    sort(results.begin(), results.end());
    for (int i = 0; i < results.size(); i++) {
        cout << results[i];
        if (i < results.size() - 1) { cout << " "; }
    }
    system("pause");
    return 0;
}