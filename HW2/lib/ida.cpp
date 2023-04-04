#include "./ida.h"
#include "./help.h"

long long int count_heurstic = 0;

double guss(int x) {
    return (1.0 / 5.0 * (sqrt((2.0 * M_PI)))) * exp(-((x * x) / 2.0));
}

int heurstic(bitset<MAX_SIZE> board, int size) {
    count_heurstic++;
    int sum = 0;
    int lim1 = size / 3, lim2 = 2 * size / 3;
    for(int i = 0; i < size; i++) {
        if(board[i] == 1 && lim1 <= i && i <= lim2) {
            sum++;
        }
    }
    return sum + board.count();
}

int IDA_search(bitset<MAX_SIZE> board, vector<int> &ans, unordered_map<unsigned long long int, int> &same, int deep, int size) {
    // when all cell has been wipe out, find answer
    if(board == 0) return 0;

    // over the limited deep
    if(deep < 0) return deep;

    if(!same.count(board.to_ullong())) same[board.to_ullong()] = INT_MIN;
    if(same[board.to_ullong()] >= deep) return INT_MIN;
    same[board.to_ullong()] = deep;

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

            int deep_diff = IDA_search(rec_board, ans, same, deep - heurstic(rec_board, size), size);
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
    for(int deep = heurstic(board, size); ;) {
        unordered_map<unsigned long long int, int> same;
        //cout<<deep<<" ";
        int deep_update = IDA_search(board, ans, same, deep, size);
        if(deep_update == 0) {
            cout<<"times: "<<count_heurstic<<endl;
            return ans;
        }
        deep -= deep_update;
    }
    return vector<int>();
}
