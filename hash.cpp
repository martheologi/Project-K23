#include <iostream>
#include <vector>
#include <list>
#include <iterator>
#include <string>
#include <random>
#include <cmath>
#include <bits/stdc++.h>

#include "structs.h"
#include "funct.h"
#include "hash.h"

using namespace std;

// Return the sum of distance between all
// the pair of points.
int distance_l1(vector<double> x, vector<double> y, int d)
{
    int sum = 0;
    for (int i = 0; i < d; i++)
        sum += abs(x.at(i) - y.at(i));

    return sum;
}

//vriskw ta a sumfwna me ton tupo sth diafaneia 21
int a_generator(double xi, double s, int W){
    return floor((xi-s)/W);
}

//upswnw tous ari8mous se megalh dunamh xwris overflow
long long int modular_pow(long long int base, long long int exponent, int modulus){
    long long int result = 1;

    while (exponent > 0){
        if (exponent % 2 == 1)
            result = (result * base) % modulus;

        exponent = exponent >> 1;
        base = (base * base) % modulus;
    }

    return result;
}

//vriskei ta h sumfwna me ton tupo sth diafaneia 22
int h_generator(vector<int> a, int d, long int m, int M){
    long long int result=0;
    for(int i=0; i<d; i++){
        result += (a.at(d-(i+1)) * modular_pow(m, i, M));
        result = result%M;
    }
    return result;
}

//kanei concatenation ta h gia na vroume to g
int64_t g_generator(vector<int> h, int k){
    int64_t result = h.at(0);
    for(int i=0; i<k; i++){
        result = result << 32/k | h.at(i);
    }
    return result;
}

//vriskei to key gia to HT sumfwna me tis diafaneies 21-22
int hash_key(Vector_Item item, int buckets, int d, int k, int L, int W, int M, long int m){
    double s;
    random_device rd;
    default_random_engine generator(rd());

    vector<int>h;
    //ftiaxnw k hash sunarthseis
    uniform_real_distribution<double> distribution(0.0,W);
    for(int j=0; j<k; j++){
        vector<int>a;
        //gia ka8e xi tou dianusmatos vriskw ta ai (tupos diafaneia 21)
        for(int i=0; i<d; i++){
            s = distribution(generator);
            a.push_back(a_generator(item.get_vector().at(i), s, W));
        }
        h.push_back(h_generator(a, d, m, M));
    }
    //ftiaxnw to g me concatenation
    int64_t g = g_generator(h, k);
    return g%buckets;
}
