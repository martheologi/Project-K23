#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <sstream>
#include <cmath>
#include <limits>
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
    //while (file.good())
    for(int i=0; i<10; i++)
    {
        if (!getline (file, line)) break;
        c++;

        Curve curve = Initialize_Curve(line);

        Curves_dataset->push_back(curve);
    }
    file.close();

    return c;
}

// Return the sum of distance between all
// the pair of points.
double distance_l1(Point x, Point y)
{
    double sum = 0;
    sum = abs(x.get_x() - y.get_x()) + abs(x.get_y() - y.get_y());

    return sum;
}

double minimum(double t1, double t2, double t3){
    double min = t1;
    if(t2 < min)
        min = t2;
    if(t3 < min)
        min = t3;

    return min;
}

double** DTW(Curve p, Curve q){
    int m1 = p.get_points().size();
    int m2 = q.get_points().size();
    cout << m1 << " " << m2 << endl;
    double** table;
    table = new double* [m1+1];
    for(int i=0; i<m1+1; i++){
        table[i] = new double [m2+1];
    }

    table[0][0] = 0;
    for(int i=1; i<m1; i++){
        table[i][0] = 10000; //std::numeric_limits<double>::max();
    }
    for(int i=1; i<m2; i++){
        table[0][i] = 10000; //std::numeric_limits<double>::max();
    }
    for(int i=1; i<m1; i++){
        for(int j=1; j<m2; j++){
            table[i][j] = distance_l1(p.get_points().at(i), q.get_points().at(j)) + minimum(table[i-1][j-1], table[i][j-1], table[i-1][j]);
        }
    }
    return table;
}

void print_table(double** table, int m1, int m2){
    for(int i=0; i<m1; i++){
        for(int j=0; j<m2; j++){
            cout << table[i][j] << "\t";
        }
        cout << endl;
    }
}
