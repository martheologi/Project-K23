#include <iostream>
#include <vector>

using namespace std;

class Vector_Item{
    private:
        int item_id;
        vector<int> x;

    public:
        Vector_Item(int id);
        ~Vector_Item();
        void push(int xi);
        void print_item();
};
