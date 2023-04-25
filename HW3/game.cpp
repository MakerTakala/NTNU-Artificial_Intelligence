#include <bits/stdc++.h>
#include <fstream>
#include <bitset>

using namespace std;

int n, m;
void show_board(uint64_t board);
fstream open_file(string file_path, const ios_base::openmode permittion);
uint64_t read_board(fstream &file);

int main() {
    fstream in = open_file("./data/1.in", ios_base::in);
    uint64_t board = read_board(in);
    show_board(board);

    return 0;
}

void show_board(uint64_t board) {
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

