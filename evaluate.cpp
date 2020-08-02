#include <iostream>
#include <fstream>
#include <vector>

using namespace std;

using uvec = vector<unsigned>;

void load(const char* filepath, unsigned& max_slices, unsigned& n_types, uvec& n_pizzas){
    ifstream file(filepath);
    if(!file){
        cerr<<"Error loading the file!\n";
        abort();
    }
    file>>max_slices>>n_types;
    n_pizzas.resize(n_types);
    for(unsigned i=0;i<n_types;++i){
        file>>n_pizzas[i];
    }
    file.close();
}

void load2(const char* filepath, unsigned& n_types, uvec& order){
    ifstream file(filepath);
    if(!file){
        cerr<<"Error loading the file!\n";
        abort();
    }
    file>>n_types;
    order.resize(n_types);
    for(unsigned i=0;i<n_types;++i){
        file>>order[i];
    }
    file.close();
}

int main(int argc, char** argv){
    
    unsigned max_score, n_types;
    uvec n_pizzas;

    load(argv[1], max_score, n_types, n_pizzas);

    unsigned n_types2;
    uvec order;
    load2(argv[2], n_types2, order);

    unsigned score = 0;
    for(unsigned i=0;i<n_types2;++i){
        score += n_pizzas[order[i]];
    }
    cout<<"Score: "<<score<<'\n';

    return 0;
}