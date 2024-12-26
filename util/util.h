//
// Created by dpapen on 30.11.24.
//

#ifndef ADVENT_OF_CODE_UTIL_H
#define ADVENT_OF_CODE_UTIL_H

#include <string>
#include <vector>
#include <set>
#include <map>

const std::string ORIENTATIONS = "^>v<@"; //adding the non-orientation @ so i can just copy this method from day 6
const int DX[]{0, 1, 0, -1};
const int DY[]{-1, 0, 1, 0};

std::map<char, std::set<std::pair<int,int>>> file_to_char_locations(const std::string& filepath, int& found_width, int& found_height, const std::string& fillers = "");
std::vector<std::vector<char>> file_to_char_vector(const std::string& filepath);
void file_to_char_array(const std::string& filepath, char** res);

std::vector<std::string> file_to_strings(const std::string& filepath);
std::vector<std::string> file_split_on_empty_lines(const std::string& filepath);
/*
 * Caution: first entry might not start with delim!
 */
std::vector<std::string> file_split(const std::string& filepath, std::string delim);

void file_to_cols(const std::string& filepath, std::vector<std::string>* res, int cols);
void file_to_cols_int(const std::string& filepath, std::vector<int>* res, int cols);

std::vector<std::string> split_string(const std::string&s, char delim = ' ');
std::string& string_trim(std::string& s, const std::string& by = " \t\n");
std::string to_string(uint64_t val, int width);

std::vector<double> string_to_doubles(const std::string& s);
std::vector<int> string_to_ints_auto(const std::string& s);
std::vector<int> string_to_ints(const std::string& s, char delim = ' ');
std::vector<long long> string_to_longlongs(const std::string& s, char delim = ' ');
std::vector<int> string_to_digits(const std::string& s);

const std::string WRITTEN_DIGITS[] {"zero", "one", "two", "three",  "four", "five", "six", "seven", "eight", "nine"};
void sub_written_digits(std::string& s);

//TODO general substitution method



void print_map(const std::vector<std::vector<char>>& map, std::string mark = "");

//out-of-bounds
bool inline isOutOfBounds(int x, int y, const std::vector<std::vector<char>>& map) {
    return y<0 || y>=map.size() || x<0 || x>=map[y].size();
}

bool inline isOutOfBounds(int x, int y, int w, int h) {
    return y<0 || y>=h || x<0 || x>=w;
}

size_t find_pos(const std::vector<std::vector<char>>& map, int &x, int& y, const std::string& one_of);

#endif //ADVENT_OF_CODE_UTIL_H
