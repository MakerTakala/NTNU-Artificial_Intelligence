#include <fstream>
#include <iostream>
#include <bitset>
#include <sys/time.h>
#include <sys/resource.h>
#include "./lib/help.h"
#include "./lib/ids.h"
#include "./lib/ida.h"

using namespace std;

int main(int argc, char *argv[]) {
    for(int i = 1; ; i++) {
        // load input data
        fstream in = open_file("./data/in/" + to_string(i) + ".in", ios::in);
        if(in.fail()) break;
        cout<<"======CASE: "<<i<<"======"<<endl;

        // read input
        int size = 0;
        bitset<MAX_SIZE> board = read_in_file(in, size);
        in.close();

        // choose algorithm by argv
        vector<int> ans;
        if(argc == 0) {
            cout<<"Please input an algorithm!"<<endl;
            break;
        }
        else if(string(argv[1]) == "IDS") {
            ans = IDS(board, size);
        }
        else if(string(argv[1]) == "IDA") {
            ans = IDA(board, size);
        }
        else {
            cout<<"doesn't support this algorithm!"<<endl;
            break;
        }
        
        // write the answer to out file
        fstream out = open_file("./data/out/" + to_string(i) + ".out", ios::out);
        for(int x : ans) {
            out<<x<<" ";
        }
        out.close();
    }  
    
    // count time and memory usage
    rusage usage;
    getrusage(RUSAGE_SELF, &usage);
    cout<<endl;
    cout<<"Usage time: "<<usage.ru_utime.tv_sec<<"s."<<usage.ru_stime.tv_usec<<endl;
    cout<<"Usage memory: "<<usage.ru_maxrss<<" byte"<<endl;
    return 0;
}

