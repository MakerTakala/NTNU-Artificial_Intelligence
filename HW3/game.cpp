#include <bits/stdc++.h>
#include <unistd.h>
#include <fstream>
#include <bitset>
#include <vector>
#include <sys/time.h>
#include <sys/resource.h>

/* 
You can use makefile to compile the program by 'make'.
In user interface, if you only want to cheak homework, you can use mode(3) One step.
Othereise, you can play PVP and PVE mode
*/
// You can revise the file path if you want
#define INPUT_PATH "./input.txt"
#define OUTPUT_PATH "./output.txt"


using namespace std;

// use to remove the piece
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

int start();
void PVP(uint64_t board);
void PVE(uint64_t board);
int ONE(uint64_t board);
void show(uint64_t board);
int take_piece_amount(uint64_t board, uint64_t mask);
uint64_t remove(uint64_t board, uint64_t mask);
fstream open_file(string file_path, const ios_base::openmode permittion);
uint64_t read_board(fstream &file);


int main() {
    system("clear");
    // set the game mode
    int mode = start();

    fstream in = open_file(INPUT_PATH, ios_base::in);
    uint64_t init_board = (read_board(in));
    in.close();

    if(mode == 1) {
        PVP(init_board);
    }
    if(mode == 2) {
        PVE(init_board);
    }
    if(mode == 3) {
        ONE(init_board);
    }

    return 0;
}

