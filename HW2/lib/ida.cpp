#include "./ida.h"

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
