#include <fstream>
#include <iostream>
#include <bitset>
#include <sys/time.h>
#include <sys/resource.h>
#include "./lib/help.h"
#include "./lib/ids.h"
#include "./lib/ida.h"
#include "./lib/cli.h"

using namespace std;

int main(int argc, char *argv[]) {
    for(int i = 1; ; i++) {
        // racord the start time and memory
        rusage start;
        getrusage(RUSAGE_SELF, &start);

        // load input data
        fstream in = open_file("./data/in/" + to_string(i) + ".in", ios::in);
        if(in.fail()) break;
        if(argc == 0) {
            cout<<"Please input an algorithm!"<<endl;
            break;
        }

        // read input
        int size = 0;
        bitset<MAX_SIZE> board = read_in_file(in, size);
        in.close();

        cout<<"CASE: "<<i<<" ===== [ ";
        for(int i = 0; i < size; i++) cout<<board[i]<<" ";
        cout<<"]"<<endl;

        // choose algorithm by argv
        vector<int> ans;

        if(string(argv[1]) == "IDS") {
            ans = IDS(board, size);
        }
        else if(string(argv[1]) == "IDA") {
            ans = IDA(board, size);
        }
        else if(string(argv[1]) == "CLI"){
            ans = CLI(board, size);
        }
        else{
            cout<<"doesn't support this algorithm!"<<endl;
            break;
        }

        
        // write the answer to out file
        fstream out = open_file("./data/out/" + to_string(i) + ".out", ios::out);
        cout<<"Step: "<<ans.size()<<endl;
        cout<<"Ans: ";
        for(int x : ans) {
            out<<x<<" ";
            cout<<x<<" ";
        }
        cout<<endl;
        out.close();

        // record end time and memory
        rusage end;
        getrusage(RUSAGE_SELF, &end);

        unsigned long long int ns = 1000000;
    unsigned long long int usage1 = (end.ru_utime.tv_sec - start.ru_utime.tv_sec) * ns + (end.ru_utime.tv_usec - start.ru_utime.tv_usec);
    unsigned long long int usage2 = (end.ru_stime.tv_sec - start.ru_stime.tv_sec) * ns + (end.ru_stime.tv_usec - start.ru_stime.tv_usec);
    unsigned long long int usage = usage1 + usage2;

    cout<<"Total run time = "<<usage / ns<<"."<<setiosflags(ios::right)<<setw(6)<<setfill('0')<<usage % ns<<" seconds"<<endl<<endl;
    }  
    
    return 0;
}

