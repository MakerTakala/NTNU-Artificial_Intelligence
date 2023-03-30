#include "./ids.h"
#include "./help.h"

// an IDS DFS
bool IDS_search(bitset<MAX_SIZE> board, vector<int> &ans, vector<int> &tmp, int deep, int size) {
    // when all cell has been wipe out, update the mininum answer
    if(board == 0) {
        if(ans.size() == 0 || ans.size() > tmp.size()) ans = tmp;
        cout<<"find: ";
        for(int x : tmp)
            cout<<x<<" ";
        cout<<endl;
        return true;
    }
    // over the limited deep
    if(deep == 0) return false;

    // suppose all cell is split
    bitset<MAX_SIZE> next_board = spilt(board, size);

    // use flag for record success or not
    bool flag = false;

    // try to wipe out each cell
    for(int i = 0; i < size; i++) {
        bitset<MAX_SIZE> rm_board(next_board);
        if(board[i] == 1) {
            // if a cell be wipe out, recover the board 
            bitset<MAX_SIZE> rec_board = recover(board, next_board, size, i);
            tmp.push_back(i + 1);
            if(IDS_search(rec_board, ans, tmp, deep - 1, size)) {
                flag = true;
            }
            tmp.pop_back();
        }
    }
    return flag;
}

// run the IDS algorithm
vector<int> IDS(bitset<MAX_SIZE> board, size_t size) {
    if(size == 1) return vector<int>{1};
    
    //iterate the deep
    vector<int> ans, tmp;
    for(int deep = board.count(); ; deep += 1) {
        cout<<"deep: "<<deep<<endl;
        if(IDS_search(board, ans, tmp, deep, size)) break;
    }
    return ans;
}