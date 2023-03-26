#include <fstream>
#include <vector>
#include <iostream>

using namespace std;

int main() {
    fstream in;
    in.open("./in/1.in", ios::in);
    if(in.fail()) cout<<"file can't open."<<endl;
    
    vector<int> board;
    int in_space;
    while(in>>in_space) {
        board.push_back(in_space);
    }
    

    in.close();
    return 0;
}
