#include "./help.h"

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

vector<int> read_out_file(fstream &out) {
    vector<int> ans;
    int x;
    while(out>>x) {
        ans.push_back(x);
    }
    return ans;
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

