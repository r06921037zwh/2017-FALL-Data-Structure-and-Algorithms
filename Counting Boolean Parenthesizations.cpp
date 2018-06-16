#include <iostream>
#include <sstream>
#include <vector>
#include <string>
using namespace std;
 
int countParenth(const vector<string> &symbols,const vector<string> &operators, int n){
    vector<vector<int> > F(n, vector<int>(n, 0));
    vector<vector<int> > T(n, vector<int>(n, 0));
 
    // Fill diaginal entries first
    // All diagonal entries in T[i][i] are 1 if symbol[i]
    // is T (true).  Similarly, all F[i][i] entries are 1 if
    // symbol[i] is F (False)
    for (int i = 0; i < n; i++){
        F[i][i] = (symbols[i] == "false") ? 1 : 0;
        T[i][i] = (symbols[i] == "true") ? 1 : 0;
    }
 
    // Now fill T[i][i+1], T[i][i+2], T[i][i+3]... in order
    // And F[i][i+1], F[i][i+2], F[i][i+3]... in order
    for (int gap = 1; gap < n; ++gap)
    {
        for (int i = 0, j = gap; j<n; ++i, ++j)
        {
            T[i][j] = F[i][j] = 0;
            for (int g = 0; g < gap; g++)
            {
                // Find place of parenthesization using current value of gap
                int k = i + g;
 
                // Store Total[i][k] and Total[k+1][j]
                int tik = T[i][k] + F[i][k];
                int tkj = T[k + 1][j] + F[k + 1][j];
 
                // Follow the recursive formulas according to the current
                // operator
                if (operators[k] == "and"){
                    T[i][j] += T[i][k] * T[k + 1][j];
                    F[i][j] += (tik*tkj - T[i][k] * T[k + 1][j]);
                }
                if (operators[k] == "or"){
                    F[i][j] += F[i][k] * F[k + 1][j];
                    T[i][j] += (tik*tkj - F[i][k] * F[k + 1][j]);
                }
                if (operators[k] == "xor"){
                    T[i][j] += F[i][k] * T[k + 1][j] + T[i][k] * F[k + 1][j];
                    F[i][j] += T[i][k] * T[k + 1][j] + F[i][k] * F[k + 1][j];
                }
            }
        }
    }
    return T[0][n - 1];
}
 
 
int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(0);
 
    int testcase;
    cin >> testcase;
    cin.ignore(1000, '\n');
    for (int i = 0; i < testcase; i++) {
        int Num;
        cin >> Num;
        vector<string> symbols;
        vector<string> operators;
        for (int j = 1; j < Num + 1; j++) {
            string temp;
            cin >> temp;
            if (j % 2 == 1) { symbols.push_back(temp); }
            else operators.push_back(temp);
        }
 
        cout << countParenth(symbols, operators, symbols.size()) << '\n';
    }
 
    //system("pause");
    return 0;
}