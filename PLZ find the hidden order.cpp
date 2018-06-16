#include <iostream>
#include <algorithm>
#include <vector>
#include <string>
using namespace std;
 
int maxSumIS(const vector<int> &str,vector<int> &msisCount, int n)
{
    for (int i = 1; i < n; i++) {
        for (int j = 0; j < i; j++) {
            if (str[i] > str[j] && msisCount[i] < msisCount[j] + 1) {
                msisCount[i]++;
            }
        }
    }
    int max = *max_element(msisCount.begin(), msisCount.end());
    return max;
}
 
int main() {
    int N;
    cin >> N;
    for (int i= 0; i < N; i++) {
        vector<int> str;
        string temp;
        cin >> temp;
        for (int j = 0; j < temp.length(); j++) {
            str.push_back(temp[j] - 'a' + 1);
        }
 
        vector<int> msisCount(str.size(), 1);
        int maxLen = maxSumIS(str, msisCount, str.size());
        cout << maxLen << '\n';
    }
 
    system("pause");
    return 0;
}
 
//http://www.geeksforgeeks.org/dynamic-programming-set-14-maximum-sum-increasing-subsequence/
