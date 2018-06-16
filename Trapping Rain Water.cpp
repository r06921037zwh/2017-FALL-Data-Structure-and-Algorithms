#include <iostream>
#include <algorithm>
#include <vector>
using namespace std;

int findWater(const vector<vector<int> > &arr){
	int water = 0;
	for (int k = 0; k < arr.size(); k++) {
		int n = arr[k].size();

		vector<int> left(n, 0);
		vector<int> right(n, 0);

		left[0] = arr[k][0];
		for (int i = 1; i < n; i++) {
			left[i] = max(left[i - 1], arr[k][i]);
		}

		right[n - 1] = arr[k][n - 1];
		for (int i = n - 2; i >= 0; i--) {
			right[i] = max(right[i + 1], arr[k][i]);
		}

		for (int i = 0; i < n; i++) {
			water += min(left[i], right[i]) - arr[k][i];
		}
	}
	return water;
}

int main(){
	ios_base::sync_with_stdio(false);
	cin.tie(0);
	
	vector<vector<int> > Record;
	vector<int> record;
	int num;
	while (cin >> num) {
		if (num == 0) {
			if (!record.empty()) {
				Record.push_back(record);
				record.clear();
			}
			continue;
		}
		record.push_back(num);
	}
	
	Record.push_back(record);
	/*
	for (int i = 0; i < Record.size(); i++) {
		for (int j = 0; j < Record[i].size(); j++) {
			cout << Record[i][j] << " ";
		}
		cout << '\n';
	}*/
	

	cout << findWater(Record) <<'\n';
	return 0;
}