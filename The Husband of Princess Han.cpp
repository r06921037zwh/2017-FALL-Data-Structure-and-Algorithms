#include <iostream>
#include <algorithm>
#include <numeric>
#include <vector>
using namespace std;
 
// return the optimal maximum value which a player can attain
int optimalStrategy(const vector<int>& container, int N) {
    // create a Table[N][N]
    vector<vector<int> > table(N, vector<int>(N, 0));
 
    for (int range = 0; range < N; range++) {
        for (int i = 0, j = range; j < N; i++, j++) {
            int x = ((i + 2) <= j) ? table[i + 2][j] : 0;
            int y = ((i + 1) <= (j - 1)) ? table[i + 1][j - 1] : 0;
            int z = (i <= (j - 2)) ? table[i][j - 2] : 0;
 
            table[i][j] = max(container[i] + min(x, y), container[j] + min(y, z));
        }
    }
    return table[0][N - 1];
}
 
int main() {
    int N;
    cin >> N;
    vector<int> container;
    for (int i = 0; i < N; i++) {
        int temp;
        cin >> temp;
        container.push_back(temp);
    }
 
    int optValue = optimalStrategy(container, N);
    int totalValue = accumulate(container.begin(), container.end(), 0);
    int opponentValue = totalValue - optValue;
 
    if (optValue > opponentValue) { cout << "Y" << '\n' << optValue - opponentValue;; }
    else { cout << "N" << '\n' << opponentValue - optValue; }
 
    system("pause");
    return 0;
}
 
/* http://www.geeksforgeeks.org/dynamic-programming-set-31-optimal-strategy-for-a-game/ */
