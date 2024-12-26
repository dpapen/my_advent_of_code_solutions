//
// Created by dpapen on 12.12.24.
//
#include "../../util/util.h"
#include <iostream>

using namespace std;

const int DX[]{0,1,0,-1};
const int DY[]{-1,0,1,0};


bool is_new_side(int x, int y, int orientation, vector<vector<char>>& map){
    int i=3;
    {
        int x2 = x + DX[(orientation + i)%4];
        int y2 = y + DY[(orientation + i)%4];
        if (!isOutOfBounds(x2, y2, map)
        && (map[y2][x2] - map[y][x])%('a' - 'A') == 0) { //same letter
            if (isOutOfBounds(x2 + DX[orientation], y2 + DY[orientation], map)
            || (map[y2 + DY[orientation]][x2 + DX[orientation]] - map[y2][x2]) % ('a' - 'A') != 0) {
                return false;
            }
        }
    }
    return true;
}

void search_plot(int x, int y, vector<vector<char>>& map, int& area, int& perimeter, int& sides ) {
    char plant = map[y][x];
    ++area;
    map[y][x] += 'a'-'A';//to lowercase

    for(int i=0; i<4; ++i) {
        int x2 = x+DX[i];
        int y2 = y+DY[i];
        if(!isOutOfBounds(x2,y2,map)) {
            switch (map[y2][x2]-plant) {
                case 'a'-'A': //same char in lowercase = same plant already searched
                    break;
                case 0: //same char = same plant not searched
                    search_plot(x2, y2, map, area, perimeter, sides);
                    break;
                default: //different plant
                    ++perimeter;
                    if(is_new_side(x,y,i,map)) ++sides;
            }
        } else {
            ++perimeter;//we need a fence on the outside of the map, too
            if(is_new_side(x,y,i,map)) ++sides;
        }
    }

}

int main() {
    vector<vector<char>> map = file_to_char_vector("../2024/12/input");
    unsigned long long res = 0;

    for(int y=0; y<map.size(); ++y) {
        for(int x=0; x<map[y].size(); ++x) {
            if(map[y][x] < 'a'){
                int area = 0;
                int perimeter = 0;
                int sides = 0;
                search_plot(x, y, map, area, perimeter, sides);
                res += area*sides;
            }
        }
    }


    cout << res << "\n";
    return 0;
}