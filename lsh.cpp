#include <iostream>
#include <fstream>
#include <vector>
#include <unordered_map>
#include <random>
#include <string>
#include <cmath>
#include <bits/stdc++.h>

#include "structs.h"
#include "funct.h"
#include "hash.h"

using namespace std;

int main()
{
    fstream file;
    int L = 5;
    int W = 3000;
    int k = 4;
    long int m = pow(2, 32) - 5;
    int M = pow(2, (32/k));

    vector<Vector_Item> Items;

    //arxikopoiw pinaka me ta data apo to input file
    int c = Initialize_Dataset_Vector("input_small_id", &Items);

    cout << "Dataset with "<< c << " items" << endl;

    //pinakas apo hash tables
    vector<unordered_map<int,int>> HT;

    //arxikopoiw hash table me key tupou int kai plhroforia tupou int (krataw mono to id afou exw to dianusma sth domh)
    for(int i=0; i<L; i++){
        unordered_map<int, int> umap;
        HT.push_back(umap);
    }

    default_random_engine generator;
    uniform_real_distribution<double> distribution(0.0,W);
    //gia ka8e dianusma tou dataset
    for(int n=0; n<c; n++){
        Vector_Item item = Items.at(n);
        int d = item.get_vector().size();

        vector<int>a;
        vector<int>h;
        double s;

        for(int l=0; l<L; l++){
            //ftiaxnw k hash sunarthseis
            for(int j=0; j<k; j++){
                //gia ka8e xi tou dianusmatos vriskw ta ai (tupos diafaneia 21)
                for(int i=0; i<d; i++){
                    s = distribution(generator);
                    a.push_back(a_generator(item.get_vector().at(i), s, W));
                    //cout << item.get_vector().at(i)<< "|" << s << " ";
                }
                h.push_back(h_generator(a, d, m, M));
            }
            int g = g_generator(h, k);
            //to vazw sto hash table
            HT.at(l).insert({g, item.get_item_id()});
        }
    }

    //anoigw kai diaxeirizomai to file me ta queries
    file.open("query_small_id");


    file.close();


    return 0;
}
