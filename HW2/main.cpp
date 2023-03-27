#include <fstream>
#include <iostream>
#include <sys/time.h>
#include <sys/resource.h>
#include "algo.h"

using namespace std;

fstream open_file(string file_path, ios_base::openmode permittion);

int main(int argc, char *argv[]) {

    for(int i = 1; ; i++) {
        fstream in = open_file("./in/" + to_string(i) + ".in", ios::in);
        if(in.fail()) {
            break;
        }

        string str;
        int in_space;
        while(in>>in_space) {
            str += to_string(in_space);
        }
        bitset<1000> board(str); 
        in.close();


        fstream out = open_file("./out/" + to_string(i) + ".out", ios::out);
        if(string(argv[0]) == "IDS") {
            IDS(board, str.length(), out);
        }
        else if(string(argv[0]) == "IDA") {
            IDA(board, str.length(), out);
        }
        else {
            cout<<"doesn't support algorithm!"<<endl;
            break;
        }
        out.close();
    }  
    
    rusage usage;
    getrusage(RUSAGE_SELF, &usage);
    cout<<endl;
    cout<<"Usage time: "<<usage.ru_utime.tv_usec<<" ms"<<endl;
    cout<<"Usage memory: "<<usage.ru_maxrss<<" byte"<<endl;
    return 0;
}

fstream open_file(string file_path, ios_base::openmode permittion) {
    fstream file;
    file.open(file_path, permittion);
    return file;
}