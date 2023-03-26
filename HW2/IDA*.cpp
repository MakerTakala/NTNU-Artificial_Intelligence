#include <fstream>
#include <vector>
#include <iostream>

using namespace std;

int main() {
    fstream in, out;
    in.open("./in/1.in", ios::in);
    out.open("./out/1.out", ios::out);
    if(in.fail()) cout<<"in file can't open."<<endl;
    if(out.fail()) cout<<"out file can't open."<<endl;
    
    vector<int> board;
    int in_space;
    while(in>>in_space) {
        board.push_back(in_space);
    }
    

    in.close();
    out.close();
    return 0;
}
