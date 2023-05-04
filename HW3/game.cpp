#include <bits/stdc++.h>
#include <unistd.h>
#include <fstream>
#include <bitset>
#include <vector>

using namespace std;

uint64_t take_mask[16] = {
    0xFFFFFFFFFFFFFF00, 
    0xFFFFFFFFFFFF00FF, 
    0xFFFFFFFFFF00FFFF, 
    0xFFFFFFFF00FFFFFF, 
    0xFFFFFF00FFFFFFFF, 
    0xFFFF00FFFFFFFFFF, 
    0xFF00FFFFFFFFFFFF, 
    0x00FFFFFFFFFFFFFF,
    0xFEFEFEFEFEFEFEFE,
    0xFDFDFDFDFDFDFDFD, 
    0xFBFBFBFBFBFBFBFB,
    0xF7F7F7F7F7F7F7F7, 
    0xEFEFEFEFEFEFEFEF, 
    0xDFDFDFDFDFDFDFDF, 
    0xBFBFBFBFBFBFBFBF,
    0x7F7F7F7F7F7F7F7F
};

int n, m;

pair<int, int> maximize(uint64_t board, int alpha, int beta, pair<int, int> get);
pair<int, int> minimize(uint64_t board, int alpha, int beta, pair<int, int> get);

void show(uint64_t board);
int take_piece_amount(uint64_t board, uint64_t mask);
uint64_t remove(uint64_t board, uint64_t mask);
fstream open_file(string file_path, const ios_base::openmode permittion);
uint64_t read_board(fstream &file);


int main() {
    fstream in = open_file("./data/1.in", ios_base::in);
    uint64_t init_board = (read_board(in));
    in.close();
    
    pair<int, int> get{0, 0};
    vector<int> selects;

    int turn = 0;
    while(init_board) {
        show(init_board);

        pair<int, int> ans = maximize(init_board, INT_MIN, INT_MAX, {0, 0});
        int utility = ans.first, step = ans.second;

        cout<<"STEP: "<<step<<endl<<"Utility: "<<utility<<endl;
        selects.push_back(step);

        uint64_t next_board = remove(init_board, take_mask[step]);
        int take = take_piece_amount(init_board, next_board);

        if(turn == 0) {
            get.first += take;
        }
        else {
            get.second += take;
        }
        turn ^= 1;

        init_board = next_board;
        
    }

    cout<<endl<<endl<<"FIN:"<<endl;
    for(int x : selects) {
        cout<<x<<" ";
    }
    cout<<endl;
    cout<<"GET: "<<get.first<<" "<<get.second<<endl;

    

    return 0;
}

pair<int, int> maximize(uint64_t board, int alpha, int beta, pair<int, int> get) {
    //usleep(500 * 1000);
    if(board == 0) return {get.first - get.second, -1};

    int max_utility = INT_MIN, max_select = -1;
    for(int i = 0; i < 16; i++) {
        uint64_t next_board = remove(board, take_mask[i]);
        int take = take_piece_amount(board, next_board);
        if(take == 0) continue;

        pair<int, int> next = minimize(next_board, alpha, beta, {get.first + take, get.second});
        int next_utility = next.first;

        if(next_utility > max_utility) {
            max_utility = next_utility;
            max_select = i;
        }
        
        if(max_utility >= beta) break;

        alpha = max(alpha, max_utility);
    }
    return {max_utility, max_select};
}

pair<int, int> minimize(uint64_t board, int alpha, int beta, pair<int, int> get) {
    //usleep(500 * 1000);
    if(board == 0) return {get.first - get.second, -1};

    int min_utility = INT_MAX, min_select = -1;
    for(int i = 0; i < 16; i++) {
        uint64_t next_board = remove(board, take_mask[i]);
        int take = take_piece_amount(board, next_board);
        if(take == 0) continue;
        

        pair<int, int> next = maximize(next_board, alpha, beta, {get.first, get.second + take});
        int next_utility = next.first;

        if(next_utility < min_utility) {
            min_utility = next_utility;
            min_select = i;
        }

        if(min_utility <= alpha) break;

        beta = min(beta, min_utility);
    }
    return {min_utility, min_select};
}


void show(uint64_t board) {
    for(int i = 0; i < n; i++) {
        for(int j = 0; j < m; j++) {
            cout<<(board & 1)<<" ";
            board = (board>>1);
        }
        for(int j = 0; j < 8 - m; j++) {
            board = (board>>1);
        }
        cout<<endl;
    }
    cout<<endl;
}

uint64_t remove(uint64_t board, uint64_t mask){
    return board & mask;
}

int take_piece_amount(uint64_t board, uint64_t mask) {
    int count = 0;
    int n = board ^ mask;
    while (n)
    {
        n = n & (n - 1);
        count++;
    }
    return count;
}

fstream open_file(string file_path, const ios_base::openmode permittion) {
    fstream file;
    file.open(file_path, permittion);
    return file;
}

uint64_t read_board(fstream &file) {
    file>>n>>m;
    string input;
    for(int i = 0; i < n; i++) {
        for(int j = 0, x; j < m; j++) {
            file>>x;
            input = to_string(x) + input;
        }
        for(int j = 0, x; j < 8 - m; j++) {
            input = "0" + input;
        }
    }
    return bitset<64>(input).to_ullong();
}

