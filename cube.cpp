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

using namespace std;

int main(){
    int k = 3;
    int M = 10;
    int probes = 2;

    vector<Vector_Item> Items;

    //arxikopoiw pinaka me ta data apo to input file
    int c = Initialize_Dataset_Vector("input_small_id", &Items);

    cout << "Dataset with "<< c << " items" << endl;

    //pinakas apo hash tables
    vector<unordered_multimap<int,int>> HT;

    //HASHIIIIIING
    //gia ka8e dianusma tou dataset
    for(int n=0; n<c; n++){
        Vector_Item item = Items.at(n);
        int d = item.get_vector().size();

        for(int l=0; l<L; l++){
            int key = hash_key(item, buckets, d, k, L, W, M, m);//g%buckets;
        }
    }

    return 1;
}
