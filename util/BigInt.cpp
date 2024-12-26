//
// Created by dpapen on 23.12.24.
//

#include "BigInt.h"
#include <iomanip>

using namespace std;

ostream& operator<< (ostream& lhs, const BigInt& rhs) {
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

BigInt& BigInt::operator+= (const BigInt& rhs) {
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