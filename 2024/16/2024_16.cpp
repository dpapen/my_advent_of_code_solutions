//
// Created by dpapen on 16.12.24.
//
#include "../../util/util.h"
#include <iostream>
#include <fstream>


using namespace std;

unsigned long long COST_TURN = 1000;

struct goal {
    int goal_x;
    int goal_y;

    inline unsigned long long h(int x, int y, size_t o) const {
        int dx = goal_x - x;
        int dy = goal_y - y;
        unsigned long long res = abs(dx) + abs(dy);

        if (dx * DX[o] < 0 || dy * DY[o] < 0) res += 2 * COST_TURN;
        else if ((dx != 0 && dy != 0)
                 || (dx == 0 && DY[0] == 0)
                 || (dy == 0 && DX[0] == 0))
            res += COST_TURN;

        return res;
    }

};

//no time for an elegant and safe solution
inline u_int32_t get_id(size_t x, size_t y, size_t o) {
    u_int32_t res = x;
    res = res << 10;
    res += y;
    res = res << 10;
    res += (int)o;
    return res;
}

inline size_t get_x(int32_t id){
    return (int)(id >> 20);
}

inline size_t get_y(int32_t id){
    return (int)(id >> 10)%(1<<10);
}

inline size_t get_o(int32_t id){
    return (int)id %(1<<10);
}


struct Oriented_Node{
    size_t x;
    size_t y;
    bool o;//only use 0,1, because 2,3 would just reverse the roles of in and out

    Oriented_Node* in = nullptr; // down or left //the oriented_node you came from if you haven't turned here yet
    Oriented_Node* out = nullptr; // up or right //the oriented_node you reach when leaving in current direction

    u_int64_t cost_in = UINT64_MAX; //cost to come here (from in)
    u_int64_t cost_out = UINT64_MAX; //cost to leave (to out)

    //used as memory for path-algorithms
    u_int64_t min_cost_to_reach = UINT64_MAX;
    Oriented_Node* pre = nullptr;//as memory for graph alg

    Oriented_Node() = delete;
    Oriented_Node(int x, int y, size_t o):x(x), y(y), o(o%2){}
};


map<u_int32_t, Oriented_Node> map_to_oriented_maze_nodes(const vector<vector<char>>& maze, const string& walkable = ".") {
    map<u_int32_t, Oriented_Node> res{};

    for(size_t y=0; y<maze.size(); ++y) {
        for(size_t x=0; x<maze[y].size(); ++x){
            if(walkable.contains(maze[y][x])){
                X =
            }
        }
    }
    /*
    int lineNr=0;
    string line;
    fs >> line;
    found_width = line.length();//assume a rectangular shape
    while(fs) {
        for(int i=0; i<line.length(); ++i){
            if(!fillers.contains(line[i])) {
                if (!res.contains(line[i])) {
                    res.insert({line[i], set<pair<int, int>>{}});
                }
                res[line[i]].insert({i, lineNr});
            }
        }
        ++lineNr;
        fs >> line;
    }
    found_height = lineNr;*/
    return res;
}


int main() {
    string filepath = "../2024/16/input";

    vector<vector<char>> map = file_to_char_vector(filepath);

    goal goal{};
    find_pos(map, goal.goal_x, goal.goal_y, "E");

    int start_x;
    int start_y;
    find_pos(map, start_x, start_y, "S");

    //save distances for A*
    size_t h = map.size();
    size_t w = map[0].size();


    //test my id hack for relevant numbers
    for(int y=0; y<h; ++y){
        for(int x=0; x<w; ++x){
            for(size_t o=0; o<10; ++o){
                int32_t id = get_id(x,y,o);
                if(x != get_x(id) || y != get_y(id) || o != get_o(id)) {
                    cout << "ERROR: id Hack not working for (x,y,o) = (" << x << ", " << y << ", " << o <<") -> "
                    << id << " -> (" << get_x(id) << ", " << get_y(id) << ", " << get_o(id) << ")\n";
                }
            }
        }
    }




    cout << sizeof (size_t) <<"\n";

    return 0;
}