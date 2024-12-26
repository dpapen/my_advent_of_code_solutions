//
// Created by dpapen on 17.12.24.
//
#include "../../util/util.h"
#include <iostream>
#include <sstream>

using namespace std;

void run_program(const vector<int> &program, u_int64_t a_init, u_int64_t b_init, u_int64_t c_init, ostream &os = cout,
                 bool halt_on_output = false) {
    u_int64_t combo[8] = {0, 1, 2, 3, a_init, b_init, c_init, 0};
    u_int64_t *a = &combo[4];
    u_int64_t *b = &combo[5];
    u_int64_t *c = &combo[6];

    int instr_ptr = 0;

    while (instr_ptr < program.size()) {
        switch (program[instr_ptr]) {
            case 0://adv
                *a = *a >> combo[program[instr_ptr + 1]];
                break;
            case 1://bxl
                *b = *b ^ program[instr_ptr + 1];
                break;
            case 2://bst
                *b = combo[program[instr_ptr + 1]] % 8;
                break;
            case 3://jnz
                if (*a != 0) instr_ptr = program[instr_ptr + 1] - 2;//will add 2 again later
                break;
            case 4://bxc
                *b = *b ^ *c;
                break;
            case 5://out
                os << combo[program[instr_ptr + 1]] % 8 << ",";
                if (halt_on_output) return;
                break;
            case 6://bdv
                *b = *a >> combo[program[instr_ptr + 1]];
                break;
            case 7://cdv
                *c = *a >> combo[program[instr_ptr + 1]];
                break;
        }
        instr_ptr += 2;
    }
}

//assuming we can jest set b=c=0 mid programm without changing the result
u_int64_t guess_next_digits(const vector<int> &program, int bitshift, const u_int64_t a_offset, int index) {
    u_int64_t res = UINT64_MAX;
    for (u_int64_t i = 0; i<(1<<bitshift); ++i) {
        stringstream s;
        run_program(program, a_offset+i, 0, 0, s, true);
        if (s.str() == to_string(program[index]) + ",") {
            res = a_offset+i;

            cout << "\ni: "<<index<<" res= "<< res << " Pre : ";
            run_program(program, res, 0, 0);

            if (index > 0)  res = guess_next_digits(program, bitshift, res<<bitshift, index-1);

            cout << "\ni: "<<index<<" res= "<< res << " Pre : ";
            run_program(program, a_offset, 0, 0);

            if(res < UINT64_MAX) return res;//TODO does this allow named_return_value_optimization, question originated from return by-value-param
        }
    }
    return res; //return UINT64_MAX; //TODO do i need to write it to a_offset myself or is NRVO clever enough?
}

int main() {
    string filename = "../2024/17/input";
    vector<string> input = file_to_strings(filename);
    vector<int> program = string_to_ints_auto(input[4]);

    //PART 1:
    run_program(program,
                string_to_ints_auto(input[0])[0],
                string_to_ints_auto(input[1])[0],
                string_to_ints_auto(input[2])[0]);

    //PART 2:
    string goal = split_string(input[4], ' ')[1] + ",";
    //bruteforce
    /*
    u_int64_t limit = UINT64_MAX;
    for (u_int64_t i = UINT32_MAX / 2; i < limit; ++i) {//until wraparound
        if (i % (2 << 21) == 0) cout << (100.0 * i) / limit << "%\n";
        stringstream s;
        run_program(program, (int) i, 0, 0, s);
        if (s.str() == goal) {
            cout << "Solution A = " << i << "\n";
            return 0;
        }
    }
    */
    //one output at a time
    cout << oct << "\nPritning everything in octal!";
    u_int64_t current_guess = guess_next_digits(program, 3, 0, program.size()-1);

    cout << "\n\nsolution A(oct) = " << current_guess << "\n";
    run_program(program,
                current_guess,
                string_to_ints_auto(input[1])[0],
                string_to_ints_auto(input[2])[0]);
    cout << "\n";
    for(int i : program) cout << i << ",";

    cout << dec << "\nA(dec) = "<< current_guess << "\n";
    return 0;
}