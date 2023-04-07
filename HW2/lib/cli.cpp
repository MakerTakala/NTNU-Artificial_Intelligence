#include "./cli.h"
#include "./help.h"

int heurstic(bitset<MAX_SIZE> board) {
    return board.count();
}

bool CLI_serch(bitset<MAX_SIZE> board, vector<int> &ans, size_t size) {
    while(1) {
        // cout<<board<<endl;
        // for(int x : ans) {
        //     cout<<x<<" ";
        // }
        // cout<<endl;
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

vector<int> CLI(bitset<MAX_SIZE> board, size_t size){
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