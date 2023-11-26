/**
 * Dylan Maldonado,
 * Luke Davis,
 * Justin Schwerdtfeger
 *
 * Course: COSC 1436.001 Programming Fundamentals
 * Group Project
 * Due Date: 2023-11-26
 * Instructor: Korinne Caruso
 *
 * Purpose: Describe what the program, as a whole, does (e.g.,
 * calculates a payroll). This need not be long. Just a
 * couple of sentences will do. Many students
 * mistakenly describe the purpose of the assignment
 * here (e.g., to learn how to use functions) rather than
 * the purpose of the program.
 *
 * Input: This section is very important to anyone (including
 * yourself) who may want to use this program. There are
 * usually four things that are useful to know about a
 * programs input:
 *
 * 1. What is the input? What information does the
 * program expect to receive in order to run correctly?
 *
 * 2. What is the format of the input? If the input is coming
 * from a file, the data is probably laid out in specific
 * columns.
 *
 * 3. From where does the program expect to receive the
 * input? Does the program read from the keyboard
 * (cin) or a file? If it reads from a file, where and what
 * is the filename?
 *
 * 4. Sometimes there are program restrictions in terms of
 * the input that you may want to mention. For example,
 * the maximum number of students that can be read is
 * 50 or definitions can be no longer than 250
 * characters.
 *
 * Output: This section is similar to the input section, but of
 * course, describes what is output instead. It should
 * include information about the contents of the output,
 * general format (e.g., a table), where the output is sent
 * (cout or file), the name(s) of any file(s) created, and
 * any other relevant information.
 */

#include <cctype>
#include <cstdlib>
#include <ctime>
#include <fstream>
#include <iostream>
#include <limits>
#include <string>
#include <vector>
using namespace std;

/**
 * @brief Display intro to user
 */
void intro();

/**
 * @brief Get answer using text file. Open text file corresponding to word
 * length. Pick random word in text file.
 *
 * @param lengthOfWord The word length to open the correct text file.
 *
 * @return The randomly selected word in the text file
 */
string getAnswer(int lenghtOfWord);

/**
 * @brief Get the number of guesses from the user by printing out a prompt, and
 * using cin.
 *
 * @return The number of guesses from the user
 */

int getNumberOfGuesses();

/**
 * @brief Get the length of the words for the game from the user by printing out
 * a prompt, and using cin.
 *
 * @return The length of the guesses and answer from the user
 */
int getLengthOfWord();

/**
 * @brief Get the username for saving data from the user by printing out a
 * prompt, and using cin. Give user option to not save data.
 *
 * @return The username from the user. Return empty string if none was selected
 */
string getUsername();

/**
 * @brief Validate word using the following checks:
 *  1. The length of word must match numberOfLetters.
 *  2. The word must contain only alphabetical characters.
 *  3. The word must not have already been guessed before.
 *  4. The word must be a part of the word list.
 *
 * @param word The word to Validate.
 *
 * @param guessedWords The guessed words list to checks.
 *
 * @param numberOfLetters The numberofLetters that the word must have.
 *
 * @return true if all checks pass, false if any check fails.
 */
bool isValidInput(const string &word, const vector<string> &guessedWords,
                  int numberOfLetters);

/**
 * @brief Run Game. Displays keyboard and info about guesses using 'O' for
 * correct, '-' for in word, and 'X' for not in word. Clears screen between
 * valid guesses.
 *
 * @param username The username to use for save data
 *
 * @param answer The correct answer to be used for the game
 *
 * @param numberOfGuesses The number of guesses allowed until word is revealed.
 */
void game(const string &username, const string &answer, int numberOfGuesses);

/**
 * @brief Print playerdata to file matching players username.
 *
 * @param username The username corresponding to the output text file for the
 * user.
 *
 * @param guessedWords The guessed words to be included in the text file
 *
 * @param guessedWordResults The Results ('O', '-', or 'X'), for each word to be
 * included in text file.
 */
void printToFile(const string &username, const vector<string> &guessedWords,
                 const vector<string> &guessedWordResults);

/**
 * @brief Get a value from the user using cin. Works with generic type T.
 * Handles invalid data.
 *
 * @param prompt The prompt that the user will see. You may want to add a new
 * line character
 *
 * @return The value from the user
 */
template <typename T> T input(const char *prompt);

/**
 * @brief Convert a string to lowercase
 *
 * @param input The input to be converted
 *
 * @return The input in lowercase form
 */
string toLower(const string &input);

/**
 * @brief Check if a string is alphabetical
 *
 * @param input The input to be converted
 *
 * @return true if input is alphabetical; false if not
 */
bool isAlpha(const string &input);

