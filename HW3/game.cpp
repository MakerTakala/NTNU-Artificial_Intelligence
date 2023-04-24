#include <bits/stdc++.h>
#include <fstream>
#include <bitset>

using namespace std;

void show_board(uint64_t board, const int n, const int m) {
    for(int i = 0; i < n * m; i++) {
        cout<<(board & 1)<<" ";
        board = (board>>1);
        if(i % n == n - 1) cout<<endl;
    }
}
fstream open_file(string file_path, const ios_base::openmode permittion);
uint64_t read_board(fstream &file, int &n, int &m);

int main() {
    int n, m;
    fstream in = open_file("./data/1.in", ios_base::in);
    uint64_t board = read_board(in, n, m);
    show_board(board, n, m);

    return 0;
}

fstream open_file(string file_path, const ios_base::openmode permittion) {
    fstream file;
    file.open(file_path, permittion);
    return file;
}

uint64_t read_board(fstream &file, int &n, int &m) {
    file>>n>>m;
    string input;
    for(int i = 0; i < n; i++) {
        for(int j = 0, x; j < m; j++) {
            file>>x;
            input = to_string(x) + input;
        }
        for(int j = 0, x; j < 8 - m; j++) {
            file>>x;
            input = "0" + input;
        }
    }
    return bitset<64>(input).to_ullong();
}

