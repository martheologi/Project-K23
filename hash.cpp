#include <iostream>
#include <vector>
#include <list>
#include <iterator>
#include <random>
#include <cmath>
#include <bits/stdc++.h>

using namespace std;

// Return the sum of distance between all
// the pair of points.
int distance_l1(int x[], int y[], int n)
{
    int sum = 0;

    // for each point, finding distance to
    // rest of the point
    for (int i = 0; i < n; i++)
        sum += abs(x[i] - y[i]);
    return sum;
}

int a_generator(double xi, double s, int W){
    return floor((xi-s)/W);
}

int h_generator(vector<int> a, int d, long int m, int M){
    long long int result=0;
    for(int i=0; i<d; i++){
        //cout << a.at(d-(i+1)) << " ";
        result += (a.at(d-(i+1)) * pow(m, i));
    }
    //cout << result <<endl;
    cout << result%M << " ";
    return result%M;
}
