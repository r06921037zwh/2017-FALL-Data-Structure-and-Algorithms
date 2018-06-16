#include <iostream>
#include <algorithm>
#include <vector>
#include <sstream>
#include <string>
using namespace std;

struct chord{
	int start, finish;
	chord(int start_point, int end_point) :start(start_point), finish(end_point) {};
};

bool myfunction(chord s1, chord s2){
	return (s1.start < s2.start);
}
int maxChord(vector<chord> &arr, int N) {
	vector<vector<int> > table(N, vector<int>(N, 0));
	for (int j = 0; j <= N - 1; j++) {
		int k;
		for (int m = 0; m < arr.size(); m++) {
			if (arr[m].start == j) {
				k = arr[m].finish;
				break;
			}
			else if (arr[m].finish == j) {
				k = arr[m].start;
				break;
			}
		}
		for (int i = 0; i <= j - 1; i++) {
			if (i <= k && k <= j - 1 && table[i][k - 1] + table[k + 1][j - 1] + 1 > table[i][j - 1]) {
				table[i][j] = table[i][k - 1] + table[k + 1][j - 1] + 1;
			}
			else {
				table[i][j] = table[i][j - 1];
			}
		}
	}
	return table[0][N - 1];
}

int main(){
	vector<chord> arr;
	int N;
	cin >> N;
	cin.ignore(1000, '\n');
	string temp;
	while (getline(cin, temp)) {
		if (temp.length() == 1 && temp == "0") { break; }
		stringstream ss;
		ss.str(temp);
		int left, right;
		ss >> left >> right ;
		if (left > right) { swap(left, right); }
		arr.push_back( chord(left, right) );
	}
	arr.erase(arr.end() - 1);
	sort(arr.begin(), arr.end(), myfunction);
	/*
	for (int i = 0; i < arr.size(); i++) {
		cout << arr[i].start << arr[i].finish << '\n';
	}*/
	if (N == 0) { cout << 0; }
	else if (N == 2) { cout << 1; }
	else {cout << maxChord(arr, N);}
	
	return 0;
}