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
            int d = 2;
            double delta = 0.000001;
            vector<Point> grid;

            random_device rd;
            default_random_engine generator(rd());
            uniform_real_distribution<double> distribution(0.0,d);

            //gia ka8e shmeio 8a ftiaksw to (a1*delta, a2*delta)
            for(int p=0; p<curve.get_m(); p++){
                Point t, point = curve.get_points().at(p);
                Point g;
                double a1, a2;

                t.set_x(distribution(generator));
                t.set_y(distribution(generator));
                a1_a2(&a1, &a2, t, point, delta);

                //cout << "a1 = " << a1 << " a2 = "<< a2 << endl;
                g.set_x((a1*delta)+t.get_x());
                g.set_y((a2*delta)+t.get_y());

                // std::cout.precision(16);
                // cout << "(" << point.get_x() << ", " << point.get_y() << ") -----> ";
                // cout << "(" << t.get_x() << ", " << t.get_y() << ")" << " ------> ";
                // cout << "(" << g.get_x() << ", " << g.get_y() << ")" << endl;
                int found = 0;
                for(int i=0; i<grid.size(); i++){
                    if((grid.at(i).get_x() == g.get_x()) && (grid.at(i).get_y() == g.get_y())){
                        found = 1;
                        break;
                    }
                }
                if(found == 0) grid.push_back(g);
            }
            //ftixnw dianisma apo to grid
            Vector_Item item;
            //vazw se dianusma me th seira ta xi kai ta yi apo ta points ths curve
            for(int i=0; i<grid.size(); i++){
                    item.push(grid.at(i).get_x());
                    item.push(grid.at(i).get_y());
            }
            for(int i=grid.size(); i<max_points*2; i++){
                item.push(max_coord);
            }
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
