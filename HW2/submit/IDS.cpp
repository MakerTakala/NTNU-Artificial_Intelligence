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
bool cross_01_judge(bitset<MAX_SIZE> board, vector<int> &ans, int size, int deep);



int main(int argc, char *argv[]) {

    // load input data
    fstream in = open_file("../data/in/1.in", ios::in);
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

    fstream out = open_file("../data/out/1.out", ios::out);
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

bool IDS_search(bitset<MAX_SIZE> board, vector<int> &ans, unordered_map<unsigned long long int, int> &same, int deep, int size) {
    // when all cell has been wipe out, find answer
    if(board == 0 || cross_01_judge(board, ans, size, deep)) return true;
    
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
    if(size == 1) return vector<int>{1};
    
    //iterate the deep
    vector<int> ans;
    for(int deep = 1; ; deep += 1) {
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

bool cross_01_judge(bitset<MAX_SIZE> board, vector<int> &ans, int size, int deep) {
    // filp the board
    // why? beacuse I forget right and left should reverse but I don't want to fix all right and left
    for(int i = 0; i < size / 2; i++) {
        board[i] = board[i] ^ board[size - i - 1];
        board[size - i - 1] = board[i] ^ board[size - i - 1];
        board[i] = board[i] ^ board[size - i - 1];
    }

    int left = 0, right = size - 1;
    while(board[left] == board[0]) left++;
    while(board[right] == board[size - 1]) right--;
    
    if(left > right) return false;
    
    for(int i = left + 1; i <= right; i++) {
        if((board[i] ^ board[i - 1]) == 0) return false;
    }

    bool left_all_0 = true, right_all_0 = true;
    if(left != 0 && board[0] == 1) {
        left_all_0 = false;
        left--;
    }
    if(right != size - 1 && board[size - 1] == 1) {
        right_all_0 = false;
        right++;
    }

    vector<int> tmp_ans;

    // 111 10101 111
    if(left_all_0 == false && right_all_0 == false) {
        int left_1_size = left, right_1_size = size - 1 - right;
        if(left_1_size <= right_1_size) {
            for(int i = left - 1; i >= 1; i--) {
                tmp_ans.push_back(size - i);
                left--;
                right--;
            }
            left_all_0 = true;
        }
        else {
            for(int i = right + 1; i <= size - 2; i++) {
                tmp_ans.push_back(size - i);
                left++;
                right++;
            }
            right_all_0 = true;
        }
    }
    // 111111 10101  or  111 10101 000
    if(left_all_0 == false && right_all_0 == true) {
        for(int i = left - 1; i >= 1; i--) {
            tmp_ans.push_back(size - i);
            left--;
            if(right == size - 1) right = size - 2;
            else right++;
        }
    }

    // 10101 111111  or  000 10101 111
    if(left_all_0 == true && right_all_0 == false) {
        for(int i = right + 1; i <= size - 2; i++) {
            tmp_ans.push_back(size - i);
            right++;
            if(left == 0) left = 1;
            else left--;
        }
        
    }
    
    // 000 10101 000
    if(left <= size - 1 - right)  {
        for(int i = left; i <= size - 2; i++) {
            tmp_ans.push_back(size - i);
        }
    }
    else {
        for(int i = right; i >= 1; i--) {
            tmp_ans.push_back(size - i);
        }
    }

    if((int)tmp_ans.size() > deep) return false;
    
    for(int x : tmp_ans) {
        ans.push_back(x);
    }

    return true;
}
