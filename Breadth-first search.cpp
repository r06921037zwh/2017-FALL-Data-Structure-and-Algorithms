#include <iostream>
#include <string>
#include <vector>
#include <queue>
using namespace std;
 
#define TableSize 9
 
struct pos {
    pos(int x_pos, int y_pos) : x(x_pos), y(y_pos){}
    int x, y;
    bool operator==(const pos &position) const {
        return (x == position.x && y == position.y);
    }
};
 
int dir[8][2] = { {-2, 1},{-1, 2},{1, 2},{2, 1},
                  {2, -1},{1,-2},{-1, -2},{-2, -1} };
 
bool checkRange(int x, int y){
    return x >= 0 && x < TableSize && y >= 0 && y < TableSize;
}
 
int main() {
    int holeNum;
    cin >> holeNum;
    vector<pos> holePos;
    for (int i = 0; i < holeNum; i++) {
        string hole;
        cin >> hole;
        pos temp(0,0);
        temp.y = (int)(hole[0] - 'a');
        temp.x = (int)(hole[1] - '0' - 1);
        //cout << hole_x << " " << hole_y << '\n';
        holePos.push_back(temp);
    }
 
    int routes;
    cin >> routes;
    for (int i = 0; i < routes; i++) {
        string start, end;
        cin >> start >> end;
        int start_y = (int)(start[0] - 'a');
        int start_x = (int)(start[1] - '0' - 1);
        int end_y = (int)(end[0] - 'a');
        int end_x = (int)(end[1] - '0' - 1);
 
        int Table_count[TableSize][TableSize] = { -1 };
        bool Table_status[TableSize][TableSize] = { false };
        bool IsHole[TableSize][TableSize] = { false };
 
        Table_count[start_x][start_y] = 0;
        Table_status[start_x][start_y] = true;
        for (int j = 0; j < holePos.size(); j++) {
            IsHole[holePos[j].x][holePos[j].y] = true;
        }
        IsHole[start_x][start_y] = false;
        IsHole[end_x][end_y] = false;
 
        queue<pos> BFS;
        BFS.push(pos(start_x, start_y));
        pos destination(pos(end_x, end_y));
 
 
 
        if (BFS.front() == destination) {
            cout << "Going from " << start << " to " << end << " needs 0 moves."<<'\n';
            continue;
        }
 
        bool isFind = false;
        pos currentPos(0, 0), newPos(0, 0);
        while (!BFS.empty()) {
            currentPos = BFS.front();
            //cout << currentPos.x << " " << currentPos.y << '\n';
            //cout << Table_status[currentPos.x][currentPos.y] << " " << Table_count[currentPos.x][currentPos.y] << '\n';
            BFS.pop();
 
            for (int j = 0; j < 8; ++j) {
                newPos.x = currentPos.x + dir[j][0];
                newPos.y = currentPos.y + dir[j][1];
 
                if (checkRange(newPos.x, newPos.y) && !Table_status[newPos.x][newPos.y] && !IsHole[newPos.x][newPos.y]) {
                    BFS.push(newPos);
                    Table_status[newPos.x][newPos.y] = true;
                    Table_count[newPos.x][newPos.y] = Table_count[currentPos.x][currentPos.y] + 1;
                    //cout << newPos.x << " " << newPos.y << " ";
                    //cout << Table_count[newPos.x][newPos.y] << '\n';
                }
 
                if (newPos == destination) {
                    isFind = true;
                    break;
                }
 
            }
            if (isFind) break;
        }
 
        cout << "Going from " << start << " to " << end << " needs "
            << Table_count[newPos.x][newPos.y] <<" moves." << '\n';
 
    }
 
    system("pause");
    return 0;
}