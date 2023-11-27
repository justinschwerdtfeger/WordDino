#include <fstream>
#include <iostream>
#include <vector>
using namespace std;

string toLower(const string &input) {
    string output;
    for (char character : input) {
        output += tolower(character);
    }
    return output;
}
int main() {
    ifstream inFile;
    ofstream outFile;
    string contents;

    inFile.open("word-list-6-letter.txt");
    outFile.open("word-list-6-letter-corrected.txt");

    while (inFile >> contents) {
        contents = toLower(contents);
        outFile << contents << endl;
    }

    inFile.close();
    return 0;
}
