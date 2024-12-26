//
// Created by dpapen on 13.12.24.
//
#include "../../util/util.h"
#include <iostream>

using namespace std;

inline long det(long m[2][2]) {
    return m[0][0]*m[1][1]-m[0][1]*m[1][0];
}

inline void quasi_invert(long m[2][2]) {
    swap(m[0][0], m[1][1]);
    swap(m[0][1], m[1][0]);
    m[0][1] *= -1;
    m[1][0] *= -1;
}

inline void  matr_mult(const long m[2][2], long v[2]) {
    long tmp = m[0][0]*v[0]+m[0][1]*v[1];
    v[1] = m[1][0]*v[0]+m[1][1]*v[1];
    v[0] = tmp;
}


int main() {
    vector<string> input = file_to_strings("../2024/13/input");
    input.emplace_back("");//to trigger the last calculation

    vector<int> v;
    unsigned long long res = 0;

    for(const string& s : input) {
        if(s.empty() && !v.empty()) {
            if(v.size() == 6) {
                long a[2][2] = {{v[0], v[1]},{v[2],v[3]}};
                long b[2] = {v[4]+10000000000000,  v[5]+10000000000000};
                long d = det(a);
                if(d == 0) cout << "not invertable: skipping as no solution is implemented yet\n";
                else{
                    quasi_invert(a);
                    matr_mult(a,b);
                    if(b[0]%d != 0 || b[1]%d !=0) cout << "no integer solution: skipped\n";
                    else res += (3*b[0]+1*b[1])/d;
                }
            }
            else cout << "somethings wrong only " << v.size() << " numbers read!\n";
            v.clear();
        } else {
            v.push_back(stoi(s.substr(s.find('X') + 2, s.find(','))));
            v.push_back(stoi(s.substr(s.find('Y') + 2, string::npos)));
        }
    }

    /*
    vector<int> a = string_to_ints(input[0].substr(12, pos), ',');
    vector<int> b = string_to_ints(input[1], ',');
    vector<int> p = string_to_ints(input[2], ',');
*/
    cout << res << "\n";


    return 0;
}