#include <iostream>
#include <fstream>
#include <vector>
#include <unordered_map>
#include <random>
#include <string>
#include <iterator>
#include <cmath>
#include <bits/stdc++.h>
#include <bitset>

#include "structs.h"
#include "funct.h"
#include "hash.h"

Hypercube_vertices::Hypercube_vertices(){}

Hypercube_vertices::~Hypercube_vertices(){}

void Hypercube_vertices::set_code(string HCcode){
    code = HCcode;
}

string Hypercube_vertices::get_code(){
    return code;
}

vector<int> Hypercube_vertices::get_p_vector(){
    return p_vector;
}

void Hypercube_vertices::add_point(int point_pos){
    p_vector.push_back(point_pos);
}

//epistrefei th 8esh tou vector pou vrhke thn korifh vertice
int find_vertice(vector<Hypercube_vertices> HyperCube, string vertice){
    for(int i=0; i<HyperCube.size(); i++){
        if(HyperCube.at(i).get_code() == vertice)
            return i;
    }

    return -1;
}

void print_HyperCube(vector<Hypercube_vertices> HyperCube){
    for(int i=0; i<HyperCube.size(); i++){
        cout << HyperCube.at(i).get_code() << "------> " << HyperCube.at(i).get_p_vector().size()<< " ";
        for(int j=0; j<HyperCube.at(i).get_p_vector().size(); j++){
            cout << HyperCube.at(i).get_p_vector().at(j) << " ";
        }
        cout << endl;
    }
}

Vector_Item HyperCubeNN(vector<Vector_Item> Items, Vector_Item item, vector<Hypercube_vertices> HyperCube, unordered_map<int, int> *f_index, int k, int M, int Modulus, long int m, int probes, int W, int *HyperCubeNN_dist){

    string vertice = get_vertice(item, k, W, m, Modulus, f_index);
    int d = item.get_vector().size();
    int NN_position = -1;
    long int NN_dist = 10000000000000;
    const int bits = 3;
    //const int bits = const_cast<const int&>(k);

    //psaxnw NN prwta sthn korufh pou anhkei to query
    int pos;
    if((pos = find_vertice(HyperCube, vertice)) != -1){
        for(int i=0; i<HyperCube.at(pos).get_p_vector().size(); i++){
            if(i == M) break;

            Vector_Item neighbor_item = Items.at(HyperCube.at(pos).get_p_vector().at(i)); //HyperCube.at(pos).get_p_vector().at(i) se auth th 8esh krataw to position tooy shmeiou ston vector Items

            if(distance_l1(neighbor_item.get_vector(), item.get_vector(), d) < NN_dist){
                NN_position = HyperCube.at(pos).get_p_vector().at(i);
                NN_dist = distance_l1(neighbor_item.get_vector(), item.get_vector(), d);
            }
        }
    }
    else{
        cout << "ERROOOOOOOOR" << endl;
    }

    //psaxnw NN se probes akoma korufes
    for(int p=0; p<probes; p++){
        // vector<bool> bit_vertice;
        // for(int v=0; v<vertice.length(); v++){
        //     bit_vertice.push_back(vertice[v]);
        // }
        //bit_vertice.at(p)  = ! bit_vertice.at(p);
        //string new_vertice;
        // for(int v=0; v<bit_vertice.size(); v++){
        //     new_vertice += ('0'+bit_vertice.at(v));
        // }
        bitset<bits> bit_vertice(vertice); //metatrepei to string se bits
        int pos;
        bit_vertice.set(p, !bit_vertice[p]); //allazei ka8e fora ena bit
        string new_vertice = bit_vertice.to_string<char,std::string::traits_type,std::string::allocator_type>();

        //cout << new_vertice << "\t";
        if((pos = find_vertice(HyperCube, new_vertice)) != -1){
            for(int i=0; i<HyperCube.at(pos).get_p_vector().size(); i++){
                if(i == M) break;

                Vector_Item neighbor_item = Items.at(HyperCube.at(pos).get_p_vector().at(i)); //HyperCube.at(pos).get_p_vector().at(i) se auth th 8esh krataw to position tooy shmeiou ston vector Items

                if(distance_l1(neighbor_item.get_vector(), item.get_vector(), d) < NN_dist){
                    NN_position = HyperCube.at(pos).get_p_vector().at(i);
                    NN_dist = distance_l1(neighbor_item.get_vector(), item.get_vector(), d);
                }
            }
        }
        else{
            cout << "ERROOOOOOOOR" << endl;
        }
    }

    *HyperCubeNN_dist = NN_dist;
    //cout << NN_dist << endl;
    return Items.at(NN_position);
}
