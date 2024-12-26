//
// Created by dpapen on 30.11.24.
//

#include "util.h"
#include <iostream>
#include <string>

using namespace std;

int main() {
    auto res = file_to_strings("../2023/01/input");
    for(const string& s : res) {
        cout << s <<"\n";
    }

    vector<int> digits = string_to_digits("a1b23c3d756");
    for(int i : digits) {
        cout << i << ",";
    }
    cout << "\n";

    return 0;
}