// maximize node
pair<int, int> maximize(uint64_t board, int alpha, int beta, pair<int, int> get) {
    // detect all chese are remove
    if(board == 0) return {get.first - get.second, -1};

    // recode the high utility and correspond select
    int max_utility = INT_MIN, max_select = -1;

    // try all step
    for(int i = 0; i < 16; i++) {
        //remove corresponded row or col  
        uint64_t next_board = remove(board, take_mask[i]);
        // counting how much piece are removed
        int take = take_piece_amount(board, next_board);

        if(take == 0) continue;

        // recursion to minimize node
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

// minimize node
pair<int, int> minimize(uint64_t board, int alpha, int beta, pair<int, int> get) {
    // detect all chese are remove
    if(board == 0) return {get.first - get.second, -1};

    // recode the lowest utility and correspond select
    int min_utility = INT_MAX, min_select = -1;

    // try all step
    for(int i = 0; i < 16; i++) {
        //remove corresponded row or col  
        uint64_t next_board = remove(board, take_mask[i]);
        // counting how much piece are removed
        int take = take_piece_amount(board, next_board);

        if(take == 0) continue;
        
        // recursion to maximize node
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


// mode selection
int start() {
    int select;
    cout<<"(1) PVP"<<endl;
    cout<<"(2) PVE"<<endl;
    cout<<"(3) One step(HW reqeust)"<<endl;
    cout<<"(0) Exit"<<endl;
    cout<<"Please select play mode(1-3): ";
   

    cin>>select;
    if(select == 1 || select == 2 || select == 3) {
        return select;
    }
    if(select != 0) cout<<"Wrong Input!"<<endl;
    exit(0);
}

// PVP mode
void PVP(uint64_t board) {
    system("clear");

    // recode player round
    int turn = 0;

    // recode getting chese
    pair<int, int> get{0, 0};

    while(board) {
        cout<<endl<<"========================="<<endl;
        cout<<"Player"<<turn + 1<<" round!"<<endl;
        cout<<"Points: "<<"Player1: "<<get.first<<"     "<<"Player2: "<<get.second<<endl<<endl;
        ONE(board);
        cout<<"--------------------------"<<endl;
        cout<<"Please input your choose: ";
        int select = 0;
        cin>>select;
        if(select <= 0 || n + m < select) {
            cout<<"Wrong Input!"<<endl;
            exit(0);
        }
        if(select > n) select += (8 - n);
        select--;
        uint64_t next_board = remove(board, take_mask[select]);
        int take = take_piece_amount(board, next_board);
        system("clear");
        cout<<"Player"<<turn + 1<<" get "<<take<<" piece!"<<endl;
        if(turn == 0) {
            get.first += take;
        }
        else {
            get.second += take;
        }
        board = next_board;
        turn ^= 1;
    }

    cout<<endl<<"========================="<<endl;
    cout<<"Points: "<<"Player1: "<<get.first<<"     "<<"Player2: "<<get.second<<endl<<endl;
    if(get.first > get.second) {
        cout<<"Player1 WIN!"<<endl;
    }
    else if(get.first < get.second) {
        cout<<"Player2 WIN!"<<endl;
    }
    else {
        cout<<"TIE!"<<endl;
    }
}

//PVE mode
void PVE(uint64_t board) {
    //system("clear");

    // recode player round
    int turn = 0;

    // recode getting chese
    pair<int, int> get{0, 0};

    while(board) {
        cout<<endl<<"========================="<<endl;
        if(turn == 1) {
            cout<<"Computer round!"<<endl;
        }
        else {
            cout<<"Player round!"<<endl;
        }
        cout<<"Points: "<<"Player: "<<get.first<<"     "<<"Computer: "<<get.second<<endl<<endl;
        int ans = ONE(board);
        cout<<"--------------------------"<<endl;
        cout<<"Please input your choose: ";
        int select = 0;
        if(turn == 1) {
            select = ans;
            usleep(1000 * 1000);
        }
        else {
            cin>>select;
        }
        
        if(turn == 0) {
             if(select <= 0 || n + m < select) {
                cout<<"Wrong Input!"<<endl;
                exit(0);
            }
            if(select > n) select += (8 - n);
            select--;
        }
        
        uint64_t next_board = remove(board, take_mask[select]);
        int take = take_piece_amount(board, next_board);
        system("clear");
        if(turn == 1) {
            cout<<"Computer get "<<take<<" piece!"<<endl;
        }
        else {
            cout<<"Player get "<<take<<" piece!"<<endl;
        }
        
        if(turn == 0) {
            get.first += take;
        }
        else {
            get.second += take;
        }
        board = next_board;
        turn ^= 1;
    }

    cout<<endl<<"========================="<<endl;
    cout<<"Points: "<<"Player: "<<get.first<<"     "<<"Computer: "<<get.second<<endl<<endl;
    if(get.first > get.second) {
        cout<<"Player WIN!"<<endl;
    }
    else if(get.first < get.second) {
        cout<<"Computer WIN!"<<endl;
    }
    else {
        cout<<"TIE!"<<endl;
    }
}

// only apply one step
int ONE(uint64_t board) {
    // recode start time
    rusage start, end;;
    getrusage(RUSAGE_SELF, &start);
    
    // get the answer
    pair<int, int> ans = maximize(board, INT_MIN, INT_MAX, {0, 0});

    getrusage(RUSAGE_SELF, &end);


    // deal with output file
    fstream out = open_file(OUTPUT_PATH, ios_base::out);

    show(board);
    cout<<"Recommand Step:"<<endl;

    if(ans.second < 8) {
        out<<"Row#: "<<ans.second + 1<<endl;
        cout<<"Row#: "<<ans.second + 1<<"("<<ans.second + 1<<")"<<endl;
    }
    else {
        out<<"Column#: "<<ans.second - 7<<endl;
        cout<<"Column#: "<<ans.second - 7<<"("<<ans.second - 7 + n<<")"<<endl;
    }
    out<<ans.first<<" points"<<endl;
    cout<<ans.first<<" points"<<endl;


    // counting usage time
    unsigned long long int ns = 1000000;
    unsigned long long int usage1 = (end.ru_utime.tv_sec - start.ru_utime.tv_sec) * ns + (end.ru_utime.tv_usec - start.ru_utime.tv_usec);
    unsigned long long int usage2 = (end.ru_stime.tv_sec - start.ru_stime.tv_sec) * ns + (end.ru_stime.tv_usec - start.ru_stime.tv_usec);
    unsigned long long int usage = usage1 + usage2;

    out<<"Total run time = "<<usage / ns<<"."<<setiosflags(ios::right)<<setw(6)<<setfill('0')<<usage % ns<<" seconds"<<endl;
    cout<<"Total run time = "<<usage / ns<<"."<<setiosflags(ios::right)<<setw(6)<<setfill('0')<<usage % ns<<" seconds"<<endl<<endl;
    out.close();
    return ans.second;
}

// show the board
void show(uint64_t board) {
    cout<<"  ";
    for(int i = n + 1; i <= n + m; i++) {
        cout<<setfill(' ')<<setiosflags(ios::left)<<setw(3)<<i;
    }
    cout<<endl<<" .";
    for(int i = n + 1; i <= n + m; i++) {
        cout<<"---";
    }
    cout<<endl;
    for(int i = 0; i < n; i++) {
        cout<<setiosflags(ios::left)<<setw(1)<<i + 1<<"|";
        for(int j = 0; j < m; j++) {
            cout<<(board & 1)<<"  ";
            board = (board>>1);
        }
        for(int j = 0; j < 8 - m; j++) {
            board = (board>>1);
        }
        cout<<endl;
    }
    cout<<endl;
}

// remove the chese by mask
uint64_t remove(uint64_t board, uint64_t mask){
    return board & mask;
}

// use bit counting the count the number of moved chese
int take_piece_amount(uint64_t board, uint64_t next_board) {
    int count = 0;
    uint64_t n = board ^ next_board;
    while (n) {
        n = (n & (n - 1));
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

