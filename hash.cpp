#include <iostream>
#include <vector>
#include <list>
#include <iterator>
#include <string>
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

int concat(int a, int b)
{
    // Convert both the integers to string
    string s1 = to_string(a);
    string s2 = to_string(b);

    // Concatenate both strings
    string s = s1 + s2;
    //cout << s << endl;

    // Convert the concatenated string
    // to integer
    int c = stoi(s);

    // return the formed integer
    return c;
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
    //cout << result%M << " ";
    return result%M;
}

int g_generator(vector<int> h, int k){
    int result = concat(h.at(0), h.at(1));
    //cout << concat()<< endl;
    for(int i=2; i<k; i++){
        result = concat(result, h.at(i));
    }
    //cout << result << endl;
    return result;
}
