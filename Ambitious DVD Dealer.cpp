#include<iostream>
#include<algorithm>
#include<vector>
using std::vector;
 
void DynamicProgramming(int song_Num, int DVD_Num, int diskTime, const vector <int> songs ){
    // Declare a 3D vector F[song_Num + 1][DVD_Num][diskTime + 1]
    vector<vector<vector<int> > > F(song_Num + 1, vector<vector<int> >(DVD_Num, vector<int>(diskTime + 1, 0)));
 
    // DP process : fill the table
    for (int i = 1; i <= song_Num ; i++){
        for (int j = 0; j < DVD_Num; j++) {
            for (int k = 0; k <= diskTime; k++) {
                F[i][j][k] = F[i - 1][j][k];
                if (diskTime >= songs[i]) {
                    // if ith song can be put in the current CD, then check whether to put it or not
                    if (songs[i] <= k) {
                        F[i][j][k] = std::max(F[i][j][k], F[i - 1][j][k - songs[i]] + 1);
                    }
                    // if ith song is too long to be put in the current CD, then check whether to put it in the next CD
                    else if (j >= 1) {
                        F[i][j][k] = std::max(F[i][j][k], F[i - 1][j - 1][diskTime - songs[i]] + 1);
                    }
                }
            }
        }
    }
    std::cout << F[song_Num][DVD_Num - 1][diskTime] << '\n';
}
 
int main(){
    vector<int> songs;        // to restore each song size
    int Num_test;
    std::cin >> Num_test;
 
    for(int i = 0; i < Num_test; i++){
        int song_Num, DVD_Num, diskTime, temp;
        std::cin >> song_Num >> DVD_Num >> diskTime;
        songs.push_back(0);
        for (int j = 0; j < song_Num; j++) {
            std::cin >> temp;
            songs.push_back(temp);
        }
        DynamicProgramming(song_Num, DVD_Num, diskTime, songs);
        songs.clear();       
    }
    return 0;
}