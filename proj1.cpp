/*
* proj1.cpp
* Milan Parmar
* 2/11/21
* Section 52
* This lab is a UMBC Word guess, hangman copy.
*/

#include <iostream>
#include <ctime>
#include <fstream>
#include <iomanip>
#include <cmath>
#include <cstdlib>
#include <string>
#include <cstring>
using namespace std;

void wordBank();
void play_game();
int file_lines();
void guess_word(string word, int size);
bool validInput(char input);

const int TOTAL_WORDS = file_lines(); // Constant variable for the amount of total words in words.txt.


int main() { // Used to start the game

    wordBank();
    
    return 0;
}

void play_game() { // Used to start and repeat the whole game.
    char playAgain;
    bool valid;

    cout << "Another game? y/n ";
    cin >> playAgain;
    
    valid = validInput(playAgain);

    while (valid == false) {
        cout << "Another game? y/n ";
        cin >> playAgain;
        valid = validInput(playAgain);   
    }
    if (playAgain == 'y') {
        wordBank();
    }    
    else {
        cout << "Thank you for playing UMBC Word Guess!" << endl;
    }
}

bool validInput(char input) { // Used to validate inputs.
    /* char input: Inputs the user's guess character
        returns boolean statement depending on validity.
    */
    char alphabet[26] = {'a','b','c','d','e','f','g','h','i','j','k','l','m','n','o','p','q','r','s','t','u','v','w','x','y','z'};
    bool valid = false;

    for(int i = 0; i < 26; i++) {
        if (input == alphabet[i]) {
            valid = true;
        }
    }
    return valid;
}

void guess_word(string word) { // Mother function of the game. Used to do all the guess work.
    /*  string word: Gets the random word selected from word bank function. */

    string strGuess;
    string guessArray[100] = {};
    string tempArray[100] = {};
    bool valid;
    char guess;    
    int size = word.size();
    int remainder = size;
    int wrongCount = 0;
    bool letterInWord = false;

    cout << "Ok. I am thinking of a word with " << size << " letters." << endl;
    cout << remainder << " letters remain." << endl;

    for(int i = 0; i < size + 1; i++) {
        guessArray[i] = "_ ";
        cout << guessArray[i];
    }

    cout << endl;
    cout << "What letter would you like to guess?" << endl;
    cin >> guess;
    valid = validInput(guess);
    strGuess = guess;
    tempArray[0] = strGuess;

    while (valid == false) {
        cout << "Invalid input, try again: ";

        cin.clear();
        cin.ignore(256, '\n');
        cin >> guess;
        valid = validInput(guess);
        strGuess = guess;
        tempArray[0] = strGuess;        
    }

    while (wrongCount < 5 && remainder > 0) {
        letterInWord = false;
        for(int g = 0; g < size; g++) {
            if (guess == word[g]) {
                if ((tempArray[0] + " ") == guessArray[g]) {
                    cout << "You've already guessed this word." << endl;
                    letterInWord = false;   
                }
                else {
                    guessArray[g] = strGuess + " ";
                    remainder--;
                    letterInWord = true;
                    cout << remainder << " letters remain." << endl;
                }
            }
        }
        if (letterInWord == false) {
            wrongCount++;
            cout << "There are no " << guess << " in the puzzle." << endl;
            cout << "You have " << 5 - wrongCount << " bad guesses left." << endl;
            cout << remainder << " letter remain." << endl;

            for(int i = 0; i < size; i++) {
                cout << guessArray[i];
            } 
            cout << endl;         
            if (wrongCount < 5) {
                cout << "What letter would you like to guess?" << endl;
                cin >> guess;
                valid = validInput(guess);
                strGuess = guess;
                tempArray[0] = strGuess;
                
                while (valid == false) {
                    cout << "Invalid input, try again: ";

                    cin.clear();
                    cin.ignore(256, '\n');
                    cin >> guess;
                    valid = validInput(guess);
                    strGuess = guess;
                    tempArray[0] = strGuess;        
                }
            }            
        }
        if (remainder > 0 && letterInWord == true) {
            for(int i = 0; i < size; i++) {
                cout << guessArray[i];
            }
            cout << endl;         

            cout << "What letter would you like to guess?" << endl;
            cin >> guess;
            valid = validInput(guess);
            strGuess = guess;
            tempArray[0] = strGuess;
            
            while (valid == false) {
                cout << "Invalid input, try again: ";

                cin.clear();
                cin.ignore(256, '\n');
                cin >> guess;
                valid = validInput(guess);
                strGuess = guess;
                tempArray[0] = strGuess;        
            }
        }        
        for(int i = 0; i < size; i++) {
            cout << guessArray[i];
        }
        cout << endl;
    }
    if (remainder == 0) {
        cout << "Congrats you won!" << endl;
        play_game();
    }
    if (wrongCount == 5) {
        cout << "Sorry, you lost" << endl;
        cout << "The correct word was: " << word << endl;
        play_game();
    }
}

void wordBank() { // Determines the random word in the words.txt file to use.
    string words[10000] = {};
    int index = 0;
    string word = "";

    srand(time(NULL));
    int randomNum = rand() % TOTAL_WORDS;

    ifstream myfile("words.txt");
    if (myfile.is_open()) {
        while(myfile >> words[index]) {
            index++;    
        }
    }    
    else {
        cout << "Unable to open file." << endl; //Only if file doesn't exist or open correctly
    }
    myfile.close();

    word = words[randomNum - 1];

    guess_word(word);
}

int file_lines() { // Determines how many lines are in the read file
    string dummyArray[10000] = {};
    int numOfLines = 0;
    int index = 0;

    cout << "Welcome to UMBC Word Guess" << endl;

    ifstream myfile("words.txt");
    if (myfile.is_open()) {
        cout << "Your file was imported!" << endl;
        while(myfile >> dummyArray[index]) {
            numOfLines += 1;
            index++;    
        }
        cout << numOfLines << " words imported." << endl;
    }    
    else {
        cout << "Unable to open file" << endl; //Only if file doesn't exist or open correctly
    }
    myfile.close();

    return numOfLines;
}