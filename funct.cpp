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

using namespace std;

//epistrefei ena vector item apo th grammh tou arxeiou pou pairnei san orisma
Vector_Item initialize_item(string line){
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
        Vector_Item item = initialize_item(line);

        //apo8hkeuw to dataset se ena vector
        Items->push_back(item);
        id_flag = 1;
    }
    file.close();

    return c;
}

Vector_Item ExactNN(vector<Vector_Item> Items, Vector_Item item, int c, int* ExactNN_dist){
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

    *ExactNN_dist = min;
    return Items.at(NN_pos);
}

Vector_Item AproximateNN(vector<Vector_Item> Items, Vector_Item item, vector<unordered_multimap<int, int>> HT, int buckets, int k, int L, long int m, int M, int W, int* AprNN_dist){
    int NN_id = -1;
    int NN_position = -1;
    long int NN_dist = 10000000000000;

    int d = item.get_vector().size();

    for(int l=0; l<L; l++){
        //ftiaxnw k hash sunarthseis
        int key = hash_key(item, buckets, d, k, L, W, M, m);//g%buckets;
        auto found = HT.at(l).find(key);

        if(found != HT.at(l).end()){
            auto itr = HT.at(l).equal_range(key);

            //gia ka8e stoixeio me kleidei key
            int retrieved_items = 0;
            for (auto it = itr.first; it != itr.second; it++) {
                retrieved_items++;
                Vector_Item neighbor_item = Items.at(it->second); //edw 8a xreiastei mia find an to id den einai 0-n

                if(retrieved_items > 3*L) break;

                if(distance_l1(item.get_vector(), neighbor_item.get_vector(), d) < NN_dist){
                   NN_id = neighbor_item.get_item_id();
                   NN_position = it->second;
                   NN_dist = distance_l1(item.get_vector(), neighbor_item.get_vector(), d);
                }
            }
        }
        else
            cout << "!!!!!!!!!!!there is no key " << key << endl;
    }
    *AprNN_dist = NN_dist;

    return Items.at(NN_position);
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

//grafei ta apotelesmata sto arxeio output
void write_results(string filename, int qID, int NnID, int dLSH, int dTrue, double tLSH, double tTrue)
{
    ofstream file;
    file.open (filename, ios::app); // append mode

    if(file.is_open()){
        file << "Query:" << qID << endl;
        file << "Nearest neighbor:" << NnID << endl;
        file << "distanceLSH:" << dLSH << endl;
        file << "distanceTrue:" << dTrue << endl;
        file << "tLSH:" << tLSH << " s." << endl;
        file << "tTrue:" << tTrue << " s." << endl << endl;
    }

    file.close();

    return;
}
