#include <iostream>
#include <vector>
#include <string>

#include "structs.h"

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
