#include <fstream>
#include <ctime>
#include <cstdlib>
#include <iostream>
#include <string>
using namespace std;

void intro();
string getWord(int lenghtOfWord);
int getNumberOfGuesses();
int getLengthOfWord();
void game(int numberOfGuesses, string word);

int main() {
    intro();
    int numberOfGuesses = getNumberOfGuesses();
    int lengthOfWord = getLengthOfWord();
    string word = getWord(lengthOfWord);
    game(numberOfGuesses, word);
    return 0;
}

// Justin
void intro() {
    // TODO: improve these instructions
    cout << "               __" << endl;
    cout << "              / _)" << endl;
    cout << "     _.----._/ /" << endl;
    cout << "    /         /" << endl;
    cout << " __/ (  | (  |" << endl;
    cout << "/__.-'|_|--|_|" << endl;

    cout << "Hello and welcome to Word Dino!" << endl;
    cout << "Here are the rules" << endl;
    cout << "If your text turns yellow, your letter is in the word, but it is "
            "not in the right place"
         << endl;
    cout << "If your text turns green, your letter is in the word and in the "
            "right place"
         << endl;
    cout << "Have fun!" << endl;
}

// Luke
// This should read the lengthOf word and read the corresponding file (there is
// only 1 so far which is for 5 letter words)
string getWord(int lengthOfWord) {
// Open the file
    ifstream file(filename);

    // Check if the file is opened successfully
    if (!file.is_open()) {
        cerr << "Error opening file: " << filename << endl;
        return "";
    }

    // Count the number of lines in the file
    int numberOfLines = 0;
    string line;
    while (getline(file, line)) {
        numberOfLines++;
    }

    // Check if the file is empty
    if (numberOfLines == 0) {
        cerr << "Error: File is empty." << endl;
        return "";
    }

    // Generate a random number between 1 and the number of lines
    srand(static_cast<unsigned int>(time(nullptr)));  // Seed the random number generator
    int randomLineNumber = rand() % numberOfLines + 1;

    // Reset the file position to the beginning
    file.clear();
    file.seekg(0, ios::beg);

    // Read the selected word from the file
    int currentLineNumber = 0;
    string targetWord;
    while (getline(file, line)) {
        currentLineNumber++;
        if (currentLineNumber == randomLineNumber) {
            targetWord = line;
            break;
        }
    }

    // Close the file
    file.close();

    return targetWord;

    // For now only 5 letter words should be allowe
    return "";
}

// Dylan - This function should ask the user how many guesses they would like
// and return that number. It needs to have input validation
int getNumberOfGuesses() {}

// Dylan - This function should ask the user for the length of the word. Be sure
// to use input validation and if the user enters an invalid number meaning if
// they type anything other than 5, they will be prompted again
int getLengthOfWord() {
    // For now only 5 letter words should be allowed
    // If the user enters any length other than 5 it should not work
}

void game(int numberOfGuesses, string word) {}
