//
// Created by dpapen on 30.11.24.
//

#include "../../util/util.h"
#include <iostream>
#include <vector>

using namespace std;

int main() {
    vector<string> input = file_to_strings("../2023/01/input");
    vector<int> digits;
    int calibration = 0;
    /*for(const string& s : input){
        digits = string_to_digits(s);
        calibration += digits.front()*10 + digits.back();
    }
    cout << calibration << "\n";
*/
    cout << "\n---------------------------------------------\n\n";

    calibration = 0;
    for(string& s : input){
        cout << s << " --> ";
        sub_written_digits(s);
        cout << s << " --> ";
        digits = string_to_digits(s);
        cout << digits.front() << digits.back() << "\n";
        calibration += digits.front()*10 + digits.back();
    }
    cout << calibration << "\n";

    return 0;
}