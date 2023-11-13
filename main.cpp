#include <cstdlib>
#include <ctime>
#include <fstream>
#include <iostream>
#include <string>
#include <limits>
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
    string filename = "";
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
    srand(static_cast<unsigned int>(
        time(nullptr))); // Seed the random number generator
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

int getNumberOfGuesses() {
    int guesses;
    while (true) {
        cout << "How many guesses would you like?" << endl;
        cin >> guesses;
        cin.ignore(numeric_limits<streamsize>::max(), '\n');

        if (cin.fail()) {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "Invalid input, try again." << endl;
            continue;
        }
        if (guesses < 1 || guesses > 100) {
            cout << "Please enter a number 1-100" << endl;
            continue;
        }
        break;
    }
    return guesses;
}


int getLengthOfWord() {
    int WordLenght;
    while (true) {
            cout << "How long would you like the word to be? (Between 2 and 6)" << endl;
            cin >> WordLenght;
            cin.ignore(numeric_limits<streamsize>::max(), '\n');

        if (cin.fail()) {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "Invalid input, try again." << endl;
            continue;
        }
        if (WordLenght < 2 || WordLenght > 6) {
            cout << "Please enter a number between 2-6" << endl;
            continue;
        }
       break;
    }
return WordLenght;
}

void game(int numberOfGuesses, string word) {}
