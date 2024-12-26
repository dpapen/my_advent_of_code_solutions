//
// Created by dpapen on 06.12.24.
//
#include "../../util/util.h"
#include <fstream>
#include <iostream>
#include <vector>
#include <set>

using namespace std;
const string ORIENTATIONS = "^>v<";
const int DX[]{0,1,0,-1};
const int DY[]{-1,0,1,0};

void findPos(const vector<vector<char>>& map, int& x, int& y, int& orientation) {
    for(int r=0; r<map.size(); ++r) {
       //auto tmp = std::find_first_of(map[r].begin(), map[r].end(), ORIENTATIONS.begin(), ORIENTATIONS.end());
       for(int c=0; c<map[r].size(); ++c) {
           if(ORIENTATIONS.contains(map[r][c])){
               x = c;
               y = r;
               for(int i=0; i<ORIENTATIONS.size(); ++i) {
                   if(ORIENTATIONS[i] == map[r][c]){
                       orientation = i;
                       return;
                   }
               }
           }
       }
    }
}


bool isLooping(const vector<vector<char>>& map) {
    set<pair<int,int>> hist[4]{};

    //int res = 1;

    int x;
    int y;
    int o;
    findPos(map, x, y, o);

    while(true) {
    if(hist[o].contains({x,y})) {
        return true;
    } else {
        hist[o].insert({x, y});
    }
    if(isOutOfBounds(x+DX[o], y+DY[o], map)) {
        //map[y][x] = 'X';
        return false;
    }
    //if facing obstacle turn right
    if(map[y+DY[o]][x+DX[o]] == '#'){
        o = (o+1)%4;
        //map[y][x] = ORIENTATIONS[o];
    } else {
        //take a step foreward
        //map[y][x] = 'X';
        x += DX[o];
        y += DY[o];
        //if(map[y][x] != 'X') ++res;
        //map[y][x] = ORIENTATIONS[o];
    }

    }

}

int main() {
    vector<vector<char>> map = file_to_char_vector("../2024/06/input");

    set<pair<int,int>> hist[4]{};

    int res = 1;

    int x;
    int y;
    int o;
    findPos(map, x, y, o);

    int initialx = x;
    int initialy = y;
    cout << x << ", " << y << ": " << ORIENTATIONS[o] << "\n";
    while(true) {
        if(hist[o].contains({x,y})) {
            break;
        } else {
            hist[o].insert({x, y});
        }
        if(isOutOfBounds(x+DX[o], y+DY[o], map)) {
            map[y][x] = 'X';
            break;
        }
        //if facing obstacle turn right
        if(map[y+DY[o]][x+DX[o]] == '#'){
            o = (o+1)%4;
            map[y][x] = ORIENTATIONS[o];
        } else {
            //take a step foreward
            map[y][x] = 'X';
            x += DX[o];
            y += DY[o];
            if(map[y][x] != 'X') ++res;
            map[y][x] = ORIENTATIONS[o];
        }

    }

    cout << res << "\n";
    //PART 2:
    map = file_to_char_vector("../2024/06/input");
    set<pair<int,int>> possible_obstacles{};

    for(int r=0; r < map.size(); ++r) {
        cout << "." << flush;
        for(int c=0; c < map[r].size(); ++c) {
            char memory = map[r][c];
            //check if we can place a new obstacle here
            if(ORIENTATIONS.contains(memory)) continue;
            if(memory == '#') continue;
            //place obstacle
            map[r][c] = '#';
            //add to possible obstacles, if it creates loop
            if(isLooping(map)) possible_obstacles.insert({c, r});
            //remove obstacle again
            map[r][c] = memory;
        }
    }

    cout << "\n" << possible_obstacles.size() << "\n";
    return 0;
}