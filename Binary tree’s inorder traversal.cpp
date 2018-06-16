#include<iostream>
#include<algorithm>
#include<vector>
#include<stack>
using namespace std;
 
struct node {
    int number;
    int key;
};
 
int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0);
 
    int N, counter = 0;
    cin >> N;
 
    for (int i = 0; i < N; i++) {
        counter++;
 
        vector<node> Nodes;
        node temp;
        temp.key = 0;
        temp.number = -2;
        Nodes.push_back(temp);
 
        int treeSize;
        cin >> treeSize;
        for (int j = 0; j < treeSize; j++) {
            cin >> temp.number;
            if (Nodes[(j + 1) / 2].number == -1) { temp.number = -1; }
            temp.key = j + 1;
            Nodes.push_back(temp);
        }
        vector<node> results;
        stack<node> operStack;
        int currentKey = 1;
        while(1){
            if (currentKey <= treeSize) {
                operStack.push(Nodes[currentKey]);
                currentKey = 2 * currentKey;
            }
            else if(currentKey > treeSize && operStack.size() != 0){
                results.push_back(operStack.top());
                currentKey = operStack.top().key * 2 + 1;
                //if (operStack.top().number != -1) { cout << operStack.top().number << " ";}
                operStack.pop();
            }
            else break;
        }
        for (int k = 0; k < results.size(); k++) {
            if (results[k].number == -1) { continue; }
            cout << results[k].number << " ";
        }
        if (counter < N) { cout << '\n'; }
    }
    //system("pause");
    return 0;
}