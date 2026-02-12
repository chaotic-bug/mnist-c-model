#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <cmath>
#include <string>
using namespace std;


vector<vector<float>> outputs;
int hidden_config[]={30,30,10};

typedef struct node{
    vector<float> weight;
    float bias;
} node;

typedef struct inputs{
    int lable;
    vector<float> val;
}Inputs;
vector<Inputs> train_data;
vector<vector<node>> hidden_layer;


//INput fuction 

vector<Inputs> input(){
    ifstream file("mnist_test.csv");
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
            sample.val.push_back(stoi(value));
        }
        data.push_back(sample);
    }
    return data;
}


float matmulti(vector<float> wei,float bi,vector<float> in){
    float out;
    for(int i=0;i<in.size();i++){
        out=wei[i]*in[i];
    }
    out+=bi;
    return 1/(1+exp(-out));;
}


void train(){
    cout<<"Loading data...\n";
    train_data=input();
    for(Inputs dick:train_data){
        for(int i=0;i<sizeof(hidden_config);i++){
            for(int j=0;j<hidden_config[i];j++){
                if(i==0)
                    outputs[i][j]=matmulti(hidden_layer[i][j].weight,hidden_layer[i][j].bias,dick.val);
                else
                    outputs[i][j]=matmulti(hidden_layer[i][j].weight,hidden_layer[i][j].bias,outputs[i]);
            }
        }
    }


}



// void network(int no_input, int hidden_layer_width, int hidden_layer_length, int no_output){
//     outputs.resize(no_output);
//     // hidden_layer.resize(hidden_layer_width,hidden_layer_length);
// }

int main(){
    vector<Inputs> hell=input();
    for(float i :hell[1].val)
    cout<<i<<"|";
    return 0;
}