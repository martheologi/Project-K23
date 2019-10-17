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

int main()
{
    fstream file;
    int L = 5;
    double W = 3000;
    int k = 4;
    long int m = pow(2, 32) - 5;
    int M = pow(2, (32/k));

    vector<Vector_Item> Items;

    //arxikopoiw pinaka me ta data apo to input file
    int c = Initialize_Dataset_Vector("input_small_id", &Items);
    int buckets = c/16;

    cout << "Dataset with "<< c << " items" << endl;

    //pinakas apo hash tables
    vector<unordered_multimap<int,int>> HT;

    //arxikopoiw hash table me key tupou int kai plhroforia tupou int
    //(krataw mono th 8esh tou ston vector Items afou exw to dianusma ekei)
    for(int i=0; i<L; i++){
        unordered_multimap<int, int> umap;
        HT.push_back(umap);
    }

    //HASHIIIIIING
    //gia ka8e dianusma tou dataset
    for(int n=0; n<c; n++){
        Vector_Item item = Items.at(n);
        int d = item.get_vector().size();

        for(int l=0; l<L; l++){
            int key = hash_key(item, buckets, d, k, L, W, M, m);//g%buckets;
            //to vazw sto hash table
            HT.at(l).insert({key, n});
        }
    }

    //printing HT
    /*for(int l=0; l<L; l++){
        unordered_multimap<int, int>:: iterator itr;
        cout << "count = " << HT.at(l).bucket_count() << endl;
        for(itr=HT.at(l).begin(); itr!=HT.at(l).end(); itr++){
            cout << "key: " << itr->first << " value: " << itr->second << " in bucket: " << HT.at(l).bucket(itr->first);
            cout << "|" << HT.at(l).bucket_size(HT.at(l).bucket(itr->first)) << endl;
        }
        cout << endl;
    }*/

    //anoigw kai diaxeirizomai to file me ta queries
    file.open("query_small_id");
    string line;

    while (file.good())
    {
        if (!getline (file, line)) break;
        double s;

        c++;
        Vector_Item item = get_item(line);

        Vector_Item NN_item = AproximateNN(Items, item, HT, buckets, k, L, m, M, W);
    }

    file.close();

    return 0;
}
