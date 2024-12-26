//
// Created by dpapen on 25.12.24.
//
#include "../../util/util.h"
#include <iostream>

using namespace std;

int main() {
    string filepath = "../2024/25/input";
    vector<string> input = file_split_on_empty_lines(filepath);

    set<u_int32_t> locks{};
    set<u_int32_t> keys{};

    for(const string& s : input){
        u_int32_t bit_code = 0;
        for(int i=5; i<30; ++i){
            if(s[i] == '#') ++bit_code;
            bit_code = bit_code << 1;
        }

        if(s.starts_with('#')) locks.insert(bit_code);
        else keys.insert(bit_code);
    }

    //part 1
    u_int64_t res = 0;
    for(u_int32_t l : locks){
        for(u_int32_t k : keys){
            if(!(l & k)) ++res;
        }
    }


    cout << res << "\n";

    return 0;
}