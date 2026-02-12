#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <cmath>
#include <string>
using namespace std;


typedef struct inputs{
    int lable;
    vector<float> val;
}Inputs;

vector<Inputs> data;


vector<Inputs> input(string name ){
    ifstream file(name);
    if(!file.is_open()){
        cerr << "Failed to open file\n";
    }
    vector<Inputs> data;
    string line;
    while (getline(file,line)){
        stringstream row(line);
        string value;
        Inputs sample;
        int f=1;
        while (getline(row, value, ',')) {
            if(f==1){
                sample.lable=stoi(value);
                f=0;
                continue;
            }
            sample.val.push_back(stoi(value)/255.0f);
        }
        data.push_back(sample);
    }
    return data;
}
