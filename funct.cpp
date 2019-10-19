#include <iostream>
#include <fstream>
#include <vector>
#include <unordered_map>
#include <random>
#include <cmath>
#include <bits/stdc++.h>

#include "structs.h"
#include "funct.h"
#include "hash.h"

using namespace std;

//epistrefei ena vector item apo th grammh tou arxeiou pou pairnei san orisma
Vector_Item get_item(string line){
  Vector_Item item;
  int id_flag = 1;
  string digits = "";

  //pairnw ena ena ta xi
  for (auto x : line){
    if (x == ' '){
      if(id_flag == 1){
        item.set_id(stoi(digits));
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
  return item;
}

//arxikopoiei ton pinaka me ta data apo to input file
int Initialize_Dataset_Vector(string filename, vector<Vector_Item>* Items){
    string digits = "";
    string line;
    int id_flag = 1;
    int c = 0;
    fstream file;

    file.open(filename);
    // extracting from the file
    while (file.good())
    {
        if (!getline (file, line)) break;
        c++;
        Vector_Item item = get_item(line);

        //apo8hkeuw to dataset se ena vector
        Items->push_back(item);
        id_flag = 1;
        //item.print_item();
    }
    file.close();

    return c;
}

Vector_Item ExactNN(vector<Vector_Item> Items, Vector_Item item, int c){
    int NN_pos = -1;
    int d = item.get_vector().size();
    int NN_dist;
    long int min = 10000000000000;
    int i;

    for(i=0; i<c; i++){

        Vector_Item neighbor_item = Items.at(i);
        NN_dist=distance_l1(item.get_vector(), neighbor_item.get_vector(), d);

        if(NN_dist<min){
            NN_pos= i;
            min=NN_dist;
        }
    }
    cout << Items.at(NN_pos).get_item_id() << " " << NN_dist << endl;
    return Items.at(NN_pos);
}

Vector_Item AproximateNN(vector<Vector_Item> Items, Vector_Item item, vector<unordered_multimap<int, int>> HT, int buckets, int k, int L, long int m, int M, int W){
    int NN_id = -1;
    int NN_position = -1;
    long int NN_dist = 10000000000000;

    int d = item.get_vector().size();

    for(int l=0; l<L; l++){
        //ftiaxnw k hash sunarthseis
        int key = hash_key(item, buckets, d, k, L, W, M, m);//g%buckets;
        //cout << "key of query " << item.get_item_id() << " is " << key << endl;
        auto found = HT.at(l).find(key);

        if(found != HT.at(l).end()){
            auto itr = HT.at(l).equal_range(key);

            //gia ka8e stoixeio me kleidei key
            int retrieved_items = 0;
            for (auto it = itr.first; it != itr.second; it++) {
                retrieved_items++;
                Vector_Item neighbor_item = Items.at(it->second); //edw 8a xreiastei mia find an to id den einai 0-n
                //cout << neighbor_item.get_item_id() << "\t";

                if(retrieved_items > 3*L) break;

                if(distance_l1(item.get_vector(), neighbor_item.get_vector(), d) < NN_dist){
                   NN_id = neighbor_item.get_item_id();
                   NN_position = it->second;
                   NN_dist = distance_l1(item.get_vector(), neighbor_item.get_vector(), d);
                }
            }
            //cout << "Possiboool NN of query " << item.get_item_id() << " is with dist = " << NN_dist << endl;
            //Items.at(NN_position).print_item();
        }
        else
            cout << "!!!!!!!!!!!there is no key " << key << endl;
        //cout << endl;
    }
    cout << "FINAL NN of query " << item.get_item_id() << " is " << Items.at(NN_position).get_item_id() << " " << NN_dist << endl;
    //Items.at(NN_position).print_item();

    return Items.at(NN_position);
}

//grafei ta apotelesmata sto arxeio output
void write_results(string filename, string qID, string NnID, double dLSH, double dTrue, double tLSH, double tTrue)
{
    ofstream file;
    file.open (filename, ios::app); // append mode

    if(file.is_open()){
        file << "Query:" << qID << endl;
        file << "Nearest neighbor:" << NnID << endl;
        file << "distanceLSH:" << dLSH << endl;
        file << "distanceTrue:" << dTrue << endl;
        file << "tLSH:" << tLSH << endl;
        file << "tTrue:" << tTrue << endl << endl;
    }

    file.close();

    return;
}