/**
 * @brief Clear screen using "cls" on Windows or "clear" on unix
 */
void clearScreen();

int main() {
    intro();
    int numberOfGuesses = getNumberOfGuesses();
    int lengthOfWord = getLengthOfWord();
    string username = getUsername();
    string answer = getAnswer(lengthOfWord);
    game(username, answer, numberOfGuesses);
    return 0;
}

void intro() {
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
    cout << "If your text turns yellow, your letter is in the word, but it "
            "is "
            "not in the right place"
         << endl;
    cout << "If your text turns green, your letter is in the word and in "
            "the "
            "right place"
         << endl;
    cout << "Have fun!" << endl;
}

string getAnswer(int lengthOfWord) {

    // Create file name based on length of word so that we open the file
    // corresponding to the lenght of the word.
    string filename = "word-list-" + to_string(lengthOfWord) + "-letter.txt";
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

    int randomLineNumber =
        (rand() % numberOfLines) + 1; // Add one becuase there is no line 0

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

    // Loops forever
    while (true) {
        // use input function with int for input validation
        guesses = input<int>("How many guesses would you like? ");

        // If input is out of range, repeat
        if (guesses < 1 || guesses > 100) {
            cout << "Please enter a number 1-100" << endl;
            continue;
        }

        // otherise, break out of loop
        break;
    }
    return guesses;
}

int getLengthOfWord() {
    int wordLength;

    // Loops forever
    while (true) {

        // use input function with int for input validation
        wordLength = input<int>("How long would you like the word to be "
                                "(between 2 and 6 letters)? ");

        // If input is out of range, repeat
        if (wordLength < 2 || wordLength > 6) {
            cout << "Please enter a number between 2-6" << endl;
            continue;
        }
        // otherise, break out of loop
        break;
    }
    return wordLength;
}

string getUsername() {

    // Loops forever
    while (true) {
        cout << "Would you like to save data? " << endl;
        cout << "(Y)es" << endl;
        cout << "(N)o" << endl;

        // Use input function with char for input validation
        char userInput = input<char>("Please enter a letter: ");

        // convert user input to lowercase
        userInput = tolower(userInput);

        switch (userInput) {
        case 'y':
            break; // break out of switch
        case 'n':
            return ""; // return empty string
        default:
            continue; // Loop again
        }
        break; // break out of loop to get the username
    }

    cout << "This program will need a username to create the save file. "
         << endl;

    string username = input<string>(
        "Please enter the username you would like to use for saving: ");

    return username;
}

// This function should return false if the input is invalid.
// Return true at the end if all checks pass.
bool isValidInput(const string &input, const vector<string> &guessedWords,
                  int numberOfLetters) {

    // Check to make sure user's input is the right number of letters
    if (input.length() != numberOfLetters) {
        cout << "Input was not the right number of letters. " << endl;
        return false;
    }

    // Check to make sure userinput is alphabetical
    if (!isAlpha(input)) {
        cout << "Your input must use alphabetical characters only. " << endl;
        return false;
    }

    // Check if user has already guessed the word
    for (string word : guessedWords) {
        if (input == word) {
            cout << "You have already guessed that word. " << endl;
            return false;
        }
    }

    string filename = "word-list-" + to_string(numberOfLetters) + "-letter.txt";
    ifstream file(filename);

    // Check if the file is opened successfully
    if (!file.is_open()) {
        cerr << "Error opening file: " << filename << endl;
        return false;
    }

    string line;

    // Check through each line in the file
    while (getline(file, line)) {

        // If input matches the line, return true.
        if (input == line) {
            file.close();
            return true;
        }
    }

    // This only happens if no lines in the file returned true
    cerr << "Word not found on list" << endl;
    file.close();
    return false;
}

