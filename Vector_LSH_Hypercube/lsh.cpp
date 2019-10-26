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
using namespace std::chrono;

int main(int argc, char* argv[])
{
    std::clock_t start;
    double t_true, t_lsh;

    fstream file;
    string INfile=argv[2];
    string Qfile=argv[4];
    string OUTfile=argv[10];

    int k= atoi(argv[6]);
    int L= atoi(argv[8]);
    double W = 3000;
    long int m = pow(2, 32) - 5;
    int M = pow(2, (32/k));

    vector<Vector_Item> Items;

    //arxikopoiw pinaka me ta data apo to input file
    int c = Initialize_Dataset_Vector(INfile, &Items);
    int buckets = c/16;

    cout << "Dataset with "<< c << " items" << endl;

    //pinakas apo hash tables
    //vector<unordered_multimap<int,int>> HT;

    //arxikopoiw hash table me key tupou int kai plhroforia tupou int
    //(krataw mono th 8esh tou ston vector Items afou exw to dianusma ekei)
    // for(int i=0; i<L; i++){
    //     unordered_multimap<int, int> umap;
    //     HT.push_back(umap);
    // }
    vector<Bucket>** HT = new vector<Bucket>* [L];

    for(int l=0; l<L; l++){
        HT[l] = new vector<Bucket>;
        for(int i=0; i<buckets; i++){
            Bucket b;;
            b.set_key(i);
            HT[l]->push_back(b);
        }
    }

    //HASHIIIIIING
    //gia ka8e dianusma tou dataset
    for(int n=0; n<c; n++){
        Vector_Item item = Items.at(n);
        int d = item.get_vector().size();

        for(int l=0; l<L; l++){
            int key = hash_key(item, buckets, d, k, L, W, M, m);//g%buckets;
            //to vazw sto hash table
            if((key<0) || (key>=buckets)) continue;
            HT[l]->at(key).push_pos(n);
            //HT.at(l).insert({key, n});
        }
    }

    //anoigw kai diaxeirizomai to file me ta queries
    file.open(Qfile);
    string line;

    while (file.good())
    {
        if (!getline (file, line)) break;

        Vector_Item item = initialize_item(line);
        int ExactNN_dist, AprNN_dist;

        start = std::clock();
        Vector_Item ExactNN_item = ExactNN(Items, item, c, &ExactNN_dist);
        t_true = ( std::clock() - start ) / (double) CLOCKS_PER_SEC;

        start = std::clock();
        Vector_Item NN_item = AproximateNN(Items, item, HT, buckets, k, L, m, M, W, &AprNN_dist);
        t_lsh= ( std::clock() - start ) / (double) CLOCKS_PER_SEC;

        write_results(OUTfile, item.get_item_id(), NN_item.get_item_id(), AprNN_dist, ExactNN_dist, t_lsh, t_true);
    }

    file.close();

    for(int l=0; l<L; l++){
        delete HT[l];
    }
    delete[] HT;

    return 0;
}
