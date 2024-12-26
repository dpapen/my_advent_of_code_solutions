//
// Created by dpapen on 24.12.24.
//
#include "../../util/util.h"
#include <iostream>
#include <list>
#include <utility>

using namespace std;

constexpr size_t USED_BITS = 45;//64 would be saver, but this is optimized for the concrete aoc puzzle

class Gate {
    friend ostream& operator<<(ostream& lhs, const Gate& rhs){
        lhs << rhs.out << " = " << rhs.in0 << " " << rhs.type << " " << rhs.in1;
        return lhs;
    }
    friend ostream& print_dependencies(ostream& s, const string& goal, const map<string, Gate>& gates_by_output){
        if(gates_by_output.contains(goal)) {
            const Gate &g = gates_by_output.at(goal);
            s << g.out << "  ( ";
            print_dependencies(s, g.in0, gates_by_output);
            s << " " << g.type << " ";
            print_dependencies(s, g.in1, gates_by_output);
            s << " )";
        }
        else {
            s << goal;
        }

        return s;
    }
    friend void get_dependencies(const string& goal, const map<string, Gate>& gates_by_output, set<pair<string, string>>& dependencies){
        if(gates_by_output.contains(goal)) {
            dependencies.insert({goal, ""});
            const Gate &g = gates_by_output.at(goal);
            get_dependencies(g.in0, gates_by_output, dependencies);
            get_dependencies(g.in1, gates_by_output, dependencies);
        }
    }
private:
    string type; //TODO use enum?
    string in0;
    string in1;
    string out;

public:
    Gate() = delete;

    Gate(string type, string in0, string in1, string out)
            : type(std::move(type)), in0(std::move(in0)), in1(std::move(in1)), out(std::move(out)) {};

    void swap_outputs(Gate& another){
        string tmp = out;
        out = another.out;
        another.out = tmp;
    }

    /*
     * tries to resolve with the given wire values.
     * if sucessfull adds the now known out value to that map and returns true
     * returns false otherwise
     */
    bool resolve(map<string, bool>& known){
        if(known.contains(in0) && known.contains(in1)){
            bool res;
            if(type == "AND") res = known[in0] && known[in1];
            else if(type == "OR") res = known[in0] || known[in1];
            else if(type == "XOR") res = known[in0] ^ known[in1];
            else throw runtime_error("unknown gate-type");

            known.insert({out, res});
            return true;
        }
        else return false;
    }
};

void swap_outputs(const string& out1, const string& out2, map<string, Gate>& gate_by_output){
    gate_by_output.at(out1).swap_outputs(gate_by_output.at(out2));
    swap(gate_by_output.at(out1), gate_by_output.at(out2));
}


/*
 * know is call by reference, as we want to augment it
 * gates_by_output is call by value,
 * for this evaluation we want to erase already processed gates
 * without any side effect
 */
void resolve_network(map<string, bool>& known, map<string, Gate> gates_by_output){
    auto it = gates_by_output.begin();
    bool changed = false;
    while (!gates_by_output.empty()) {
        if (it->second.resolve(known)) {
            it = gates_by_output.erase(it);
            changed = true;
        } else ++it;

        if (it == gates_by_output.end()){
            if(changed) it = gates_by_output.begin();
            else return;
            changed = false;
        }
    }
}

uint64_t get_z(const map<string, bool>& known){
    u_int64_t res{0};

    for(auto it = known.crbegin(); it->first.starts_with('z'); ++it){
        res = res << 1;
        if(it->second) ++res;
    }
    return res;
}

map<string, bool> construct_input(uint64_t x, uint64_t y){
    map<string, bool> res{};
    for(size_t i=0; i<USED_BITS; ++i){
        res.insert({"x"+to_string(i,2), x%2});
        res.insert({"y"+to_string(i,2), y%2});
        x/2;
        y/2;
    }
    return res;
}

