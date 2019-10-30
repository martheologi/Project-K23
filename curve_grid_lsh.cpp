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
#include "hash.h"
#include "curve_funct.h"

using namespace std;
using namespace std::chrono;

int main(int argc, char* argv[]){

    std::clock_t start;
    double t_true, t_lsh;

    fstream file;
    string INfile=argv[2];
    string Qfile=argv[4];
    string OUTfile=argv[10];

    int k_vec = atoi(argv[6]);
    int L_grid= atoi(argv[8]);

    vector<Curve> Curves_dataset;
    int max_points = 0;
    double max_coord = 0;

    int c = Initialize_Curve_Dataset(INfile, &Curves_dataset, &max_points, &max_coord);
    int buckets = c/16;
    double W = 3000;
    long int m = pow(2, 32) - 5;
    int M = pow(2, (32/k_vec));

    cout << "Dataset with " << c << " curves"<<endl;
    std::cout.precision(16);
    cout << "max dim = " << max_points << "max coord = " << max_coord << endl;

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
    for (int n=0; n<c; n++){
        Curve curve = Curves_dataset.at(n);

        for(int l=0; l<L_grid; l++){
            //ftiaxnw to grid ths kampulhs
            Vector_Item item = grid_curve_vector(curve, max_points, max_coord);

            //to vazw se hash table
            int key = hash_key(item, buckets, max_points*2, k_vec, W, M, m);
            if((key<0) || (key>=buckets)) continue;

            HT[l]->at(key).push_pos(n);
        }
    }
    cout << "finished hashing" << endl;
    // for(int l=0; l<L_grid; l++){
    //     for(int b=0; b<buckets; b++){
    //         HT[l]->at(b).print();
    //     }
    // }

    //anoigw kai diaxeirizomai to file me ta queries
    file.open(Qfile);
    string line;
    double temp;

    while (file.good())
    {
        if (!getline (file, line)) break;

        Curve curve = Initialize_Curve(line, &temp);
        double ExactNN_dist, AprNN_dist;

        start = std::clock();
        Curve ExactNN_curve = curve_ExactNN(Curves_dataset, curve, c, &ExactNN_dist);
        t_true = ( std::clock() - start ) / (double) CLOCKS_PER_SEC;
        //cout << "exact " << ExactNN_dist << endl;

        start = std::clock();
        Curve NN_curve = curve_AproximateNN(Curves_dataset, curve, HT, buckets, k_vec, L_grid, m, M, W, &AprNN_dist, max_points, max_coord);
        t_lsh= ( std::clock() - start ) / (double) CLOCKS_PER_SEC;
        //cout << "aprox " << AprNN_dist << endl;

        write_curve_results("LSH", "LSH", OUTfile, curve.get_id(), ExactNN_curve.get_id(), NN_curve.get_id(), AprNN_dist, ExactNN_dist);

    }

    return 0;
}
