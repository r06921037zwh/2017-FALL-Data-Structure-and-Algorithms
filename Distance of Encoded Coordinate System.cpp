#include<iostream>
#include<algorithm>
#include<stack>
#include<vector>
using namespace std;
 
int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0);
 
    int N, Di;
    unsigned long long Pi;
    cin >> N;
    for (int i = 0; i < N; i++) {
        cin >> Di >> Pi;
        stack<int> temp;
        vector<int> Numbers;
        // perform storing in each digit
        while (Pi > 0) {
            temp.push(Pi % 10);
            Pi /= 10;
        }
        while (!temp.empty()){
            Numbers.push_back(temp.top());
            temp.pop();
        }
 
        static int count = 0;
        bool flag = false;
        if (Di > 0) {
            do {
                if (count == Di) {
                    for (int i = 0; i < Numbers.size(); i++) {
                        cout << Numbers[i];
                        flag = true;
                    }
                    cout << '\n';
                }
                count++;
            } while (next_permutation(Numbers.begin(), Numbers.end()));
 
            if (!flag) {
                cout << "NOPE!!" << '\n';
            }
            count = 0;
        }
 
        else {
            Di = abs(Di);
            do {
                if (count == Di) {
                    for (int i = 0; i < Numbers.size(); i++) {
                        cout << Numbers[i];
                        flag = true;
                    }
                    cout << '\n';
                }
                count++;
            } while (prev_permutation(Numbers.begin(), Numbers.end()));
 
            if (!flag) {
                cout << "NOPE!!" << '\n';
            }
            count = 0;
        }
    }   
 
    system("pause");
    return 0;
}