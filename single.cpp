#include <vector>
#include <iostream>
#include <cmath>
using namespace std;

struct preceptron {

    vector<int> inputs;
    vector<int> weights;
    double output;
    preceptron(){
        inputs.resize(3);
        weights.resize(3);
        
        output=0;
    }
};


int main(){
    preceptron p;
    cout<<"enter weights: ";
    for(int i=0;i<3;i++)
        cin>>p.weights[i];
    cout<<"enter inputs: ";
    for(int i=0;i<3;i++)
        cin>>p.inputs[i];
    for(int i=0;i<3;i++)
        p.output+=p.inputs[i]*p.weights[i];
    p.output= 1/(1+exp(-p.output));
    cout<<"output: "<<p.output;
    
}