#include <iostream>
#include <fstream>
#include <vector>
#include <unordered_map>
#include <random>
#include <string>
#include <cmath>
#include <iterator>
#include <chrono>
#include <ctime>
#include <bitset>
#include <bits/stdc++.h>

#include "structs.h"
#include "funct.h"

int main(int argc, char* argv[]){

    fstream file;
    string INfile=argv[2];
    string Qfile=argv[4];
    string OUTfile=argv[10];

    int k_vec = atoi(argv[6]);
    int L_vec= atoi(argv[8]);

    vector<Curve> Curves_dataset;

    int c = Initialize_Curve_Dataset(INfile, &Curves_dataset);

    // for(int i=0; i<Curves_dataset.size(); i++){
    //     Curves_dataset.at(i).print();
    // }
    cout << "Dataset with " << c << " curves"<<endl;


    return 0;
}
