#include <fstream>
#include <iostream>
#include <bitset>
#include <vector>
#include <unordered_map>
#include <sys/time.h>
#include <sys/resource.h>

#define MAX_SIZE 60

using namespace std;

int heurstic(bitset<MAX_SIZE> board);
bool CLI_serch(bitset<MAX_SIZE> board, vector<int> &ans, size_t size);
vector<int> CLI(bitset<MAX_SIZE> board, size_t size);
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
    vector<int> ans = CLI(board, size);

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

int heurstic(bitset<MAX_SIZE> board) {
    return board.count();
}

bool CLI_serch(bitset<MAX_SIZE> board, vector<int> &ans, size_t size) {
    while(1) {
        if(board == 0) return true;

        // suppose all cell is split
        bitset<MAX_SIZE> next_board = spilt(board, size);

        vector<bitset<MAX_SIZE>> candicate_rec_board;
        vector<int> candicate_click;

        int MIN_h = INT_MAX, total_random;
        // try to wipe out each cell
        for(int i = 0; i < size; i++) {
            if(board[i] == 1) {
                // if a cell be wipe out, recover the board 
                bitset<MAX_SIZE> rec_board = recover(board, next_board, size, i);
                if(rec_board == board) continue;

                int ori_h = heurstic(board), h = heurstic(rec_board);
                if(ori_h >= h) {
                    if(h == MIN_h) {
                        candicate_rec_board.push_back(rec_board);
                        candicate_click.push_back(i);
                    }
                    else if(h < MIN_h) {
                        MIN_h = h;
                        candicate_rec_board.clear();
                        candicate_click.clear();
                        candicate_rec_board.push_back(rec_board);
                        candicate_click.push_back(i);
                    }
                }
                
            }
        }

        if(candicate_click.size() == 0) return false;
        int next = random() % candicate_click.size();
        board = candicate_rec_board[next];
        ans.push_back(candicate_click[next] + 1);
    }
    return false;
}

vector<int> CLI(bitset<MAX_SIZE> board, size_t size) {
    if(size == 0) return vector<int>();

    vector<int> tmp_ans, ans;
    srandom(time(0));
    for(int i = 0; i < 100000; i++) {
        tmp_ans.clear();
        if(CLI_serch(board, tmp_ans, size)) {
            if((tmp_ans.size() < ans.size()) || ans.empty()) {
                ans = tmp_ans;
            }
        }
    }
    return ans;
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