list<map<string,bool>> construct_test_inputs(size_t bit){
    list<map<string,bool>> res{};


    map<string, bool> zero{};
    for(size_t i=0; i < USED_BITS; ++i){
        zero.insert({"x"+ to_string(i,2), 0});
        zero.insert({"y"+ to_string(i,2), 0});
    }
    //0,0,0 -> 0
    zero["x"+ to_string(bit,2)] = 0;
    zero["y"+ to_string(bit,2)] = 0;
    zero["expected"+ to_string(bit,2)] = 0;
    res.push_back(zero);
    //0,1,0 -> 1
    zero["x"+ to_string(bit,2)] = 0;
    zero["y"+ to_string(bit,2)] = 1;
    zero["expected"+ to_string(bit,2)] = 1;
    res.push_back(zero);
    //1,0,0 -> 1
    zero["x"+ to_string(bit,2)] = 1;
    zero["y"+ to_string(bit,2)] = 0;
    zero["expected"+ to_string(bit,2)] = 1;
    res.push_back(zero);
    //1,1,0 -> 0
    zero["x"+ to_string(bit,2)] = 1;
    zero["y"+ to_string(bit,2)] = 1;
    zero["expected"+ to_string(bit,2)] = 0;
    res.push_back(zero);


    if(bit>0) {
        //try to start with a carry-over
        zero["x"+ to_string(bit-1,2)] = 1;
        zero["y"+ to_string(bit-1,2)] = 1;
        //0,0,1 -> 1
        zero["x"+ to_string(bit,2)] = 0;
        zero["y"+ to_string(bit,2)] = 0;
        zero["expected"+ to_string(bit,2)] = 1;
        res.push_back(zero);
        //0,1,1 -> 0
        zero["x"+ to_string(bit,2)] = 0;
        zero["y"+ to_string(bit,2)] = 1;
        zero["expected"+ to_string(bit,2)] = 0;
        res.push_back(zero);
        //1,0,1 -> 0
        zero["x"+ to_string(bit,2)] = 1;
        zero["y"+ to_string(bit,2)] = 0;
        zero["expected"+ to_string(bit,2)] = 0;
        res.push_back(zero);
        //1,1,1 -> 1
        zero["x"+ to_string(bit,2)] = 1;
        zero["y"+ to_string(bit,2)] = 1;
        zero["expected"+ to_string(bit,2)] = 1;
        res.push_back(zero);

    }

    return res;
}

int test(const map<string, Gate>& gates_by_output, bool verbose) {
    int res = 0;
    for(int bit=0; bit < USED_BITS; ++bit){
        auto tests = construct_test_inputs(bit);
        for(auto t : tests){
            resolve_network(t,gates_by_output);
            if(t["z"+ to_string(bit, 2)] != t["expected"+ to_string(bit,2)]){
                ++res;
                if(verbose) {
                    //error found in calculation of tested bit
                    cout << "bit " << bit << " is faulty (" << t.at("x" + to_string(bit, 2))
                         << t.at("y" + to_string(bit, 2)) << "->" << t.at("z" + to_string(bit, 2))
                         << ") and uses gates: ";
                    print_dependencies(cout, "z"s + to_string(bit, 2), gates_by_output);
                    cout << "\n";
                }
                //break;//we know the calculation of this bit is erroneous no further tests needed
            }
        }
    }
    return res;
}

int main() {
    string filepath = "../2024/24/input";
    vector<string> input = file_to_strings(filepath);

    map<string, bool> known{};
    map<string, Gate> gates_by_output{};

    {//scope setup
        vector<string> tmp;
        for (const string &line: input) {
            if (line.empty() || line.starts_with('#')) continue;
            if (line.contains(':')) {//initial value
                tmp = split_string(line, ':');
                known.insert({tmp[0], stoi(tmp[1])});
            } else {//logical gate
                tmp = split_string(line, ' ');
                gates_by_output.insert({tmp[4], Gate(tmp[1], tmp[0], tmp[2], tmp[4])});
            }
        }
    }//end scope setup

    //part 1
    resolve_network(known, gates_by_output);
    cout << "z = " << get_z(known) << "\n";

    //part 2
    //print out gates for debugging;
    for(const auto& g : gates_by_output) cout << g.second <<"\n";
    cout << "\n";

    //swap

    /*
    swap_outputs("z23", "qdg", gates_by_output);
    swap_outputs("z23","cgq", gates_by_output);
    */
    swap_outputs("bdr", "pbd", gates_by_output);
    swap_outputs("cgq", "z23", gates_by_output);
    swap_outputs("svm", "nbc", gates_by_output);
    swap_outputs("kqk", "dkk", gates_by_output);



    set<pair<string, string>> dependencies{};//second string is only a dummy so we can reuse the code with first
    set<pair<string, string>> dependencies2{};
    int min = test(gates_by_output, true);
    int tmp;
    cout << "starting with "<< min << " errors:\n";

    get_dependencies("z15", gates_by_output, dependencies);
    get_dependencies("z39", gates_by_output, dependencies2);

    for(const auto& swp1 : gates_by_output){
        cout << "\n" << swp1.first << "\n";
        for(const auto& swp2 : dependencies2){
            swap_outputs(swp1.first, swp2.first, gates_by_output);
            tmp = test(gates_by_output, false);
            if(tmp<min){
                min = tmp;
                cout << "swapping "<<swp1.first<<" and "<<swp2.first<< " has only "<< min<< " errors";
                if(min == 0) return 0;
            }
            swap_outputs(swp1.first, swp2.first, gates_by_output);
        }
    }


    cout << "fin";

    return 0;
}