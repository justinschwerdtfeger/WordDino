#include <cstdlib>
#include <ctime>
#include <fstream>
#include <iostream>
#include <limits>
#include <sstream>
#include <string>
using namespace std;

void intro();
string getWord(int lenghtOfWord);
int getNumberOfGuesses();
int getLengthOfWord();
bool isValidInput(string word, int numberOfLetters);
void game(int numberOfGuesses, string word);

int main() {
    intro();
    int numberOfGuesses = getNumberOfGuesses();
    int lengthOfWord = getLengthOfWord();
    string word = getWord(lengthOfWord);
    game(numberOfGuesses, word);
    return 0;
}

void intro() {
    // TODO: improve these instructions
    cout << "               __" << endl;
    cout << "              / _)" << endl;
    cout << "     _.----._/ /" << endl;
    cout << "    /         /" << endl;
    cout << " __/ (  | (  |" << endl;
    cout << "/__.-'|_|--|_|" << endl;

    cout << "Hello and welcome to Word Dino!" << endl;
    cout << "Your goal is to guess a word." << endl;
    cout << endl;
    cout << "Here are the rules" << endl;
    cout << "If your text turns yellow, your letter is in the word, but it is "
            "not in the right place"
         << endl;
    cout << "If your text turns green, your letter is in the word and in the "
            "right place"
         << endl;
    cout << "Have fun!" << endl;
}
// This should read the lengthOf word and read the corresponding file (there is
// only 1 so far which is for 5 letter words)
string getWord(int lengthOfWord) {

    string filename =
        (stringstream() << "word-list-" << lengthOfWord << "-letter.txt").str();
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

    // Check if the selected word has the desired length
    if (targetWord.length() == lengthOfWord) {
        return targetWord;
    } else {
        cerr << "Error: Selected word does not have the desired length."
             << endl;
        return "";
    }
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
        cout << "How long would you like the word to be? (Between 2 and 6)"
             << endl;
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

// This function should return false if the input is invalid.
// Return true at the end if all checks pass.
bool isValidInput(string input, int numberOfLetters) { return true; }

void game(int numberOfGuesses, string word) {
    int remainingGuesses = numberOfGuesses;

    while (remainingGuesses > 0) {
        cout << "Remaining guesses: " << remainingGuesses << endl;

        string guess;
        while (true) {
            cout << "Please enter your guess: ";
            cin >> guess;
            if (!isValidInput(guess, word.length())) {
                continue;
            }
            break;
        }

        // Check if the guessed word is correct
        if (guess == word) {
            cout << "Congratulations! You guessed the word: " << word << endl;
            break;
        } else {
            // Provide feedback on the guessed word
            for (size_t i = 0; i < word.length(); ++i) {
                if (guess[i] == word[i]) {
                    cout << "O"; // Right letter in the right spot
                } else if (word.find(guess[i]) != string::npos) {
                    cout << "-"; // Right letter in the wrong spot
                } else {
                    cout << "X"; // Wrong letter
                }
            }

            cout << endl;
            remainingGuesses--;
        }
    }

    if (remainingGuesses == 0) {
        cout << "Sorry, you've run out of guesses. The word was: " << word
             << endl;
    }
}
//     while (true){
//         cout << "Please enter your guess"
//         cin >> word
//         cin.ignore(numeric_limits<streamsize>::max(), '\n');
//
//             if (cin.fail()){
//                 cin.clear();
//                 cin.ignore(numeric_limits<streamsize>::max(), '\n');
//                 cout << "Incorrect input" << endl;
//                 continue;
//             }
//             break
//     }
// return word
