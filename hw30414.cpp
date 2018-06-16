#include<iostream>
#include<fstream>
#include<string>
#include<sstream>
#include<vector>
#include<stack>
#include<bitset>
#include<algorithm>
#include<cmath>

using namespace std;
string lookup_num[12] = {"0","2","4","8","16","32","64","128","256","512","1024","2048"};
string lookup_cor[12] = {"0000","0001","0010","0011","0100","0101","0110","0111","1000","1001","1010","1011"};
unsigned long long nextMap(unsigned long long map, int action);

// split the binary 64bits string into every 4 bits 
vector<string> Split(const string& str){
	int NumSubstrings = str.length() / 4;
	vector<string> results;
	for (int i = 0; i < NumSubstrings; i++){
		results.push_back(str.substr(i * 4, 4));
	}
	return results;
}
// check if there is an element of 2048
bool determineSuccess(const vector<string>& split_map) {
	int flag = 0;
	for (int i = 0; i < 16; i++) {
		if (split_map[i] == "1011") {
			flag = 1;
		}
	}
	if (flag == 0) {return 0;}
	else return 1;
}

void print_map(const unsigned long long& map) {
	if (map == -1) {
		cout << "Action:" << endl;
		cout << -1 << endl;
		cout << "Final:" << endl;
		for (int i = 0; i < 4; i++) {
			for (int j = 0; j < 4; j++) {
				cout << -1 << " ";
			}
			cout << endl;
		}
	}
	else {
		cout << "Final:" << endl;
		string map_str = bitset<64>(map).to_string();
		vector<string> split_map_str = Split(map_str);
		vector<int> map_int;
		for (int i = 15; i >= 0; i--) {
			unsigned long  map_converted_value = bitset<64>(split_map_str[i]).to_ulong();
			map_int.push_back(map_converted_value);
		}
		for (int j = 0; j < 4; j++) {
			for (int k = 0; k < 4; k++) {
				if (map_int[4 * j + k] == 0) { cout << 0 << " "; }
				else {
					cout << pow(2, map_int[4 * j + k]) << " ";
				}
			}
			cout << endl;
		}
	}
}

unsigned long long playGame(const unsigned long long& map) {
	stack<unsigned long long> container;
	stack<int> container_move_actions;
	vector<unsigned long long> move_records;
	vector<int> move_actions;
	unsigned long long temp;

	container.push(map);
	container_move_actions.push(-1);
	while (!container.empty()) {
		temp = container.top();
		move_records.push_back( container.top() );
		move_actions.push_back( container_move_actions.top() );
		container_move_actions.pop();
		container.pop();

		// If current map fulfills the requirement, return the current map
		string map_str = bitset<64>(temp).to_string();
		if ( determineSuccess(Split(map_str)) ) { 
			cout << "Action:" << endl;
			for (int i = 1; i < move_actions.size(); i++) {
				cout << move_actions[i] << " ";
			}
			cout << endl;
			cout << "Procedure:" << endl;
			for (int j = 1; j < move_records.size() ; j++) {
				print_map(move_records[j]);
			}
			cout << endl;
			return temp; 
		}

		////////////////////////// generate p<=4 maps and push into the stack/////////////////////////// 
		vector<unsigned long long> nextmaps;
		vector<int> nextmaps_actions;
		unsigned long long next_temp;
		//print_map(temp);
		for (int i = 0; i < 4; i++) {
			next_temp = nextMap(temp, i);
			//print_map(next_temp);
			if (next_temp != temp){
				nextmaps.push_back(next_temp);
				nextmaps_actions.push_back(i);
			}
		}
		//cout << "Next map size:" << nextmaps.size() << endl;;
		if (nextmaps.size() == 0) { 
			if(move_actions[move_actions.size() - 1 ] == 3){
				move_actions.pop_back();
				move_records.pop_back();
			}
			move_actions.pop_back();
			move_records.pop_back();
			continue; 
		}
		else {
			for (int j = nextmaps.size() - 1; j >= 0; j--) {
				container.push(nextmaps[j]);
				container_move_actions.push(nextmaps_actions[j]);
			}
		}
	}
	return -1;
}



int main() {
	string temp;
	int map_count;
	vector<string> map;
	cin >> map_count;
	// read the following maps, every 4 lines a count
	for (int i = 0; i < map_count; i++) {
		// for every 4 lines read in map and transfer to unsigned long long
		for (int j = 0; j < 16; j++) {
			cin >> temp;
			map.push_back( temp );
		}
		// restore the map converted form original map
		string map_converted;
		for (int k = 15; k >= 0; k--) {
			for (int m = 0; m < 12; m++) {
				if (map[k] == lookup_num[m]) {
					map_converted += lookup_cor[m];
				}
			}
		}
		// convert from binary string to decimal usigned long long
		unsigned long long map_converted_value = bitset<64>(map_converted).to_ullong();
		unsigned long long results = playGame(map_converted_value);
		print_map(results);
		//print_map(map_converted_value);
		map.clear();
	}

	//system("pause");
	return 0;
}