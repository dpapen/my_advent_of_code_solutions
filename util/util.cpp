//
// Created by dpapen on 30.11.24.
//

#include "util.h"
#include <fstream>
#include <iostream>
#include <sstream>
#include <set>
#include <map>
#include <iomanip>

using namespace std;

/*
 * using map here (red-black-tree) as relatively few entries are expected, and we don't want the overhead of a hash_map
 */
map<char, set<pair<int,int>>> file_to_char_locations(const string& filepath, int& found_width, int& found_height, const string& fillers) {
    ifstream fs(filepath);

    if(!fs) cout << "ERROR: Couldn't open \""+filepath+"\"\n";

    map<char, set<pair<int,int>>> res{};
    int lineNr=0;
    string line;
    fs >> line;
    found_width = line.length();//assume a rectangular shape
    while(fs) {
        for(int i=0; i<line.length(); ++i){
            if(!fillers.contains(line[i])) {
                if (!res.contains(line[i])) {
                    res.insert({line[i], set<pair<int, int>>{}});
                }
                res[line[i]].insert({i, lineNr});
            }
        }
        ++lineNr;
        fs >> line;
    }
    found_height = lineNr;
    return res;
}


vector<vector<char>> file_to_char_vector(const string& filepath) {
    ifstream fs(filepath);

    if(!fs) cout << "ERROR: Couldn't open \""+filepath+"\"\n";

    vector<vector<char>> res{};
    int lineNr=0;
    string line;
    fs >> line;
    while(fs) {
        res.emplace_back();
        for(char c : line){
            res[lineNr].push_back(c);
        }
        ++lineNr;
        fs >> line; //TODO ignores empty lines! is this desirable?
    }
    return res;
}

void file_to_char_array(const string& filepath, char** res){
    ifstream fs(filepath);

    if(!fs) cout << "ERROR: Couldn't open \""+filepath+"\"\n";
    char tmp;
    int i=0;
    while(fs) {
        fs >> res[0][i];
        ++i;
    }
}


char** file_to_char_array(const string& filepath){
    auto res = new char[140][140]; //TODO get from file
    ifstream fs(filepath);

    if(!fs) cout << "ERROR: Couldn't open \""+filepath+"\"\n";
    char tmp;
    int i=0;
    while(fs) {
        fs >> res[0][i];
        ++i;
    }
    return reinterpret_cast<char **>(res);
}


vector<string> file_to_strings(const string& filepath) {
    ifstream fs(filepath);
    if(!fs) cout << "ERROR: Couldn't open \""+filepath+"\"\n";

    vector<string> res{};
    string line;

    getline(fs, line, '\n');
    //fs >> line;
    while(fs) {
        res.push_back(line);
        getline(fs, line, '\n');
        //fs >> line;
    }

    fs.close();
    return res;
}

vector<string> file_split_on_empty_lines(const string& filepath){
    ifstream fs(filepath);
    if(!fs) cout << "ERROR: Couldn't open \""+filepath+"\"\n";

    vector<string> res{""};
    string line;

    getline(fs, line, '\n');
    //fs >> line;
    while(fs) {
        if(line.empty()) res.emplace_back("");
        else res.back() += line;
        getline(fs, line, '\n');
        //fs >> line;
    }

    fs.close();
    return res;
}


//TODO check behaviour
vector<string> file_split(const string& filepath, string delim){
    ifstream fs(filepath);
    if(!fs) cout << "ERROR: Couldn't open \""+filepath+"\"\n";
    vector<string> res{};
    string read="";
    string entry="";
    getline(fs, read, delim[0]);
    while(fs){
        read = delim[0] + read;
        if(read.starts_with(delim)){
            res.push_back(entry);
            entry = "";
        }
        entry += read;
        getline(fs, read, delim[0]);
    }
    res.push_back(entry);
    return res;
}


void file_to_cols(const string& filepath, vector<string>* res, int cols) {
    string entry;
    ifstream fs(filepath);

    if(!fs) cout << "ERROR: Couldn't open \""+filepath+"\"\n";

    getline(fs, entry, ' ');
    while(fs) {
        for(int i=0; i < cols && fs; ++i){
            res[i].push_back(entry);
            fs >> entry;
        }
    }

    fs.close();
}

