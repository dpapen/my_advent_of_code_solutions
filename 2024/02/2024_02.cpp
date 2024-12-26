//
// Created by dpapen on 02.12.24.
//

#include "../../util/util.h"
#include <iostream>
#include <vector>

#include <chrono>

using namespace std;

bool is_safe(vector<int> ints) {
    int tmp = ints.front()-1;
    bool safe = true;
    for(int val : ints) {
        if(val <= tmp || val > tmp+3 ){
            safe = false;
            break;
        }
        tmp = val;
    }
    if(safe) {
        //cout << "ascending";
        return true;
    }
    //if not check safely decreasing
    tmp = ints.front() + 1;
    safe = true;
    for (int val: ints) {
        if (val >= tmp || val < tmp - 3) {
            safe = false;
            break;
        }
        tmp = val;
    }
    if (safe) {
        //cout << "descending";
        return true;
    }
    return false;
}

int main() {
    vector<string> input = file_to_strings("../2024/02/input");

    int safe_counter = 0;
    for(const string& s : input) {
        //cout << "\n" << s << "-->";
        vector<int> ints = string_to_ints(s);
        if(is_safe(ints))  ++safe_counter;
        else{
            for(int i=0; i<ints.size(); ++i) {
                vector<int> c;
                copy(ints.begin(), ints.end(), back_inserter(c));
                c.erase(c.begin()+i);
                if(is_safe(c)){
                    ++safe_counter;
                    break;
                }
            }
        }
    }

    cout << safe_counter;

    return 0;
}