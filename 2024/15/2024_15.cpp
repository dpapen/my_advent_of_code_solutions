//
// Created by dpapen on 15.12.24.
//
#include "../../util/util.h"
#include <iostream>


using namespace std;

void findPos(const vector<vector<char>> &map, int &x, int &y, int &orientation) {
    for (int r = 0; r < map.size(); ++r) {
        //auto tmp = std::find_first_of(map[r].begin(), map[r].end(), ORIENTATIONS.begin(), ORIENTATIONS.end());
        for (int c = 0; c < map[r].size(); ++c) {
            if (ORIENTATIONS.contains(map[r][c])) {
                x = c;
                y = r;
                for (int i = 0; i < ORIENTATIONS.size(); ++i) {
                    if (ORIENTATIONS[i] == map[r][c]) {
                        orientation = i;
                        return;
                    }
                }
            }
        }
    }
}

//algorithmicly more a can_make_space
bool can_move(int x, int y, size_t o, const vector<vector<char>> &map) {
    if (isOutOfBounds(x, y, map)) return false;

    switch (map[y][x]) {
        case '.':
            return true;
        case '#':
            return false;
        case '[': //use default if left or right
            if (o % 2 == 0 && !can_move(x + DX[o] + 1, y + DY[o], o, map))
                return false;//op or down, if other half can't be pushed
            return can_move(x + DX[o], y + DY[o], o, map); //fallthrough would check the other side as well
        case ']': //use default if left or right
            if (o % 2 == 0 && !can_move(x + DX[o] - 1, y + DY[o], o, map))
                return false; //op or down, if other half can't be pushed
            return can_move(x + DX[o], y + DY[o], o, map);
        default: //including '@' and 'O'
            return can_move(x + DX[o], y + DY[o], o, map);
    }
}

void force_move(int x, int y, size_t o, vector<vector<char>> &map) {
    if (isOutOfBounds(x, y, map)) return;

    char c = map[y][x];
    map[y][x] = '.';
    switch (c) {
        case '.':
            return;
        case '[': //use default if left or right
            if (o % 2 == 0) {//up and down
                map[y][x+1] = '.';
                force_move(x + DX[o] + 1, y + DY[o], o, map);
                force_move(x + DX[o], y + DY[o], o, map);
                map[y+DY[o]][x+DX[o]+1] = ']';
                break;
            }
        case ']'://use default if left or right
            if (o % 2 == 0) {//up and down
                map[y][x-1] = '.';
                force_move(x + DX[o] - 1, y + DY[o], o, map);
                force_move(x + DX[o], y + DY[o], o, map);
                map[y+DY[o]][x+DX[o]-1] = '[';
                break;
            }
        default:
            force_move(x + DX[o], y + DY[o], o, map);
    }
    map[y+DY[o]][x+DX[o]] = c;
}

struct bot {
    int x;
    int y;
    vector<vector<char>> &map;

    void move(char orientation) {
        size_t o = ORIENTATIONS.find(orientation);
        if (o > 3) return; //o is unsigned

        vector<char> push_stack{};
        for (int x2 = x, y2 = y; !isOutOfBounds(x2, y2, map); x2 += DX[o], y2 += DY[o]) {
            char c = map[y2][x2];
            if (c == '#') break; //not possible leave loop without doing something
            if (c == '.') {
                while (!push_stack.empty()) {
                    map[y2][x2] = push_stack.back();
                    push_stack.pop_back();
                    x2 -= DX[o];
                    y2 -= DY[o];
                }
                map[y][x] = '.';
                x += DX[o];
                y += DY[o];
                break;
            }
            push_stack.push_back(c);
        }
    }

    void move2(char orientation) {
        size_t o = ORIENTATIONS.find(orientation);
        if (o > 3) return; //o is unsigned
        if (can_move(x, y, o, map)) {
            force_move(x, y, o, map);
            x += DX[o];
            y += DY[o];
        }
    }

    void set_orientation(char o) {
        map[y][x] = o;
    }
};


int gps_coordinate_sum(const vector<vector<char>> &map) {
    int res = 0;
    for (int y = 0; y < map.size(); ++y) {
        for (int x = 0; x < map[y].size(); ++x) {
            if ("O["s.contains(map[y][x])) res += 100 * y + x;
        }
    }

    return res;
}

vector<vector<char>> stretch(const vector<vector<char>> &map) {
    vector<vector<char>> res{};
    for (const vector<char>& v: map) {
        res.emplace_back();
        for(char c: v) {
            switch (c) {
                case '@':
                    res.back().push_back('@');
                    res.back().push_back('.');
                    break;
                case 'O':
                    res.back().push_back('[');
                    res.back().push_back(']');
                    break;
                default:
                    res.back().push_back(c);
                    res.back().push_back(c);
            }
        }
    }
    return res;
}


int main() {
    string filepath = "../2024/15/example2";

    //import map
    vector<vector<char>> map = file_to_char_vector(filepath);
    std::erase_if(map, [](const vector<char> &v) { return v.empty() || v[0] != '#'; });
    //stretch map for part 2
    map = stretch(map);

    //import instructions
    string instructions;
    for (const string &s: file_to_strings(filepath)) {
        if (!s.empty() && s[0] != '#') instructions += s;
    }

    int x = 0;
    int y = 0;
    int o;//ignored here
    findPos(map, x, y, o);

    bot bot = {x, y, map};

    print_map(map);

    for (char c: instructions) {
        bot.move2(c);
        bot.set_orientation(c);
        cout << "Move " << c << ":\n";
        print_map(map, ORIENTATIONS);
        //sleep(1);
    }

    bot.set_orientation('@');
    print_map(map, ORIENTATIONS);

    cout << gps_coordinate_sum(map) << "\n";

    return 0;
}