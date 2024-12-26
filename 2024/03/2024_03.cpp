//
// Created by dpapen on 03.12.24.
//

#include "../../util/util.h"
#include <iostream>
#include <vector>

#include <chrono>
#include <sstream>

using namespace std;

int main() {
    vector<string> input = file_split("../2024/03/input", "mul(");
    //check if first entry starts with mul(
    if(!input[0].starts_with("mul(")) input.erase(input.begin());
    int res = 0;
    bool doing = true;
    for(string s : input) {
        cout << s << "\n";
        stringstream stream(s.substr(4));
        string entry;
        getline(stream, entry, ',');
        try {
            int a = stoi(entry);
            if(entry == to_string(a)) {
                getline(stream, entry);
                int b = stoi(entry);
                if (entry.starts_with(to_string(b) + ")")) {
                    if (doing) res += a * b;
                    cout << "-->" << a << "*" << b << "=" << a * b << "-->" << res << "\n";
                }
            }
        } catch(std::invalid_argument){
            //ignore this s
        }
        std::reverse(s.begin(), s.end());
        int enable = s.find(")(od");
        int disable = s.find(")(t'nod");
        if(enable != string::npos && (enable < disable || disable == string::npos)) {
            doing = true;
            cout << "DO \n";
        }
        if(disable != string::npos && (disable < enable || enable == string::npos)) {
            doing = false;
            cout << "DONT \n";
        }
    }
    cout << res;
    return 0;
}
