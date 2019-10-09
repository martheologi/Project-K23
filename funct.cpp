#include <iostream>
#include <fstream>
using namespace std;

int main()
{
    fstream file;
    string digits;

    // open file
    file.open("input_small_id.txt");


    // extracting from the file
    file >> digits;
    while (file.good())
    {
        // displaying content
        cout << digits << " ";
        file >> digits;
        //trying to seperate after \n
        if (file.peek() == '\n'){
            cout << "KAINOURIO MAKATZUNI!!!" << endl;
        }
    }

    file.close();

    return 0;
}
