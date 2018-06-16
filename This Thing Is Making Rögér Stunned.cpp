#include <iostream>
#include <algorithm>
#include <stack>
#include <vector>
using namespace std;
 
int main(){
    ios_base::sync_with_stdio(false);
    cin.tie(0);
 
    int testcase;
    cin >> testcase;
 
    for (int i = 0; i < testcase; i++) {
        int N;
        cin >> N;
        vector<int> record;
        stack<int> stk_1, stk_2, stk_3;
        for (int j = 0; j < N; j++) {
            int temp;
            cin >> temp;
            record.push_back(temp);
 
            if (stk_1.empty() || temp > stk_1.top()) {
                stk_1.push(temp);
            }
            else if (temp < stk_1.top()) {
                if (stk_2.empty() || temp <= stk_2.top()) {
                    stk_2.push(temp);
                }
                else {
                    stk_3.push(temp);
                }
            }
        }
 
        vector<int> rmdupRec = record;
        sort(rmdupRec.begin(), rmdupRec.end());
        rmdupRec.erase(unique(rmdupRec.begin(), rmdupRec.end()), rmdupRec.end());
        if (record.size() != rmdupRec.size()) {
            cout << "N" << '\n';
        }
        else {
            if (stk_3.empty()) {
                cout << "Y 1" << '\n';
            }
            else {
                cout << "Y 2" << '\n';
            }
        }
    }
 
    //system("pause");
    return 0;
}