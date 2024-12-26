//
// Created by dpapen on 01.12.24.
//

#include "../../util/util.h"
#include <iostream>
#include <vector>

#include <chrono>

using namespace std;

int main() {
    auto start = chrono::high_resolution_clock::now();
    vector<int> input[2];
    file_to_cols_int("../2024/01/input", input, 2);
    auto stop = chrono::high_resolution_clock::now();
    cout << "file reading: " << chrono::duration_cast<chrono::microseconds>(stop-start).count() << "µs\n";

    start = chrono::high_resolution_clock::now();

    std::sort(input[0].begin(), input[0].end());
    std::sort(input[1].begin(), input[1].end());

    int res = 0;
    while(!input[0].empty()) {
        res += abs(input[0].back() - input[1].back());
        input[0].pop_back();
        input[1].pop_back();
    }
    cout << res << "\n";
    stop = chrono::high_resolution_clock::now();
    cout << chrono::duration_cast<chrono::microseconds>(stop-start).count() << "µs\n";


    cout << "\n----------------Part2------------------\n\n";

    file_to_cols_int("../2024/01/input", input, 2);

    start = chrono::high_resolution_clock::now();

    int similarity_score = 0;
    for(int left : input[0]) {
        similarity_score += left * count(input[1].begin(), input[1].end(),left);
    }

    cout << similarity_score << "\n";

    stop = chrono::high_resolution_clock::now();
    cout << chrono::duration_cast<chrono::microseconds>(stop-start).count() << "µs\n";

    cout << "\n----------------Part2 (make use of sorting)------------------\n\n";

    start = chrono::high_resolution_clock::now();

    std::sort(input[0].begin(), input[0].end());
    std::sort(input[1].begin(), input[1].end());
    similarity_score = 0;
    int l = 0;
    int r = 0;
    int left;
    int right;
    while(l<input[0].size() && r<input[1].size()) {
        left = input[0][l];
        right = input[1][r];
        if(left < right) l++;
        else if (left == right){
                int lm = 0;
                while(input[0][l] == left){
                    ++lm;
                    ++l;
                }
                int rm = 0;
                while(input[1][r] == right){
                    ++rm;
                    ++r;
                }
                similarity_score += left * lm * rm;
            }
        else ++r;
    }

    cout << similarity_score << "\n";
    stop = chrono::high_resolution_clock::now();
    cout << chrono::duration_cast<chrono::microseconds>(stop-start).count() << "µs\n";

    return 0;
}