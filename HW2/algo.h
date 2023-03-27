#pragma once

#include <vector>
#include <fstream>
#include <bitset>
#include <iostream>

using namespace std;

vector<int> IDS(bitset<1000> board, size_t size, fstream &out);
vector<int> IDA(bitset<1000> board, size_t size, fstream &out);

