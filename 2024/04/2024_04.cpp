//
// Created by dpapen on 04.12.24.
//

#include "../../util/util.h"
#include <iostream>

using namespace std;
bool search(const string& pattern, const vector<vector<char>>&  data, int y_init, int x_init, int y_incr, int x_incr) {
    int y = y_init;
    int x = x_init;
    for(int i=0; i<pattern.length(); ++i){
        if(y<0 || y>=data.size() || x<0 || x>=data[y].size()) return false;
        if(data[y][x] != pattern[i]) return false;
        y += y_incr;
        x += x_incr;
    }
    return true;
}


int main() {
    vector<vector<char>> in = file_to_char_vector("../2024/04/input");
    int res = 0;

    for(int i=0; i<in.size(); ++i){
        for(int j=0; j<in[i].size(); ++j){
            if(in[i][j] == 'X'){
                res += search("MAS", in, i-1, j, -1, 0);//N
                res += search("MAS", in, i-1, j+1, -1, 1);//NE
                res += search("MAS", in, i, j+1, 0, 1);//E
                res += search("MAS", in, i+1, j+1, 1, 1);//SE
                res += search("MAS", in, i+1, j, 1, 0);//S
                res += search("MAS", in, i+1, j-1, 1, -1);//SW
                res += search("MAS", in, i, j-1, 0, -1);//W
                res += search("MAS", in, i-1, j-1, -1, -1);//NW
            }
        }
    }
    cout << res << "\n";

    res = 0;
    for(int i=0; i<in.size(); ++i){
        for(int j=0; j<in[i].size(); ++j){
            if(in[i][j] == 'A'){
                res +=    (search("MAS", in, i-1, j-1, 1, 1)
                        || search("MAS", in, i+1, j+1, -1, -1))
                      &&  (search("MAS", in, i+1, j-1, -1, 1)
                        || search("MAS", in, i-1, j+1, 1, -1));
            }
        }
    }
    cout << res <<"\n";
    //TODO freigabe oder c++ - Array
    return 0;
}