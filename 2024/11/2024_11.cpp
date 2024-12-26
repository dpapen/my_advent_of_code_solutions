//
// Created by dpapen on 11.12.24.
//
#include "../../util/util.h"
#include <iostream>
#include <list>
#include <cmath>
#include <chrono>
#include <unordered_map>

using namespace std;

unsigned long long calls = 0;
unsigned long long calls_saved = 0;
unsigned long long calculations = 0;

void apply_rules(list<string>& list) {
    for(auto it=list.begin(); it!=list.end(); ++it) {
        if(*it == "0") {
            *it = "1";
        } else if(it->length()%2 == 0) {
            list.insert(it, it->substr(0, it->length()/2));
            size_t pos = it->find_first_not_of("0", it->length()/2);
            *it = (pos==string::npos)?"0":it->substr(pos);
        } else {
            *it = to_string(stoll(*it)*2024);
        }
    }
}

void apply_rules(list<unsigned long long>& list){
    for(auto it=list.begin(); it!=list.end(); ++it) {
        if (*it == 0) {
            *it = 1;
        } else {
            int length = floor(log10(*it))+1;
            if (length % 2 == 0) {
                    long long pow = 1;
                    for(int i=0; i<length/2; ++i) {
                        pow *= 10;
                    }
                    list.insert(it, *it / pow);
                    *it = *it % pow;
            } else {
                *it = *it * 2024;
            }
        }
    }
}

unsigned long long numbers_after_blinks(unsigned long long start, int blinks){
    if(blinks == 0) return 1;
    if (start == 0) {
        if(blinks == 1) return 1;
        return numbers_after_blinks(1, blinks-1);
    } else {
        int length = floor(log10(start))+1;
        if (length % 2 == 0) {
            if(blinks == 1) return 2;
            long long pow = 1;
            for(int i=0; i<length/2; ++i) {
                pow *= 10;
            }
            return numbers_after_blinks(start/pow, blinks-1)
                + numbers_after_blinks(start%pow, blinks-1);
        } else {
            if(blinks == 1) return 1;
            return numbers_after_blinks(start * 2024, blinks-1);
        }
    }
}

unsigned long long numbers_after_blinks(unsigned long long start, int blinks, unordered_map<unsigned long long, map<int,unsigned long long>>& mem){
    ++calls;
    if(mem.contains(start) && mem[start].contains(blinks)){
        calls_saved += blinks-2;
        return mem[start][blinks];
    }

    unsigned long long res;

    if(blinks == 0) {
        res = 1;
    } else if (start == 0) {
        if(blinks == 1) res = 1;
        else res = numbers_after_blinks(1, blinks-1, mem);
    } else {
        int length = floor(log10(start))+1;
        if (length % 2 == 0) {
            if(blinks == 1) res = 2;
            else {
                long long pow = 1;
                for (int i = 0; i < length / 2; ++i) {
                    pow *= 10;
                }
                res = numbers_after_blinks(start / pow, blinks - 1, mem)
                       + numbers_after_blinks(start % pow, blinks - 1, mem);
            }
        } else {
            if(blinks == 1) res = 1;
            else res = numbers_after_blinks(start * 2024, blinks-1, mem);
        }
    }
    if(mem.contains(start)) mem[start].insert({blinks, res});
    else mem.insert({start, map<int, unsigned long long>{{blinks,res}}});

    ++calculations;
    if(calculations % 10000 == 0) cout << "." << flush;

    return res;
}

int main() {
    auto start = chrono::high_resolution_clock::now();
    constexpr int MAX_BLINK = 75;

    unsigned long long res = 0;

    vector<long long> input = string_to_longlongs(file_to_strings("../2024/11/input")[0]);
    unordered_map<unsigned long long, map<int, unsigned long long>> mem;

    for(long long i : input) {
        /*list<unsigned long long> list{static_cast<unsigned long long>(i)};
        for(int i=0; i<75; ++i) {
            cout << i << ": "
                 << chrono::duration_cast<chrono::milliseconds>(chrono::high_resolution_clock::now()-start).count() << "ms "
                 << list.size()
                 << "\n";
            apply_rules(list);
        }
        res += list.size();*/
        cout << i << ": ";
        res += numbers_after_blinks(i, 10000, mem);
        cout << "\n";
    }

    cout << calls << " calls with\n" << calculations << " calcultaions. Memoization saved at least\n" << calls_saved << " calls\n";
    cout << calculations/(double)calls << "calcultations per call\n";
    cout << chrono::duration_cast<chrono::milliseconds>(chrono::high_resolution_clock::now()-start).count() << "ms\n";



    cout << "\n" << res << "\n";

    return 0;
}