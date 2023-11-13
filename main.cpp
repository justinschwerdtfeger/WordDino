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
    cout << "Hello and welcome to Wordle!" << endl;
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
