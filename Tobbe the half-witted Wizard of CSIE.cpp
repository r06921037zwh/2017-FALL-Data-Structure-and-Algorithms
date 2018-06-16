#include <iostream>
#include <sstream>
#include <vector>
#include <stack>
#include <string>
using namespace std;
 
int iCPri(string a) {    // in_come priority
    int pri;
    if (a == "(" || a == ")") { pri = 2; }
    else if (a == "*" || a == "/") { pri = 1; }
    else if (a == "+" || a == "-") { pri = 0; }
    else { pri = 3; }
    return pri;
}
 
int iSPri(string a) {    // in_stack priority
    int pri;
    if (a == "(" || a == ")") { pri = -1; }
    else if (a == "*" || a == "/") { pri = 1; }
    else if (a == "+" || a == "-") { pri = 0; }
    else { pri = -2; }
    return pri;
}
void inToPo(const vector<string>& infix, vector<string>& postfix, stack<string>& operStack) {
    operStack.push("#");
    for (int i = 0; i < infix.size(); i++) {
        if (iCPri(infix[i]) == 3) { postfix.push_back(infix[i]); }
        else if (infix[i] == ")") {
            while (operStack.top() != "(") {
                postfix.push_back(operStack.top());
                operStack.pop();
            }
            operStack.pop();
        }
        else {
            while (iSPri(operStack.top()) >= iCPri(infix[i])) {
                postfix.push_back(operStack.top());
                operStack.pop();
            }
            operStack.push(infix[i]);
        }
    }
    while (operStack.top() != "#") {
        postfix.push_back(operStack.top());
        operStack.pop();
    }
    for (int i = 0; i < postfix.size(); i++) {
        cout << postfix[i];
        if (i < postfix.size() - 1) {
            cout << " ";
        }
    }
}
int main() {
 
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    int N;
    cin >> N;
    cin.ignore(1000, '\n');
    for (int i = 0; i < N; i++) {   
        string temp;
        istringstream ss;
        getline(cin, temp);
        ss.str(temp);
        vector<string> infix;
        vector<string> postfix;
        stack<string> operStack;
        while (ss >> temp) {
            infix.push_back(temp);
        }
        inToPo(infix, postfix, operStack);
        cout << '\n';
    }
    //system("pause");
    return 0;
}
