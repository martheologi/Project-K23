#include <iostream>
#include <vector>

using namespace std;

class Vector_Item{
    private:
        int item_id;
        vector<double> x;

    public:
        Vector_Item(int id);
        ~Vector_Item();
        void push(double xi);
        int get_item_id();
        vector<double> get_vector();
        void print_item();
};
