#include <iostream>
#include <vector>

using namespace std;

class Vector_Item{
    private:
        int item_id;
        vector<double> x;

    public:
        Vector_Item();
        ~Vector_Item();
        void set_id(int id);
        void push(double xi);
        int get_item_id();
        vector<double> get_vector();
        void print_item();
};


class Hypercube_vertices{
    private:
        string code;
        int *p_vector;

    public:
        Hypercube_vertices();
        ~Hypercube_vertices();
        void set_code(string HCcode)
        string get_code();
        int* get_p_vector();
}
