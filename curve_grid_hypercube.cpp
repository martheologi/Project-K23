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

int main(int argc, char* argv[]){
    fstream file;
    string INfile=argv[2];
    string Qfile=argv[4];
    string OUTfile=argv[14];

    int k_hypercube = atoi(argv[6]);
    int M= atoi(argv[8]);
    int probes = atoi(argv[10]);
    int L_grid = atoi(argv[12]);

    vector<Curve> Curves_dataset;
    int max_points = 0;
    double max_coord = 0;

    int c = Initialize_Curve_Dataset(INfile, &Curves_dataset, &max_points, &max_coord);
    int buckets = c/16;
    double W = 3000;
    long int m = pow(2, 32) - 5;
    int Modulus = pow(2, (32/k_hypercube));

    cout << "Dataset with " << c << " curves"<<endl;
    std::cout.precision(16);
    cout << "max dim = " << max_points << "max coord = " << max_coord << endl;

    //initializing HyperCube
    vector<Hypercube_vertices> HyperCube;

    //eurethrio gia ta apotelesmata ths f
    unordered_map<int, int> f_index;

    //gia ka8e kampulh
    for (int n=0; n<c; n++){
        Curve curve = Curves_dataset.at(n);

      //  for(int l=0; l<L_grid; l++){
        //ftiaxnw to grid ths kampulhs
        Vector_Item item = grid_curve_vector(curve, max_points, max_coord);

        //to vazw sto HyperCube
        string vertice = get_vertice(item, k_hypercube, W, m, Modulus, &f_index);
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
        //}
    }
    cout << "finished hypercube" << endl;

    //print_HyperCube(HyperCube);

    file.open(Qfile);
    string line;
    double temp;

    while (file.good()){
        if (!getline (file, line)) break;

        Curve curve = Initialize_Curve(line, &temp);
        double ExactNN_dist, HyperCubeNN_dist;

        Curve ExactNN_curve = curve_ExactNN(Curves_dataset, curve, c, &ExactNN_dist);

        Curve HyperCubeNN_curve = curve_HyperCubeNN(Curves_dataset, curve, HyperCube, &f_index, k_hypercube, M, Modulus, m, probes, W, &HyperCubeNN_dist, max_points, max_coord);

        write_curve_results("LSH", "Hypercube", OUTfile, curve.get_id(), ExactNN_curve.get_id(), HyperCubeNN_curve.get_id(), HyperCubeNN_dist, ExactNN_dist);
    }

    cout << endl;


    return 0;
}
