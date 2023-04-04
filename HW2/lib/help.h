#pragma once

#include <fstream>
#include <bitset>
#include <iostream>
#include <vector>
#include <unordered_map>
#include <cmath>

#define MAX_SIZE 60

using namespace std;

fstream open_file(string file_path, ios_base::openmode permittion);
bitset<MAX_SIZE> read_in_file(fstream &in, int &size);
vector<int> read_out_file(fstream &out);
bitset<MAX_SIZE> spilt(bitset<MAX_SIZE> board, int size);
bitset<MAX_SIZE> recover(bitset<MAX_SIZE> board, bitset<MAX_SIZE> next_board,  int size, int click);
