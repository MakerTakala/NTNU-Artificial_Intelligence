#pragma once

#include <fstream>
#include <bitset>
#include <iostream>
#include <vector>
#include <unordered_map>

#define MAX_SIZE 60

using namespace std;

int heurstic(bitset<MAX_SIZE> board);
fstream open_file(string file_path, ios_base::openmode permittion);
bitset<MAX_SIZE> read_in_file(fstream &in, int &size);
vector<int> read_out_file(fstream &out);
bitset<MAX_SIZE> spilt(bitset<MAX_SIZE> board, int size);
bitset<MAX_SIZE> recover(bitset<MAX_SIZE> board, bitset<MAX_SIZE> next_board,  int size, int click);
bool cross_01_judge(bitset<MAX_SIZE> board, vector<int> &ans, int size, int deep, bool is_IDA);
