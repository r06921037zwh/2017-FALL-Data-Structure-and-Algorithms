#include <iostream>
#include <algorithm>
#include <vector>
using namespace std;
 
int main(){
    ios_base::sync_with_stdio(false);
    cin.tie(0);
 
    int testcase;
    cin >> testcase;
    for(int i = 0; i < testcase; i++){
        int totolSteps, icedStairs, maxStair;
        cin >> totolSteps >> icedStairs >> maxStair;
        vector<int> steps;
        vector<int> nonStairs;
        int temp;
        for(int j = 0; j < totolSteps; j++){
            cin >> temp;
            steps.push_back(temp);
        }
        for(int j = 0; j < icedStairs; j++){
            cin >> temp;
            nonStairs.push_back(temp);
        }
 
        vector<vector<int> > currentStairs(maxStair + 1, vector<int>(totolSteps + 1, 0) ) ;
        vector<int> possCount(totolSteps + 1, 0);
        currentStairs[0][0] = 1;
        possCount[0] = 1;
        int nowStair = 0;
        for(int j = 0; j < totolSteps ; j++){
            int count = 0;
            int already = 0;
            if(possCount[j] == 0){break;}
            for(int k = 0; k < maxStair + 1; k++){
                if(currentStairs[k][j] == 1){
                    if(k + steps[nowStair] < maxStair && k + steps[nowStair] >= 0 ){
                        if(find(nonStairs.begin(), nonStairs.end(), (k + steps[nowStair])) != nonStairs.end()) {}
                        else{ 
                            if(currentStairs[k + steps[nowStair]][j + 1] == 0){count++;}
                            currentStairs[k + steps[nowStair]][j + 1] = 1;
                        }
                    }
                    if(k - steps[nowStair] < maxStair && k - steps[nowStair] >= 0 ){
                        if(find(nonStairs.begin(), nonStairs.end(), (k - steps[nowStair])) != nonStairs.end()) {}
                        else{ 
                            if(currentStairs[k - steps[nowStair]][j + 1] == 0){count++;}
                            currentStairs[k - steps[nowStair]][j + 1] = 1; 
                        }
                    }
                    already++;
                    //cout << already << " "; 
                }
                if(nowStair == 0 || already == possCount[j]){break;}
            }
            possCount[j + 1] = count;
            nowStair++ ;
            //cout<<'\n';
        }
        /*
        for(int j = 0; j < totolSteps; j++){
            cout << possCount[j] << " ";
        }
        cout << "------------------------"<<'\n';
        for(int j = 0; j < maxStair + 1; j++){
            for(int k = 0; k < totolSteps + 1; k++){
                cout << currentStairs[j][k] << " ";
            }
            cout << '\n';
        }
        cout << "----------------------------------" << '\n';
        */
        int flag = -1;
        for(int j = maxStair; j >= 0; j--){
            if(currentStairs[j][totolSteps] == 1){
                cout << j << '\n';
                flag = 1;
                break;
            }
        }
        if(flag == -1){ cout << -1 << '\n';}
    }
 
    //system("pause");
    return 0;
}