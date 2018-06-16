#include <iostream>
#include <algorithm>
#include <vector>
using namespace std;
 
 
int main() {
    int N, P;
    cin >> N >> P;
    vector<int> price;
    vector<int> sat;
    for (int i = 0; i < N; i++) {
        int ni, pi, si;
        cin >> ni >> pi >> si;
        vector<int> temp1(ni, pi);
        vector<int> temp2(ni, si);
        price.insert(price.end(), temp1.begin(), temp1.end());
        sat.insert(sat.end(), temp2.begin(), temp2.end());
        /*
        for (int j = 0; j < price.size(); j++) {
            cout << price[j] << " ";
        }*/
    }
    int SIZE = price.size();
    vector<int> c(P + 1, 0);
    //cout << price.size() << " " << sat.size() << " " << c.size();
 
    for (int i = 0; i < SIZE; ++i)
        for (int j = P; j - price[i] >= 0; --j)    // �ѫ᩹�e
            c[j] = max(c[j], c[j - price[i]] + sat[i]);
 
 
    cout << c[P];
 
    system("pause");
    return 0;
}