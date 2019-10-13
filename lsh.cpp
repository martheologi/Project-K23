#include <iostream>
#include <fstream>
#include <vector>
#include <unordered_map>
#include <random>
#include <cmath>
#include <bits/stdc++.h>

#include "structs.h"
#include "hash.h"

using namespace std;

int main()
{
    fstream file;
    string digits = "";
    string line;
    int c = 0;
    int id_flag = 1;
    int L = 20;
    int W = 3000;
    int k = 5;
    long int m = 1;
    int M = pow(2, (32/k));
    //cout << m << endl << M << endl;

    // open file
    file.open("input_small_id");
    vector<Vector_Item> Items;

    // extracting from the file
    while (file.good())
    {
        if (!getline (file, line)) break;
        c++;
        //cout << "KAINOURIO MAKATZUNI!!!" << endl;
        Vector_Item item(c);

        //pairnw ena ena ta xi
        for (auto x : line){
            if (x == ' '){
                if(id_flag == 1){
                    id_flag = 0;
                }
                else{
                    item.push(stod(digits));
                }
                digits = "";
            }
            else{
               digits = digits + x;
            }
        }
        //apo8hkeuw to dataset se ena vector
        Items.push_back(item);
        id_flag = 1;
        //item.print_item();
    }
    cout << "Dataset with "<< c << " items" << endl;

    //pinakas apo hash tables
    vector<unordered_map<int,int>> HT;

    //arxikopoiw hash table me key tupou int kai plhroforia tupou int (krataw mono to id afou exw to dianusma sth domh)
    for(int i=0; i<L; i++){
        unordered_map<int, int> umap;
        HT.push_back(umap);
    }

    //gia ka8e dianusma tou dataset
    for(int n=0; n<c; n++){
        Vector_Item item = Items.at(n);
        int d = item.get_vector().size();
        default_random_engine generator;
        uniform_real_distribution<double> distribution(0.0,W);

        vector<int>a;
        vector<int>h;
        double s;

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
        cout << endl;
    }

    file.close();

    return 0;
}
