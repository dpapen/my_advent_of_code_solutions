//
// Created by dpapen on 14.12.24.
//
#include "../../util/util.h"
#include <iostream>


using namespace std;

constexpr int w = 101;
constexpr int h = 103;

int robot_count[h][w];

struct bot {
    pair<int, int> p;
    pair<int, int> v;

    void move() {
        --robot_count[p.second][p.first];
        p.first = (p.first+v.first)%w;
        if(p.first < 0) p.first += w;
        p.second = (p.second+v.second)%h;
        if(p.second < 0) p.second += h;
        ++robot_count[p.second][p.first];
    }
};

int count_neighbors(){
    int res = 0;
    for(int y=0; y<h; ++y) {
        for(int x=0; x<w; ++x) {
            if(robot_count[y][x] > 0) {
                if(robot_count[(y+1)%h][x] > 0) ++res;
                if(robot_count[y][(x+1)%w] > 0) ++res;
            }
        }
    }
    return res;
}


int main() {
    vector<string> input = file_to_strings("../2024/14/input");
    int t1 = 100;

    /*
     *  0 1
     *  2 3
     */
    unsigned long long sector_count[4] = {0,0,0,0};

    vector<bot> bots{};

    for(const string& s : input) {
        vector<string> s2 = split_string(s, ' ');
        vector<int> p = string_to_ints_auto(s2[0]);
        vector<int> v = string_to_ints_auto(s2[1]);

        bots.emplace_back(bot{{p[0], p[1]}, {v[0], v[1]}});
        ++robot_count[p[1]][p[0]];

        int x = ((p[0]+t1*v[0])%w+w)%w;//so the result is definitly positve
        int y = ((p[1]+t1*v[1])%h+h)%h;

        if(x != w/2 && y != h/2) {//don't count robots that are in the middle of either coord
            ++sector_count[(x>w/2)+2*(y>h/2)];
        }

        cout << x << ", " << y << ": sector " <<  (x>w/2)+2*(y>h/2) << "\n";
    }

    unsigned long long res = 1;
    for(unsigned long long i :  sector_count) res *= i;
    cout << res << "\n";

    cout << "--------------------PART2---------------------------\n";

    int max_neighbors = 0;
    int cur_neighbors = 0;

    for(int t=0; t<10000; ++t){
        cur_neighbors = count_neighbors();
        //cout << cur_neighbors <<"\n";
        if(cur_neighbors > max_neighbors) {
            max_neighbors = cur_neighbors;
            cout << "After " << t << " seconds: " << cur_neighbors << "\n";
            for (auto &y: robot_count) {
                for (int x: y) {
                    cout << ((x > 0) ? '#' : ' ') << " ";  //robot_count[y][x]
                }
                cout << "\n";
            }
        }
        for(bot& b : bots) {
            b.move();
        }
    }

    return 0;
}