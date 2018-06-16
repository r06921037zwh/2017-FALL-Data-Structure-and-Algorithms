#include <iostream>
#include <algorithm>
#include <cmath>
#include <vector>
#include <string>
using namespace std;
 
struct numbers {
    int num;
    int currentSum;
    vector<int> currTra;
    string precedence;   
};
 
bool acompare(numbers lhs,numbers rhs) {
    return (lhs.precedence < rhs.precedence);
}
 
void CreateTree(numbers& node, vector<numbers>& Nodes ,const int& depth) {
    node.num = 0;
    node.currentSum = 0;
    Nodes.push_back(node);
    for (int i = 0; i < depth + 1; i++) {
        for (int j = 0; j < pow(2, i); j++) {
            int temp;
            cin >> temp;
 
            if (i == 0) {
                node.num = temp;
                node.currentSum = temp;
                node.currTra.push_back(temp);
                node.precedence = "0";
                Nodes.push_back(node);
            }
            else {
                node.num = temp;
                node.currentSum = Nodes[Nodes.size() / 2].currentSum + temp;
                node.currTra = Nodes[Nodes.size() / 2].currTra;
                node.currTra.push_back(temp);
                node.precedence = Nodes[Nodes.size() / 2].precedence ;
                if (Nodes.size() % 2 == 0) {node.precedence += "0";}
                else { node.precedence += "1"; }
                Nodes.push_back(node);
            }
        }
    }
    sort(Nodes.begin(), Nodes.end(), acompare);
}
 
void checkSum(const vector<numbers>& Nodes, const int& sum) {
    for (int i = 0; i < Nodes.size(); i++) {
        if (Nodes[i].currentSum == sum) {
            for (int j = 0; j < Nodes[i].currTra.size(); j++) {
                cout << Nodes[i].currTra[j];
                if (j < Nodes[i].currTra.size() - 1) {cout << " ";}
            }
            cout << '\n';
        }
    }
}
int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0);
 
    int depth, sum;
    cin >> depth;
    numbers node;
    vector<numbers> Nodes;
    CreateTree(node, Nodes, depth);
    cin >> sum;
    checkSum(Nodes, sum);
 
    return 0;
}