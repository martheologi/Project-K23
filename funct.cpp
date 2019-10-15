#include <iostream>
#include <fstream>
#include <vector>
#include <unordered_map>
#include <random>
#include <cmath>
#include <bits/stdc++.h>

#include "structs.h"
#include "funct.h"

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
