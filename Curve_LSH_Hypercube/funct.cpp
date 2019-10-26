#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <sstream>
#include <cmath>
#include <bits/stdc++.h>

#include "structs.h"
#include "funct.h"

Curve Initialize_Curve(string line){
    Curve curve;
    int id_flag = 1;
    int m_flag = 2;
    string digits = "";

    for (auto x : line){
        Point p;
        if (x == '\t'){
            if(id_flag == 1){
              curve.set_id(digits);
              id_flag = 0;
              m_flag--;
            }
            if(m_flag == 1){
                curve.set_m(stoi(digits));
            }
            digits = "";
        }
        else if(x == '('){
            digits = "";
        }
        else if(x == ','){
            p.set_x(stod(digits));
            //cout << setprecision(16) << stod(digits)<< endl;
            digits = "";
        }
        else if(x == ')'){
            p.set_y(stod(digits));

            curve.push_point(p);
            digits = "";
        }
        else{
            digits = digits + x;
        }
    }
    return curve;
}

int Initialize_Curve_Dataset(string filename, vector<Curve>* Curves_dataset){
    string digits = "";
    string line;
    int c = 0;
    fstream file;

    file.open(filename);

    // extracting from the file
    while (file.good())
    //for(int i=0; i<10; i++)
    {
        if (!getline (file, line)) break;
        c++;

        Curve curve = Initialize_Curve(line);

        Curves_dataset->push_back(curve);
    }
    file.close();

    return c;
}
