//
// Created by dpapen on 19.12.24.
//
#include "../../util/util.h"
#include "../../util/BigInt.h"
#include <iostream>
#include <unordered_map>
#include <iomanip>


using namespace std;
/*
class BigInt{ //unsigned atm
    friend ostream& operator<< (ostream& lhs, const BigInt& rhs) {
        std::ios_base::fmtflags old_flags{cout.flags()};
        char old_fill{cout.fill()};
        auto old_width{cout.width()};

        lhs << dec;
        auto d = rhs.digits.crbegin();
        lhs << *d << flush;
        d++;
        while(d != rhs.digits.crend()) {
            lhs << setfill('0') << setw(2);//TODO variable BASE
            lhs << *d;
            d++;
        }

        cout.fill(old_fill);
        cout.width(old_width);
        cout.flags(old_flags);
        return lhs;
    }
private:
    vector<u_int32_t> digits;
    static constexpr u_int32_t BASE = 100;//1000000000;
public:
    [[maybe_unused]] BigInt(u_int64_t val):digits({}) {// NOLINT(*-explicit-constructor) implicit conversion wanted //TODO do we need a delete?
        digits.push_back(val%BASE);
        while(val > BASE) {
            val /= BASE;
            digits.push_back(val%BASE);
        }
    }

    /*[[maybe_unused]]explicit BigInt(u_int32_t val):digits({val}){// NOLINT(*-explicit-constructor) implicit conversion wanted
        if(digits[0] >= BASE){
            digits.push_back(digits[0]/BASE);
            digits[0] = digits[0]%BASE;
        }
    }

    BigInt& operator+= (const BigInt& rhs) {
        u_int32_t carry = 0;
        for(int i=0; i<digits.size() || i < rhs.digits.size(); ++i){
            if(i<digits.size()){
                if(i<rhs.digits.size()) {
                    digits[i] += rhs.digits[i] + carry;
                    carry = digits[i] / BASE;
                    digits[i] = digits[i] % BASE;
                } else {
                    digits[i] += carry;
                    carry = digits[i] / BASE;
                    digits[i] = digits[i] % BASE;
                    if(carry == 0) return *this;
                }
            } else {
                digits.push_back(rhs.digits[i] + carry);
                carry = digits[i] / BASE;
                digits[i] = digits[i] % BASE;
            }
        }
        if(carry != 0){
            digits.push_back(carry);
        }
        return *this;
    }
};

BigInt operator+ (const BigInt& lhs, const BigInt& rhs) {
    BigInt res{lhs};
    res += rhs;
    return res;
}*/

typedef BigInt bigInt;


unordered_map<string, int> mem{};

unsigned long long is_pattern_possible(const string& pattern,const vector<string>& towels) {
    if(pattern.empty()) return 1;
    if(mem.contains(pattern)) return mem.at(pattern);
    unsigned long long res = 0;
    for(const string& t : towels) {
        if(pattern.starts_with(t)){
            res += is_pattern_possible(pattern.substr(t.size()),towels);
        }
    }
    mem.insert({pattern, res});
    return res;
}


/*ostream& operator<<(ostream& lhs, bigInt rhs){
    if(rhs < 0){
        lhs << "-";
        rhs *= -1;
    }
    constexpr unsigned long long step = 10000000000;
    while(rhs > 0){
        lhs << static_cast<unsigned long long>(rhs%step);
        rhs/step;
    }
    return lhs;
}*/

int main() {
    string filepath = "../2024/19/input";

    vector<string> input = file_to_strings(filepath);


    vector<string> towels = split_string(input[0], ',');
    for(string& s : towels) string_trim(s);

    input.erase(input.begin());
    input.erase(input.begin());

    bigInt res{0};
    for(const string& s : input) {
        auto tmp = is_pattern_possible(s, towels);
        cout << s << ": " << tmp << "\n";
        cout << res << " + \n" << tmp << " = \n";
        res += tmp;
        cout << res << "\n\n";
    }

    cout << res << "\n";

/*
    unsigned long long x = UINT64_MAX>>1;
    unsigned long long y = UINT64_MAX>>1;
    x += 4000000;
    y -= 4551614;
    cout << x+y <<"\n";
    cout << BigInt{x}+BigInt{y};*/



    return 0;
}