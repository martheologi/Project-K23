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

    /*for(int i=0; i<2; i++){
        int m1 = Curves_dataset.at(i).get_points().size();
        int m2 = Curves_dataset.at(0).get_points().size();
        double **table = DTW(Curves_dataset.at(i), Curves_dataset.at(0));
        cout << "!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!"<<endl;
        print_table(table, m1, m2);
        for(int t=0; t<m1+1; t++)
            delete[] table[i];
        delete[] table;
    }*/


    return 0;
}
