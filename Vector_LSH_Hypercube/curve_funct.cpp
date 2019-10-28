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

Curve Initialize_Curve(string line, double* max_coord){
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
            if(*max_coord < p.get_x())
                *max_coord = p.get_x();
            digits = "";
        }
        else if(x == ')'){
            p.set_y(stod(digits));
            if(*max_coord < p.get_y())
                *max_coord = p.get_y();
            curve.push_point(p);
            digits = "";
        }
        else{
            digits = digits + x;
        }
    }
    return curve;
}

int Initialize_Curve_Dataset(string filename, vector<Curve>* Curves_dataset, int* max_points, double* max_coord){
    string digits = "";
    string line;
    int c = 0;
    fstream file;

    file.open(filename);

    // extracting from the file
    //while (file.good())
    for(int i=0; i<100; i++)
    {
        if (!getline (file, line)) break;
        c++;

        Curve curve = Initialize_Curve(line, max_coord);

        Curves_dataset->push_back(curve);

        if(*max_points < curve.get_m())
            *max_points = curve.get_m();
    }
    file.close();

    return c;
}

// Return the sum of distance between all
// the pair of points.
double point_distance(Point x, Point y)
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

void a1_a2(double* a1, double* a2, Point t, Point point, double delta){
    *a1 = (point.get_x()-t.get_x())/delta;
    //cout << *a1 <<endl;
    *a2 = (point.get_y()-t.get_y())/delta;
    int floor_a1 = floor(*a1);
    int floor_a2 = floor(*a2);
    int ceiling_a1 = ceil(*a1);
    int ceiling_a2 = ceil(*a2);
    double manh1 = abs(floor_a1 + t.get_x() - point.get_x()) + abs(floor_a2 + t.get_y() - point.get_y());
    int min = manh1;
    *a1 = floor_a1;
    *a2 = floor_a2;
    double manh2 = abs(floor_a1 + t.get_x() - point.get_x()) + abs(ceiling_a2 + t.get_y() - point.get_y());
    if(min > manh2) {
        min = manh2;
        *a1 = floor_a1;
        *a2 = ceiling_a2;
    }
    double manh3 = abs(ceiling_a1 + t.get_x() - point.get_x()) + abs(floor_a2 + t.get_y() - point.get_y());
    if(min > manh3){
        min = manh2;
        *a1 = ceiling_a1;
        *a2 = floor_a2;
    }
    double manh4 = abs(ceiling_a1 + t.get_x() - point.get_x()) + abs(ceiling_a2 + t.get_y() - point.get_y());
    if(min > manh4){
        min = manh2;
        *a1 = ceiling_a1;
        *a2 = ceiling_a2;
    }
    return;
}

double** DTW(Curve p, Curve q){
    int m1 = p.get_points().size();
    int m2 = q.get_points().size();
    //cout << m1 << " " << m2 << endl;
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
            table[i][j] = point_distance(p.get_points().at(i), q.get_points().at(j)) + minimum(table[i-1][j-1], table[i][j-1], table[i-1][j]);
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

Curve curve_ExactNN(vector<Curve> Curves_dataset, Curve curve, int c, double* ExactNN_dist){
    int NN_pos = -1;
    //int d = curve.get_vector().size();
    int NN_dist;
    long int min = 10000000000000;
    int i;

    for(i=0; i<c; i++){
        int m1 = Curves_dataset.at(i).get_points().size();
        int m2 = curve.get_points().size();
        Curve neighbor_curve = Curves_dataset.at(i);
        double **table = DTW(Curves_dataset.at(i),curve);
        NN_dist = table[m1-1][m2-1];

        if(NN_dist<min){
            NN_pos= i;
            min=NN_dist;
        }
        for(int t=0; t<m1+1; t++)
            delete[] table[t];
        delete[] table;
    }

    *ExactNN_dist = min;
    return Curves_dataset.at(NN_pos);
}
