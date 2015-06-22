#include <iostream>
#include <ctime>
#include <string>
#include <stdlib.h>
#include <vector>
#include <fstream>
#include <sstream>
#include <sys/stat.h>

using namespace std;

#include "arrival_curve.h"
#include "arrival_curve.c"

int main(int argc, char *argv[]){
        if ( argc != 5 || atoll(argv[1]) <= 0 || atoll(argv[2]) <= atoll(argv[1]) ){
                cout << "usage: [minimum interval ( >= 1 ns )] [maximum interval] [input] [output]\n";
                return 0;
        }
    clock_t start = clock();
        ifstream infile(argv[3]);
        string tmp, line;
        if(!infile.good()){
                infile.close();
                cout << "input file does not exist!\n";
                return 0;
        }
        //this is the code of setting up vector events.
        vector<float> e;
        vector<step> max_vec, min_vec;
        while (std::getline(infile, line)) {
                istringstream iss(line);
                if (!(iss >> tmp)) break; // error
                e.push_back(stof(tmp));
        }
        infile.close();
        stream.open(argv[4]);
        max_event = e[e.size() - 1]; //this is part of error checking before calling computer_arrival_curve
        if(atoll(argv[2]) > max_event){
                cout << "[maximum interval] is larger than the max event time. Exiting...\n";
                return 0;
        }
        computer_arrival_curve(e, stof(argv[1]), stof(argv[2]), max_vec, min_vec);

        long double duration = (long double) (std::clock() - start) / CLOCKS_PER_SEC;
        stream << "Duration: " << duration << endl;
        stream << "total number of getcount(): " << totalcount << endl;
        stream << "time spent per getcount(): " << duration / totalcount << endl;
        stream.close();
        return 0;

}
