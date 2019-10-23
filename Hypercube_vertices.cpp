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

int* Hypercube_vertices::get_p_vector(){
    return p_vector;
}
