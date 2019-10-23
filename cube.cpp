#include <iostream>
#include <fstream>
#include <vector>
#include <unordered_map>
#include <random>
#include <string>
#include <cmath>
#include <iterator>
#include <bits/stdc++.h>

#include "structs.h"
#include "funct.h"
#include "hash.h"

using namespace std;

int main(int argc, char* argv[]){
    int k = atoi(argv[6]);//3;
    int M = atoi(argv[8]);//10;
    int probes = atoi(argv[10]);//2;
    long int m = pow(2, 32) - 5;
    int Modulus = pow(2, (32/k));

    int W = 3000;

    fstream file;
    string INfile=argv[2];
    string Qfile=argv[4];
    string OUTfile=argv[12];

    vector<Vector_Item> Items;

    //arxikopoiw pinaka me ta data apo to input file
    int c = Initialize_Dataset_Vector(INfile, &Items);

    cout << "Dataset with "<< c << " items" << endl;

    //initializing HyperCube
    vector<Hypercube_vertices> HyperCube;

    //eurethrio gia ta apotelesmata ths f
    unordered_map<int, int> f_index;

    //gia ka8e dianusma tou dataset
    for(int n=0; n<c; n++){
        double s;
        random_device rd;
        Vector_Item item = Items.at(n);
        int d = item.get_vector().size();

        default_random_engine generator(rd());

        //ftiaxnw k hash sunarthseis
        uniform_real_distribution<double> distribution(0.0,W);
        for(int j=0; j<k; j++){
            vector<int>a;
            //gia ka8e xi tou dianusmatos vriskw ta ai (tupos diafaneia 21)
            for(int i=0; i<d; i++){
                s = distribution(generator);
                a.push_back(a_generator(item.get_vector().at(i), s, W));
            }
            int h = h_generator(a, d, m, Modulus);
            int f = f_generator(h, &f_index);
            
        }
    }

    return 0;
}
