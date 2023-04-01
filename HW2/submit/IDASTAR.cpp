#include <fstream>
#include <iostream>
#include <bitset>
#include <vector>
#include <sys/time.h>
#include <sys/resource.h>

#define MAX_SIZE 60

using namespace std;

int heurstic(bitset<MAX_SIZE> board);
int IDA_search(bitset<MAX_SIZE> board, vector<int> &ans, int deep, int size);
vector<int> IDA(bitset<MAX_SIZE> board, size_t size);
fstream open_file(string file_path, ios_base::openmode permittion);
bitset<MAX_SIZE> read_in_file(fstream &in, int &size);
bitset<MAX_SIZE> spilt(bitset<MAX_SIZE> board, int size);
bitset<MAX_SIZE> recover(bitset<MAX_SIZE> board, bitset<MAX_SIZE> next_board,  int size, int click);
bool cross_01_judge(bitset<MAX_SIZE> board, vector<int> &ans, int size, int deep);

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
    vector<int> ans = IDA(board, size);

    // record end time and memory
    rusage end;
    getrusage(RUSAGE_SELF, &end);

    unsigned long long int ns = 1000000;
    unsigned long long int usage = (end.ru_utime.tv_sec - start.ru_utime.tv_sec) * ns + (end.ru_utime.tv_usec - start.ru_utime.tv_usec);

    fstream out = open_file("c:\\output.txt", ios::out);
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

int heurstic(bitset<MAX_SIZE> board) {
    return board.count();
}

int IDA_search(bitset<MAX_SIZE> board, vector<int> &ans, int deep, int size) {
    // when all cell has been wipe out, find answer
    if(board == 0) return 0;

    // over the limited deep
    if(deep < 0) return deep;

    // suppose all cell is split
    bitset<MAX_SIZE> next_board = spilt(board, size);
    
    // use deep_update to record the maxinum change
    int deep_update = INT_MIN;
    // try to wipe out each cell
    for(int i = 0; i < size; i++) {
        bitset<MAX_SIZE> rm_board(next_board);
        if(board[i] == 1) {
            // if a cell be wipe out, recover the board 
            bitset<MAX_SIZE> rec_board = recover(board, next_board, size, i);
            ans.push_back(i + 1);

            int deep_diff = IDA_search(rec_board, ans, deep - (1 + heurstic(rec_board)), size);
            if(deep_diff == 0) return 0;
            
            deep_update = max(deep_update, deep_diff);
            ans.pop_back();
        }
    }
    return deep_update;
}

// run the IDA algorithm
vector<int> IDA(bitset<MAX_SIZE> board, size_t size) {
    if(size == 1) return vector<int>{1};

    //iterate the deep
    vector<int> ans;
    for(int deep = 1; ;) {
        int deep_update= IDA_search(board, ans, deep, size);
        if(deep_update == 0) return ans;
        deep -= deep_update;
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

bool cross_01_judge(bitset<MAX_SIZE> board, vector<int> &ans, int size, int deep) {
    int right = 0, left = size - 1;
    while(!board[right]) right++;
    while(!board[left]) left--;

    if(right == left) {
        ans.push_back(left + 1);
        return true;
    }

    for(int i = right + 1; i <= left; i++) {
        if((board[i] ^ board[i - 1]) == 0) return false;
    }

    int right_space = right, left_space = size - 1 - left;

    if(right_space >= left_space)  {
        if(size - right - 1 > deep + 1) return false;
        for(int i = right; i <= size - 2; i++) {
            ans.push_back(i + 1);
        }
    }
    else {
        if(left > deep + 1) return false;
        for(int i = left; i >= 1; i--) {
            ans.push_back(i + 1);
        }
    }
    return true;
}