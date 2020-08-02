#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <unistd.h>
#include <chrono>

using namespace std;

using uvec = vector<unsigned>;
using bvec = vector<bool>;

decltype(std::chrono::high_resolution_clock::now()) saved_time;

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

void save(const char* filepath, const uvec& order){
    ofstream file(filepath);
    if(!file){
        cerr<<"Error loading the file!\n";
        abort();
    }
    file<<order.size()<<'\n';
    for(const auto& ord: order){
        file<<ord<<' ';
    }
    file.close();
}

bool add_one(bvec& num);
bool push_one(bvec& num, int i=-1);
int pop_one(bvec& num);
int find_last_one(const bvec& num, unsigned level=0);
unsigned tell_score(const uvec& n_pizzas, const bvec& num);

int last_index = -1;

struct Input{
    unsigned max_slices, n_types;
    uvec n_pizzas;
};

struct Output{
    unsigned score;
    uvec order;
};

void algo2(const Input& input, Output& output);

int main(int argc, char** argv){

    auto time_beg = std::chrono::high_resolution_clock::now();

    // Input variables
    unsigned max_slices, n_types;
    uvec n_pizzas;

    load(argv[1], max_slices, n_types, n_pizzas);
    // unsigned DESIRED_SCORE = (unsigned)strtol(argv[2], nullptr, 10);

    // Processing
    Input input = { max_slices, n_types, n_pizzas };
    Output output;

    // algo1(input, output);
    algo2(input, output);

    // Output
    cout<<"OMS: "<<output.score<<'\n';

    if(argc > 2)
        save(argv[2], output.order);
    // ---------------------------------
    auto duration = std::chrono::duration_cast<std::chrono::microseconds>(std::chrono::high_resolution_clock::now()-time_beg);
    double dt = 1e-6 * static_cast<double>(duration.count());
    cout<<"=== Program duration: "<<dt<<'\n';


    return 0;
}

bool push_one(bvec& num, int i){
    if(i==-1){
        // i = find_last_one(num);
        i = last_index;
        if(++i == num.size()) return false;
    }

    num[i] = true;
    last_index = i;

    return true;
}

int pop_one(bvec& num){
    // int i = find_last_one(num);
    int i = last_index;

    if(i == -1) return -1;

    num[i] = false;
    last_index = find_last_one(num);

    return i;
}

int find_last_one(const bvec& num, unsigned level){
    int i = -1;
    bool found = false;
    for(auto j=num.size();j>0;--j){
        if(num[j-1]){
            i=j-1;
            if(!level){
                found = true;
                break;
            }
            --level;
        }
    }
    if(!found) i = -1;
    return i;
}

unsigned tell_score(const uvec& n_pizzas, const bvec& num){
    unsigned total = 0;

    for(unsigned i=0;i<num.size();++i){
        if(num[i]) total += n_pizzas[i];
    }

    return total;
}

// ================ Algo ===============

void algo2(const Input& input, Output& output){
    bvec num(input.n_types);
    for(unsigned i=0;i<input.n_types;++i){
        num[i] = false;
    }

    unsigned score = 0, max_score = input.max_slices;
    bool pass = true;
    unsigned curr_score = 0, diff = 0;
    unsigned size = input.n_types;
    // saved_time = std::chrono::high_resolution_clock::now();

    for(;curr_score <= max_score;){
        push_one(num);
        curr_score += input.n_pizzas[last_index];
    }   pop_one(num);

    cout<<"Curr score before loop: "<<tell_score(input.n_pizzas, num)<<'\n';

    while(pass){
        // usleep(1000000);
        pass = false;
        curr_score = tell_score(input.n_pizzas, num);
        diff = max_score - curr_score;
        // cout<<"Diff: "<<diff<<'\n';

        for(unsigned i=0;i<input.n_types-1;++i){
            if(num[i] && !num[i+1]){
                unsigned t_index = i, swap1_index, swap2_index, tmp_ind = 0;
                unsigned curr_diff = 0;

                // std::cout<<"T-F pair found @ "<<i<<", "<<i+1<<'\n';
                DIFF_SEARCH:
                swap1_index = i+1+tmp_ind;
                if(swap1_index>=input.n_types) continue;
                for(unsigned j=i+1+tmp_ind;j>tmp_ind;--j){
                    curr_diff = input.n_pizzas[swap1_index]-input.n_pizzas[j-1-tmp_ind];
                    // cout<<"\tcurr diff: "<<curr_diff<<'\n';
                    if(!pass && curr_diff>diff){
                        break;
                    }
                    if(!num[j-1-tmp_ind]) continue;
                    else if(0<=curr_diff && curr_diff<=diff){
                        swap2_index = j-1-tmp_ind;
                    }
                    pass = true;
                    if(j==tmp_ind+1 && curr_diff<diff){
                        for(;i+2+tmp_ind<input.n_types && num[i+2+tmp_ind];++tmp_ind);
                        if(i+1+tmp_ind == input.n_types) break;
                        goto DIFF_SEARCH;
                    }
                }
                if(pass){
                    // cout<<"> swapping indices "<<swap1_index<<" and "<<swap2_index<<'\n';
                    num[swap1_index] = true;
                    num[swap2_index] = false;
                }   break;
            }
        }
    }
    output.score = tell_score(input.n_pizzas, num);
    for(unsigned i=0;i<input.n_types;++i){
        if(num[i]) output.order.push_back(i);
    }
}