void game(const string &username, const string &answer, int numberOfGuesses) {
    // Create starting configurations for vectors and the keyboard array
    vector<string> guessedWords;
    vector<string> guessedWordResults;
    int KeyboardRows = 6;
    string keyboard[] = {
        "q w e r t y u i o p", "                   ", " a s d f g h j k l ",
        "                   ", "  z x c v b n m    ", "                   ",
    };

    while (numberOfGuesses > 0) {

        // Clear screen at start of each guess
        clearScreen();

        // Print out previously guessed words lists on screen
        for (int i = 0; i < guessedWords.size(); i++) {
            cout << guessedWords[i] << endl;
            cout << guessedWordResults[i] << endl;
            cout << endl;
        }

        // Print out the virtual keyboard
        for (string row : keyboard) {
            cout << row << endl;
        }

        // Print out the remainig guesses
        cout << "Remaining guesses: " << numberOfGuesses << endl;

        // Get guess from user
        string guess;
        while (true) {
            guess = input<string>("Please enter your guess: ");

            // Convert guess to lowercase
            guess = toLower(guess);

            // Check all 4 conditions using isValidInput function.
            // If the checks fail, try again.
            if (!isValidInput(guess, guessedWords, answer.length())) {
                continue;
            }

            // Otherwise break
            break;
        }

        // Add user's guess to guessed words vector
        guessedWords.push_back(guess);

        string wordResult = "";

        // Provide feedback on the guessed word
        for (int i = 0; i < guess.length(); i++) {
            char charResult;

            if (guess[i] == answer[i]) {
                charResult = 'O'; // Right letter in the right spot

            } else if (answer.find(guess[i]) != string::npos) {
                charResult = '-'; // Right letter in the wrong spot

            } else {
                charResult = 'X'; // Wrong letter
            }
            wordResult += charResult;

            // Iterate through each row in keyboard
            for (int row = 0; row < KeyboardRows; row++) {

                // Move to next row if we do not find charcter on this row
                if (keyboard[row].find(guess[i]) == string::npos) {
                    continue;
                }

                // Otherwise pos = the poisition of the guessed letter
                int pos = keyboard[row].find(guess[i]);

                // Skip letter is already correct.
                if (keyboard[row + 1][pos] == 'O') {
                    continue;
                }

                // Add the result to the row below the letter
                // Thats why there is row + 1
                keyboard[row + 1][pos] = charResult;
            }
        }

        // Add result of word ('O', '-', 'X'), to guessedWordResults vector
        guessedWordResults.push_back(wordResult);

        // Check if the guessed word is correct
        if (guess == answer) {
            cout << "Congratulations! You guessed the word: " << answer << endl;
            break;
        }

        // Subtract one attempt
        numberOfGuesses -= 1;
    }

    // After our attempts are done, put correct answer into vectors for storing
    // in file
    guessedWords.push_back(answer);
    guessedWordResults.push_back("The correct answer");

    if (numberOfGuesses == 0) {
        cout << "Sorry, you've run out of guesses. The word was: " << answer
             << endl;
    }

    // Run print to file with the necessary data
    printToFile(username, guessedWords, guessedWordResults);
}

void printToFile(const string &username, const vector<string> &guessedWords,
                 const vector<string> &guessedWordResults) {

    // Don't print if username is an empty string
    if (username == "") {
        return;
    }

    // Create filename based on username
    string fileName = username + ".txt";

    // Create read & write file in append mode, so it writes from the end of the
    // file
    fstream file;
    file.open(fileName, fstream::in | fstream::out | fstream::app);

    string contents;

    // If file is empty, crate initial contents
    if (!(file >> contents)) {

        // close file and reopen file in trunc mode so it can create a new file
        file.close();
        file.open(fileName, fstream::in | fstream::out | fstream::trunc);

        file << "               __" << endl;
        file << "              / _)" << endl;
        file << "     _.----._/ /" << endl;
        file << "    /         /" << endl;
        file << " __/ (  | (  |" << endl;
        file << "/__.-'|_|--|_|" << endl;
        file << endl;
        file << "Word Dino results for " << username << endl;
        file << endl;
    }

    file << endl;

    time_t currentTime = time(nullptr); // get current time

    // Print out current time into file
    file << ctime(&currentTime) << endl;

    // Print out all guessed words and results
    for (int i = 0; i < guessedWords.size(); i++) {
        file << guessedWords[i] << endl;
        file << guessedWordResults[i] << endl;
        file << endl;
    }

    cout << "Data saved in " << fileName << endl;
    file.close();
}

template <typename T> T input(const char *prompt) {
    T input;

    // Loop while input is invalid
    while (true) {
        cout << prompt;
        cin >> input;
        cin.ignore(numeric_limits<streamsize>::max(), '\n');

        if (cin.fail()) {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cerr << "Invalid Input" << endl;
            continue;
        }
        break;
    }
    return input;
}

string toLower(const string &input) {
    // For each character in input, convert to lowercase and add to output
    // string
    string output = "";
    for (char character : input) {
        output += tolower(character);
    }
    return output;
}

bool isAlpha(const string &input) {
    // Check each character to see if they are alphabetical. If any character is
    // not, return false. Othewise, return true
    for (char character : input) {
        if (!isalpha(character)) {
            return false;
        }
    }
    return true;
}

// Check if compiler is uing unix
#ifdef __unix__
// use clear for clearing screen
void clearScreen() { system("clear"); }
#endif

// Check if compiler is uing windows
#ifdef _WIN32
// use cls for clearing screen
void clearScreen() { system("cls"); }
#endif