void file_to_cols_int(const string& filepath, vector<int>* res, int cols) {
    string entry;
    ifstream fs(filepath);

    if(!fs) cout << "ERROR: Couldn't open \""+filepath+"\"\n";

    getline(fs, entry, ' ');
    while(fs) {
        for(int i=0; i < cols && fs; ++i){
            res[i].push_back(stoi(entry));
            fs >> entry;
        }
    }

    fs.close();
}

vector<string> split_string(const string&s, char delim) {
    vector<string> res{};
    stringstream stream(s);
    string entry;
    getline(stream, entry, delim);
    while(stream) {
        res.push_back(entry);
        getline(stream, entry, delim);//stream >> entry;
    }
    return res;
}

string& string_trim(string& s, const string& by){
    size_t pos = s.find_first_not_of(by);
    s=s.substr(pos, s.find_last_not_of(by)+1-pos);
    return s;
}

std::string to_string(uint64_t val, int width){
    stringstream key("");
    key << setw(width) << setfill('0') << val;
    return key.str();
}


vector<double> string_to_doubles(const string& s) {
    vector<double> res{};
    //TODO
    return res;
}

vector<int> string_to_ints_auto(const string& s) {
    const string valid_chars = "+-0123456789";

    vector<int> res{};
    string::size_type start = 0;
    string::size_type end = 0;
    while(start != string::npos) {
        start = s.find_first_of(valid_chars, start);
        end = s.find_first_not_of(valid_chars, start);
        res.push_back(stoi(s.substr(start, end)));
        start = end;
    }

    return res;
}


vector<int> string_to_ints(const string& s, char delim) {
    vector<int> res{};
    stringstream stream(s);
    string entry;
    getline(stream, entry, delim);
    while(stream) {
        res.push_back(stoi(entry));
        getline(stream, entry, delim);//stream >> entry;
    }
    return res;
}

vector<long long> string_to_longlongs(const string& s, char delim) {
    vector<long long> res{};
    stringstream stream(s);
    string entry;
    getline(stream, entry, delim);
    while(stream) {
        res.push_back(stoll(entry));
        getline(stream, entry, delim);//stream >> entry;
    }
    return res;
}

vector<int> string_to_digits(const string& s) {
    vector<int> res{};
    for(const char& c : s) {
        if('0' <= c && c <= '9') res.push_back(c-'0');
    }
    return res;
}

/*
void sub_written_digits(string& s) { //goes wrong at "eightwothree"
    for(int i=0; i<10; ++i){
        string::size_type pos = s.find(WRITTEN_DIGITS[i], 0);
        while(pos != string::npos) {
            s.replace(pos, WRITTEN_DIGITS[i].size(), to_string(i));
            pos = s.find(WRITTEN_DIGITS[i], pos);
        }
    }
}*/

/*
void sub_written_digits(string& s) { //"twone" -/-> 21?
    for(string::size_type pos = 0; pos < s.length(); ++pos) {
        for(int i=0; i<10; ++i) {
            if (s.substr(pos).starts_with(WRITTEN_DIGITS[i])) {
                s.replace(pos, WRITTEN_DIGITS[i].size(), to_string(i));
            }
        }
    }
}*/

void sub_written_digits(string& s) { //"twone" -/-> 21?
    for(string::size_type pos = 0; pos < s.length(); ++pos) {
        for(int i=0; i<10; ++i) {
            if (s.substr(pos).starts_with(WRITTEN_DIGITS[i])) {
                s.replace(pos, 1, to_string(i));
            }
        }
    }
}

void print_map(const vector<vector<char>>& map, string mark) {
    for(const vector<char>& v : map) {
        for(char c : v) {
            if(mark.contains(c)) cout << "\x1B[31m";
            cout << c;
            if(mark.contains(c)) cout << "\033[0m";
        }
        cout << "\n";
    }
    cout << "\n";
}

size_t find_pos(const vector<vector<char>>& map, int &x, int& y, const string& one_of) {
    for(int r=0; r<map.size(); ++r) {
        for(int c=0; c<map[r].size(); ++c) {
            if (one_of.contains(map[r][c])) {
                x = c;
                y = r;
                return one_of.find_first_of(map[r][c]);
            }
        }
    }
    return string::npos;
}

//TODO void for_each_map_pos(const vector<vector<char>>& map, regular_invocable<>)