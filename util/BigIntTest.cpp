//
// Created by dpapen on 23.12.24.
//

#include "BigInt.h"
#include <sstream>
#include <cassert>

using namespace std;

int main() {

    stringstream s("");
    stringstream t("");
    for(u_int64_t i=0; i<UINT16_MAX; ++i){
        for(u_int64_t j=0; j<UINT8_MAX-i; ++j){
            s.str("");
            t.str("");
            s << BigInt{i}+BigInt{j};
            t << BigInt{i+j};
            if(s.str() != t.str() || s.str()!= to_string(i+j)){
                cout << i << ", " << j << ":" << s.str() << " vs " << t.str() << " vs " <<
                to_string(i+j)<< "\n";
                cout << "\n";
            };
        }
        //cout << ".";
    }
    cout << "done";



    return 0;
}