//
// Created by dpapen on 05.12.24.
//
#include "../../util/util.h"
#include <fstream>
#include <iostream>
#include <set>

using namespace std;

bool check(const vector<int>& series, const set<pair<int,int>>& rules) {
    for(int i=0; i<series.size(); ++i) {
        for(int j=i+1; j<series.size(); ++j) {
            if(rules.contains({series[j],series[i]})) return false;
        }
    }
    return true;
}

void correct(vector<int>& series, const set<pair<int,int>>& rules) {
    for(int i=0; i<series.size(); ++i) {
        for(int j=i+1; j<series.size(); ++j) {
            if(rules.contains({series[j],series[i]})) {
                swap(series[i], series[j]);
                correct(series, rules);
                return;
            }
        }
    }
}

int main() {
    vector<string> input = file_to_strings("../2024/05/input");
    int res = 0;
    int corrected = 0;
    set<pair<int, int>> rules{};
    vector<int> v;
    for(const string& s : input) {
        if(s.contains('|')){
            v = string_to_ints(s, '|');
            rules.insert({v[0], v[1]});
        } else if(!s.empty()) { //check sequence
            v = string_to_ints(s, ',');
            if(check(v, rules)) {
                res += v[v.size()/2];
            } else {
                correct(v, rules);
                corrected += v[v.size()/2];
            }
        }
    }

    cout << res << "\n";
    cout << corrected << "\n";
    return 0;
}