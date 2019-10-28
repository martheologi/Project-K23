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
#include "curve_funct.h"

int main(int argc, char* argv[]){

    fstream file;
    string INfile=argv[2];
    string Qfile=argv[4];
    string OUTfile=argv[10];

    int k_vec = atoi(argv[6]);
    int L_grid= atoi(argv[8]);

    vector<Curve> Curves_dataset;

    int c = Initialize_Curve_Dataset(INfile, &Curves_dataset);
    int buckets = c/16;

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

    //arxikopoiw ta hash tables
    vector<Bucket>** HT = new vector<Bucket>* [L_grid];  //ena gia ka8e grid pou 8a mou dwsoun oi kampules

    for(int l=0; l<L_grid; l++){
        HT[l] = new vector<Bucket>;
        for(int i=0; i<buckets; i++){
            Bucket b;
            b.set_key(i);
            HT[l]->push_back(b);
        }
    }

    //gia ka8e kampulh
    for (int n=0; n<c; c++){
        for(int l=0; l<L_grid; l++){
            //ftiaxnw to grid ths kampulhs
            //to vazw se hash print_table
        }
    }



    return 0;
}
