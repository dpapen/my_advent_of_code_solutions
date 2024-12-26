//
// Created by dpapen on 10.12.24.
//
#include "../../util/util.h"
#include <iostream>
#include <set>

using namespace std;

const int DX[]{0,1,0,-1};
const int DY[]{-1,0,1,0};

void search_trail_endpoints(const vector<vector<char>>& map, int x, int y, set<pair<int,int>>& goals) {
    if(map[y][x] == '9'){
        goals.insert({x,y});
        return;
    }
    for(int i=0; i<4; ++i){
        int x2 = x+DX[i];
        int y2 = y+DY[i];
        if(!isOutOfBounds(x2, y2, map)
            && map[y2][x2] == map[y][x] + 1) {
            search_trail_endpoints(map, x2, y2, goals);
        }
    }
}

int search_distinct_trails(const vector<vector<char>>& map, int x, int y) {
    if(map[y][x] == '9'){
        return 1;
    }
    int res = 0;
    for(int i=0; i<4; ++i){
        int x2 = x+DX[i];
        int y2 = y+DY[i];
        if(!isOutOfBounds(x2, y2, map)
           && map[y2][x2] == map[y][x] + 1) {
            res += search_distinct_trails(map, x2, y2);
        }
    }
    return res;
}



int main() {
    vector<vector<char>> map = file_to_char_vector("../2024/10/input");
    long long res = 0;
    long long res2 = 0;
    for(int y=0; y<map.size(); ++y) {
        for(int x=0; x<map[y].size(); ++x) {
            if (map[y][x] == '0') {
                set<pair<int, int>> dest{};

                search_trail_endpoints(map, x, y, dest);
                res += dest.size();

                res2 += search_distinct_trails(map, x, y);
            }
        }
    }

    cout << res << "\n";
    cout << res2 << "\n";

    return 0;
}