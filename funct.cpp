#include <iostream>
#include <fstream>
#include <bits/stdc++.h>

#include "structs.h"

using namespace std;

int main()
{
    fstream file;
    string digits = "";
    string line;
    int c = 0;
    int id_flag = 1;

    // open file
    file.open("input_small_id");

    // extracting from the file
    while (file.good())
    {
        // displaying content
        if (!getline (file, line)) break;
        c++;
        //cout << "KAINOURIO MAKATZUNI!!!" << endl;
        Vector_Item item(c);

        //pairnw ena ena ta xi
        for (auto x : line){
            if (x == ' '){
                if(id_flag == 1){
                    id_flag = 0;
                }
                else{
                    item.push(stoi(digits));
                }
                digits = "";
            }
            else{
               digits = digits + x;
            }
        }
        //item.print_item();
        id_flag = 1;
    }
    cout << "Dataset with "<< c << " items" << endl;

    file.close();

    return 0;
}
