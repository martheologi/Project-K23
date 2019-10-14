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
