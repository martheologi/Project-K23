#include <iostream>
#include <fstream>
#include <string>
using namespace std;


void write_results(string filename, string qID, string NnID, double dLSH, double dTrue, double tLSH, double tTrue)
{

    ofstream file;
    file.open (filename, ios::app); // append mode

    if(file.is_open()){
        file << "Query:" << qID << endl;
        file << "Nearest neighbor:" << NnID << endl;
        file << "distanceLSH:" << dLSH << endl;
        file << "distanceTrue:" << dTrue << endl;
        file << "tLSH:" << tLSH << endl;
        file << "tTrue:" << tTrue << endl << endl;
    }

    file.close();

    return;
}

int main(){

    write_results("output_file.txt", "pirgos", "lalospito", 1.2345 , 5.4321 , 6.7890 , 9.0876);

}
