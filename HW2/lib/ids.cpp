#include "./ids.h"
#include "./help.h"

// an IDS DFS
bool IDS_search(bitset<MAX_SIZE> board, vector<int> &ans, int deep, int size) {
    // when all cell has been wipe out, find answer
    if(board == 0 || cross_01_judge(board, ans, size, deep)) return true;
    
    // over the limited deep
    if(deep == 0) return false;

    // suppose all cell is split
    bitset<MAX_SIZE> next_board = spilt(board, size);

    // try to wipe out each cell
    for(int i = 0; i < size; i++) {
        bitset<MAX_SIZE> rm_board(next_board);
        if(board[i] == 1) {
            // if a cell be wipe out, recover the board 
            bitset<MAX_SIZE> rec_board = recover(board, next_board, size, i);
            ans.push_back(i + 1);
            if(IDS_search(rec_board, ans, deep - 1, size)) return true;
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
        if(IDS_search(board, ans, deep, size)) return ans;
    }
    return vector<int>();
}