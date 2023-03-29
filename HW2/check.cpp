#include <fstream>
#include <iostream>
#include <bitset>
#include "./lib/help.h"

using namespace std;

int main() {

    for(int i = 1; ; i++) {
        // load input data
        fstream in = open_file("./in/" + to_string(i) + ".in", ios::in);
        if(in.fail()) break;

        // read input
        int size = 0;
        bitset<MAX_SIZE> board = read_in_file(in, size);
        in.close();

        fstream out = open_file("./out/" + to_string(i) + ".out", ios::in);
        if(out.fail()) break;
        vector<int> ans = read_out_file(out);
        out.close();
       
        cout<<"Case "<<i<<": "<<board<<endl;
        for(int step : ans) {
            board[step - 1] = 0;
            board = spilt(board, size);
            cout<<"\t"<<step<<" : "<<board<<endl;
        }

        if(board == 0) cout<<"AC!"<<endl;
        else cout<<"WA!"<<endl;
    }  

    return 0;
}
