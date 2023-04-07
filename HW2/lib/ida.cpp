#include "./ida.h"
#include "./help.h"

int heurstic(bitset<MAX_SIZE> board, int size, vector<int> ans) {
    int sum = 0, alive = board.count(), ans_size = ans.size();
    if(alive <= 1) return alive;
    for(int i = 1; i < size - 1; i++) {
        sum += (board[i] == 1) * 2;
    }
    return sum;
}

int IDA_search(bitset<MAX_SIZE> board, vector<int> &ans, unordered_map<unsigned long long int, int> &same, int deep, int size) {
    // when all cell has been wipe out, find answer
    if(board == 0) return 0;
    
    int h = heurstic(board, size, ans) + ans.size();
    // over the limited deep
    if(h > deep) return h;

    unsigned long long int state = board.to_ullong();
    if(!same.count(state)) same[state] = INT_MAX;
    if(same[state] < h) return INT_MAX;
    same[state] = h;

    // suppose all cell is split
    bitset<MAX_SIZE> next_board = spilt(board, size);
    
    // use deep_update to record the maxinum change
    int deep_update = INT_MAX;

    // try to wipe out each cell
    for(int i = 0; i < size; i++) {
        bitset<MAX_SIZE> rm_board(next_board);
        if(board[i] == 1) {
            // if a cell be wipe out, recover the board 
            bitset<MAX_SIZE> rec_board = recover(board, next_board, size, i);
            ans.push_back(i + 1);

            int deep_diff = IDA_search(rec_board, ans, same, deep, size);
            if(deep_diff == 0) return 0;
            deep_update = min(deep_update, deep_diff);

            ans.pop_back();
        }
    }
    return deep_update;
}

// run the IDA algorithm
vector<int> IDA(bitset<MAX_SIZE> board, size_t size) {
    if(size == 0) return vector<int>();

    //iterate the deep
    vector<int> ans;
    for(int deep = heurstic(board, size, ans); ;) {
        unordered_map<unsigned long long int, int> same;
        int deep_update = IDA_search(board, ans, same, deep, size);
        if(deep_update == 0) {
            return ans;
        }
        deep = deep_update;
    }
    return vector<int>();
}
