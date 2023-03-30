#include "./ida.h"

class State {
    public:

    bitset<MAX_SIZE> board;
    vector<int> ans;
    int priority;
    int left;
    int deep;
    int size;

    State(bitset<MAX_SIZE> _board, vector<int> _ans, int _deep, int _size) {
        board = _board;
        ans = _ans;
        priority = estimate_priority();
        left = _board.count();
        deep = _deep;
        size = _size;
    }

    int estimate_priority() {
        return spilt(this->board, size).count();
    }

    bool operator> (const State &that) const{
        return this->left + this->priority > that.left + that.priority;
    }

};

vector<int> IDA_search(bitset<MAX_SIZE> board, int deep, int size) {
    priority_queue<State, vector<State>, greater<State>> pq;
    pq.push(State(board, vector<int>(), deep, size));
    while(!pq.empty()) {
        int size = pq.size();
        while(size--) {
            State top = pq.top(); pq.pop();
            bitset<MAX_SIZE> next_board = spilt(top.board, size);
            vector<int> ans = top.ans;
            for(int i = 0; i < size; i++) {
                if(top.board[i] == 1) {
                    bitset<MAX_SIZE> rm_board = recover(top.board, next_board, size, i);
                    ans.push_back(i);
                    pq.push(State(rm_board, ans, top.deep - 1, size));
                    ans.pop_back();
                }
            }
        }
    }
    return vector<int>();
}

// run the IDA algorithm
vector<int> IDA(bitset<MAX_SIZE> board, size_t size) {
    if(size == 1) return vector<int>{1};

    //iterate the deep
    vector<int> ans;
    for(int deep = board.count(); ; deep += 3) {
        cout<<"deep: "<<deep<<endl;
        IDA_search(board, deep, size);
    }
    return ans;
}
