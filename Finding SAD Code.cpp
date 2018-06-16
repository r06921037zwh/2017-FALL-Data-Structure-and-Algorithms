#include <iostream>
#include <stack>
using namespace std;
int main() {
    int testcase;
    cin >> testcase;
 
    for (int i = 0; i < testcase; i++) {
        stack<int> Vx, Vy, Vz;
        while (1) {
            int temp;
            cin >> temp;
            if (temp == -1) { break; }
 
            if (Vx.empty() || temp <= Vx.top()) {
                Vx.push(temp);
            }
            else if (temp > Vx.top()) {
                if (Vy.empty() || temp >= Vy.top()) {
                    Vy.push(temp);
                }
                else {
                    Vz.push(temp);
                }
            }
        }
        /*
        cout << "AAA" << " " << Vx.size() << " " << Vy.size() << " " << Vz.size() << '\n';
        while (!Vx.empty()) {
            cout << Vx.top() << " ";
            Vx.pop();
        }
        cout << '\n';
        while (!Vy.empty()) {
            cout << Vy.top() << " ";
            Vy.pop();
        }
        cout << '\n';
        while (!Vz.empty()) {
            cout << Vz.top() << " ";
            Vz.pop();
        }
        */
        if (!Vz.empty()) { cout << "1" <<'\n'; }
        else cout << "0" << '\n';
 
    }
 
    system("pause");
    return 0;
}