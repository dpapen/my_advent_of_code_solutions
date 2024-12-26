//
// Created by dpapen on 07.12.24.
//

#include "../../util/util.h"
#include <fstream>
#include <iostream>
#include <vector>
#include <string>

using namespace std;

bool check(long long result, const vector<long long>& inputs, const string& operators, bool optimized = false) {
    //trivial cases
    if(inputs.empty()) return false;
    if(inputs.size() == 1) return inputs[0] == result;
    //optimization if there is no operator making numbers smaller
    if(optimized) {
        if(inputs[0] > result) return false;
    }
    //reduce length and make recursive call
    for(char op : operators) {
        vector<long long> shortened = inputs;
        shortened.erase(shortened.begin());
        switch (op) {
            case '+': shortened[0] = inputs[0] + inputs[1];
                        break;
            case '*': shortened[0] = inputs[0] * inputs[1];
                        break;
            case '|': shortened[0] = stoll(to_string(inputs[0])+ to_string(inputs[1]));
                break;
        }
        if(check(result, shortened, operators)) return true;
    }
    return false;
}

int main() {
    vector<string> input = file_to_strings("../2024/07/input");

    long long res = 0;
    for(const string& s : input) {
        long long test_value = string_to_longlongs(s, ':')[0];
        vector<long long> numbers = string_to_longlongs(s.substr(to_string(test_value).length()+2), ' ');
        if(check(test_value, numbers, "+*", true)) res += test_value;
    }
    cout << res << "\n";

    //PART 2:

    res = 0;
    for(const string& s : input) {
        long long test_value = string_to_longlongs(s, ':')[0];
        vector<long long> numbers = string_to_longlongs(s.substr(to_string(test_value).length()+2), ' ');
        if(check(test_value, numbers, "+*|", true)) res += test_value;
    }
    cout << res << "\n";
    return 0;
}