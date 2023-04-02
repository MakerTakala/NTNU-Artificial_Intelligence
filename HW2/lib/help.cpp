#include "./help.h"

int heurstic(bitset<MAX_SIZE> board) {
    return board.count();
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

bool cross_01_judge(bitset<MAX_SIZE> board, vector<int> &ans, int size, int deep, bool is_IDA) {
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

    if(is_IDA && tmp_ans.size() + heurstic(board) > deep + 1) return false;
    if(!is_IDA && tmp_ans.size() > deep + 1) return false;
    for(int x : tmp_ans)
        ans.push_back(x);

    return true;
}

