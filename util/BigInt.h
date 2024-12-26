//
// Created by dpapen on 23.12.24.
//

#ifndef ADVENT_OF_CODE_BIGINT_H
#define ADVENT_OF_CODE_BIGINT_H

#include <iostream>
#include <vector>


class BigInt{ //unsigned atm
    friend std::ostream& operator<< (std::ostream& lhs, const BigInt& rhs);
private:
    std::vector<u_int32_t> digits;
    static constexpr u_int32_t BASE = 100;//1000000000;
public:
    BigInt(u_int64_t val):digits({}) {// NOLINT(*-explicit-constructor) implicit conversion wanted //TODO do we need a delete?
        digits.push_back(val%BASE);
        while(val >= BASE) {
            val /= BASE;
            digits.push_back(val%BASE);
        }
    }

    BigInt& operator+= (const BigInt& rhs);
};

inline BigInt operator+ (const BigInt& lhs, const BigInt& rhs) {
    BigInt res{lhs};
    res += rhs;
    return res;
}

#endif //ADVENT_OF_CODE_BIGINT_H
