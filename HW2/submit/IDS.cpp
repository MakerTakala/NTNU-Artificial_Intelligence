#include <fstream>
#include <iostream>
#include <bitset>
#include <vector>
#include <unordered_map>
#include <sys/time.h>
#include <sys/resource.h>

#define MAX_SIZE 60

using namespace std;

bool IDS_search(bitset<MAX_SIZE> board, vector<int> &ans, int deep, int size);
vector<int> IDS(bitset<MAX_SIZE> board, size_t size);
fstream open_file(string file_path, ios_base::openmode permittion);
bitset<MAX_SIZE> read_in_file(fstream &in, int &size);
bitset<MAX_SIZE> spilt(bitset<MAX_SIZE> board, int size);
bitset<MAX_SIZE> recover(bitset<MAX_SIZE> board, bitset<MAX_SIZE> next_board,  int size, int click);



int main(int argc, char *argv[]) {

    // load input data
    fstream in = open_file("./input.txt", ios::in);
    if(in.fail()) return 0;

    // read input
    int size = 0;
    bitset<MAX_SIZE> board = read_in_file(in, size);
    in.close();

    // racord the start time and memory
    rusage start;
    getrusage(RUSAGE_SELF, &start);

    // choose algorithm by argv
    vector<int> ans = IDS(board, size);

    // record end time and memory
    rusage end;
    getrusage(RUSAGE_SELF, &end);

    unsigned long long int ns = 1000000;
    unsigned long long int usage = (end.ru_utime.tv_sec - start.ru_utime.tv_sec) * ns + (end.ru_utime.tv_usec - start.ru_utime.tv_usec);

    fstream out = open_file("./output.txt", ios::out);
    out<<"Total run time = "<<usage / ns<<"."<<usage % ns<<" seconds."<<endl;
    if(ans.size() != 0) {
        out<<"An optional solution has "<<ans.size()<<" moves:"<<endl;
        for(int x : ans) out<<x<<" ";
    }
    else {
        out<<"There is no solution."<<endl;
    }
    out.close();
    
    return 0;
}

// an IDS DFS
bool IDS_search(bitset<MAX_SIZE> board, vector<int> &ans, unordered_map<unsigned long long int, int> &same, int deep, int size) {
    // when all cell has been wipe out, find answer
    if(board == 0) return true;
    
    // over the limited deep
    if(deep == 0) return false;

    if(same[board.to_ullong()] >= deep) return false;
    same[board.to_ullong()] = deep;

    // suppose all cell is split
    bitset<MAX_SIZE> next_board = spilt(board, size);

    // try to wipe out each cell
    for(int i = 0; i < size; i++) {
        bitset<MAX_SIZE> rm_board(next_board);
        if(board[i] == 1) {
            // if a cell be wipe out, recover the board 
            bitset<MAX_SIZE> rec_board = recover(board, next_board, size, i);
            ans.push_back(i + 1);
            if(IDS_search(rec_board, ans, same, deep - 1, size)) return true;
            ans.pop_back();
        }
    }
    return false;
}

// run the IDS algorithm
vector<int> IDS(bitset<MAX_SIZE> board, size_t size) {
    if(size == 0) return vector<int>();
    
    //iterate the deep
    vector<int> ans;
    for(int deep = board.count(); ; deep += 1) {
        unordered_map<unsigned long long int, int> same;
        if(IDS_search(board, ans, same, deep, size)) return ans;
    }
    return vector<int>();
}

// use to opne file;
fstream open_file(string file_path, ios_base::openmode permittion) {
    fstream file;
    file.open(file_path, permittion);
    return file;
}

// use to read the input file
bitset<MAX_SIZE> read_in_file(fstream &in, int &size) {
    string str;
    int in_space;
    while(in>>in_space) {
        str = to_string(in_space) + str;
    }
    size = str.length();
    return bitset<MAX_SIZE>(str); 
}

// use to simulate all cells split
bitset<MAX_SIZE> spilt(bitset<MAX_SIZE> board, int size) {
    bitset<MAX_SIZE> next_board(0);
    for(int i = 0; i < size; i++) {
        if(i == 0) {
            if(board[1]) next_board[0] = 1;
        }
        else if(i == size - 1){
            if(board[size - 2]) next_board[size - 1] = 1;
        }
        else {
            if(board[i - 1] || board[i + 1]) next_board[i] = 1;
        }
    }
    return next_board;
}

// use to recover the borad form all cell spilt when click cell is wiped out
bitset<MAX_SIZE> recover(bitset<MAX_SIZE> board, bitset<MAX_SIZE> next_board,  int size, int click) {
    bitset<MAX_SIZE> rec_board(next_board);
    if(click - 2 < 0 || board[click - 2] == 0) rec_board[click - 1] = 0;
    if(size <= click + 2 || board[click + 2] == 0) rec_board[click + 1] = 0;

    return rec_board;
}
