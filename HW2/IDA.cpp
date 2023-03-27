#include <fstream>
#include <vector>
#include <iostream>
#include <sys/time.h>
#include <sys/resource.h>

using namespace std;

fstream open_file(string file_path, ios_base::openmode permittion);

int main() {
    fstream in = open_file("./in/1.in", ios::in);
    fstream out = open_file("./out/1.out", ios::out);
    
    vector<int> board;
    int in_space;
    while(in>>in_space) {
        board.push_back(in_space);
    }

    in.close();
    out.close();
    
    rusage usage;
    getrusage(RUSAGE_SELF, &usage);
    cout<<"Usage time: "<<usage.ru_utime.tv_usec<<" ms"<<endl;
    cout<<"Usage memory: "<<usage.ru_maxrss<<" byte"<<endl;
    return 0;
}

fstream open_file(string file_path, ios_base::openmode permittion) {
    fstream file;
    file.open(file_path, permittion);
    if(file.fail()) cout<<file_path<<" can't open";
    return file;
}