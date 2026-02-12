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

typedef struct node{
    vector<float> weight;
    float bias;
} node;

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


void save_model_binary(const vector<vector<node>>& hidden_layer, const string& filename) {
    ofstream out(filename, ios::binary);

    size_t num_layers = hidden_layer.size();
    out.write((char*)&num_layers, sizeof(num_layers));

    for (const auto& layer : hidden_layer) {
        size_t num_neurons = layer.size();
        out.write((char*)&num_neurons, sizeof(num_neurons));

        for (const auto& neuron : layer) {
            size_t num_weights = neuron.weight.size();
            out.write((char*)&num_weights, sizeof(num_weights));

            out.write((char*)neuron.weight.data(), num_weights * sizeof(float));
            out.write((char*)&neuron.bias, sizeof(float));
        }
    }

    out.close();
}



void load_model_binary(vector<vector<node>>& hidden_layer, const string& filename) {
    ifstream in(filename, ios::binary);

    if (!in.is_open()) {
        cout << "Error opening file\n";
        return;
    }

    size_t num_layers;
    in.read((char*)&num_layers, sizeof(num_layers));

    hidden_layer.clear();
    hidden_layer.resize(num_layers);

    for (size_t i = 0; i < num_layers; i++) {

        size_t num_neurons;
        in.read((char*)&num_neurons, sizeof(num_neurons));

        hidden_layer[i].resize(num_neurons);

        for (size_t j = 0; j < num_neurons; j++) {

            size_t num_weights;
            in.read((char*)&num_weights, sizeof(num_weights));

            hidden_layer[i][j].weight.resize(num_weights);

            // Read all weights at once
            in.read(
                (char*)hidden_layer[i][j].weight.data(),
                num_weights * sizeof(float)
            );

            // Read bias
            in.read(
                (char*)&hidden_layer[i][j].bias,
                sizeof(float)
            );
        }
    }

    in.close();
}
