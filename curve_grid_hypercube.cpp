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

    return 0;
}
