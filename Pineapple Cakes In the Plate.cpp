#include <iostream>
#include <algorithm>
#include <numeric>
#include <string>
#include <vector>
using namespace std;
 
int main() {
    int TestCase;
    cin >> TestCase;
    for (int i = 0; i < TestCase; i++) {
        int N;
        cin >> N;
        cin.ignore(1000, '\n');
 
        vector<vector<int> > Matrix(N, vector<int>(N, 0));
        string temp;
        for (int j = 0; j < N; j++) {
            getline(cin, temp);
            for (int k = 0; k < N; k++) {
                Matrix[j][k] = temp[k] - '0';
                //cout << Matrix[j][k] << " ";
            }
            //cout << '\n';
        }
 
        vector<vector<int> > S(N, vector<int>(N, 0));
        for (int j = 0; j < N; j++) {
            S[j][0] = Matrix[j][0];
            S[0][j] = Matrix[0][j];
        }
 
        for (int m = 1; m < N; m++){
            for (int n = 1; n < N; n++){
                if (Matrix[m][n] == 1) { S[m][n] = min ( min(S[m][n - 1], S[m - 1][n]), S[m - 1][n - 1]) + 1; }
                else S[m][n] = 0;
            }
        }
 
        int sum = 0;
        for (int m = 0; m < N; m++) {
            sum = accumulate(S[m].begin(), S[m].end(), sum);
        }
 
        cout << sum << '\n';
 
    }
    //system("pause");
    return 0;
}