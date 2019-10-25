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

using namespace std;

int main(int argc, char* argv[]){

    std::clock_t start;
    double t_true, t_cube;

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

    //PROJECTIOOOOON
    //gia ka8e dianusma tou dataset
    for(int n=0; n<c; n++){

        Vector_Item item = Items.at(n);

        string vertice = get_vertice(item, k, W, m, Modulus, &f_index);
        int pos;
        if((pos = find_vertice(HyperCube, vertice)) != -1){
            HyperCube.at(pos).add_point(n);
        }
        else{
            Hypercube_vertices new_vertice;
            new_vertice.set_code(vertice);
            new_vertice.add_point(n);
            HyperCube.push_back(new_vertice);
        }
    }
    //print_HyperCube(HyperCube);

    //anoigw kai diaxeirizomai to file me ta queries
    file.open(Qfile);
    string line;

    while (file.good()){
        if (!getline (file, line)) break;

        Vector_Item item = initialize_item(line);
        int ExactNN_dist, HyperCubeNN_dist;

        start = std::clock();
        Vector_Item ExactNN_item = ExactNN(Items, item, c, &ExactNN_dist);
        t_true = ( std::clock() - start ) / (double) CLOCKS_PER_SEC;

        start = std::clock();
        Vector_Item HyperCubeNN_item = HyperCubeNN(Items, item, HyperCube, &f_index, k, M, Modulus, m, probes, W, &HyperCubeNN_dist);
        t_cube= ( std::clock() - start ) / (double) CLOCKS_PER_SEC;

        write_results(OUTfile, item.get_item_id(), HyperCubeNN_item.get_item_id(), HyperCubeNN_dist, ExactNN_dist, t_cube, t_true);
    }

    cout << endl;

    return 0;
}
