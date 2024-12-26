//
// Created by dpapen on 08.12.24.
//
#include "../../util/util.h"
#include <iostream>
#include <set>

using namespace std;


int main() {
    int w,h;
    map<char, set<pair<int,int>>> antennas = file_to_char_locations("../2024/08/input", w, h, ".");
    set<pair<int,int>> antinodes{};



    for(const auto& a : antennas) { //TODO use of auto in klausur?
        for(pair<int,int> pos1 : a.second) {
            for(pair<int,int> pos2 : a.second) {
                if(pos1 != pos2) {
                    int x = 2 * pos1.first - pos2.first;
                    int y = 2 * pos1.second - pos2.second;
                    if (!isOutOfBounds(x, y, w, h)) {
                        antinodes.insert({x, y});
                    }
                }
            }
        }
    }
    for(int l=0; l<h; ++l) {
        for(int c=0; c<w; ++c) {
            cout << (antinodes.contains({c,l})?"#":".");
        }
        cout << "\n";
    }

    cout << antinodes.size() << "\n";

    //PART2
    antinodes.clear();//TODO memory leak?

    for(const auto& a : antennas) { //TODO use of auto in klausur?
        for(pair<int,int> pos1 : a.second) {
            for(pair<int,int> pos2 : a.second) {
                if(pos1 != pos2) {
                    int x = pos2.first;
                    int y = pos2.second;
                    int dx = pos2.first - pos1.first;
                    int dy = pos2.second - pos1.second;
                    //TODO interpreting the task strictly we must divide dx & dy by there gcd
                    while (!isOutOfBounds(x, y, w, h)) {
                        antinodes.insert({x, y});
                        x += dx;
                        y += dy;
                    }
                }
            }
        }
    }
    for(int l=0; l<h; ++l) {
        for(int c=0; c<w; ++c) {
            cout << (antinodes.contains({c,l})?"#":".");
        }
        cout << "\n";
    }

    cout << antinodes.size() << "\n";

    return 0;
}