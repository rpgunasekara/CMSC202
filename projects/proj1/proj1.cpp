/*
** File: proj1.cpp
** Project: CMSC 202 Project 1, Spring 2024
** Author: Ravindu Gunasekara
** Date: 02/23/2024
** Section: 20/22
** E-mail: rgunase1@umbc.edu
**
** This file contains the entire program for Project 1.
** This program reads the file specified by the variable
** DATAFILE, creates arrays, generates a random index,
** and uses said index to pick a category and a puzzle
** from the arrays. Then begins a game akin to Wheel of
** Fortune, and has the user input various letters, till
** the puzzle has been solved.
*/

#include <iostream>
#include <ctime>
#include <string>
#include <fstream>
#include <iomanip>
#include <cmath>
#include <cstdlib>

using namespace std;

// Constants
const string DATAFILE = "proj1_data.txt"; // file with categories and puzzles
const int DATALINES = 48; // number of lines in DATAFILE
const int ASCII = 256; // number of ASCII characters

void loadFile(string categories[], string puzzles[]);
int getAnswer(int index);
string inPuzzle(string puzzle, char guess, string guesses);
char getInput(int ascii_table[]);
bool isCompleted(string guesses);
void printPuzzle(string puzzle, string guesses);


int main () {
  string categories[DATALINES / 2];
  string puzzles[DATALINES / 2];
  int ascii_table[ASCII] = {0};
  int index = 0;
  bool play_again = true;

  // will allow player to try other puzzles
  // if they choose to
  while (play_again) {
    // begin game and load file
    cout << "Welcome to UMBC Fortune Wheel!" << endl;
    loadFile(categories, puzzles);
    cout << "24 puzzles loaded." << endl;

    // seed and generate a random category/puzzle
    srand(time(NULL));
    index = getAnswer(index);
    string category = categories[index];
    string puzzle = puzzles[index];

    // unsolved version of puzzle, used for printing
    // and winning the game
    string guesses;
    for (char i : puzzle) {
      if (i == ' ') {
        guesses += ' ';
      }
      else {
        guesses += '_';
      }
    }

    cout << "Category is: " << category << endl;
    printPuzzle(puzzle, guesses);

    // until win, asks for a guess, marks that
    // the letter has been guessed, updates values
    // and prints puzzle
    while (isCompleted(guesses) == false) {
      char guess = getInput(ascii_table);
      ascii_table[int(guess)] = 1;
      guesses = inPuzzle(puzzle, guess, guesses);
      printPuzzle(puzzle, guesses);
    }

    cout << "You won!" << endl;

    char replay;
    cout << "Do you want to play again? (y/n): ";
    cin >> replay;

    if (replay != 'y' && replay != 'Y') {
      play_again = false;
    }

    cout << endl;
  }

  return 0;
}


// loadFile: takes a file and splits the lines between two arrays
void loadFile (string categories[], string puzzles[]) {
  ifstream file(DATAFILE);

  for (int i = 0; i < DATALINES / 2; i++) {
    getline(file, categories[i]);
    getline(file, puzzles[i]);
  }

  file.close();
}


// getAnswer: generates a random number (0 - 23) and returns the value
int getAnswer (int index) {
  index = rand() % (DATALINES / 2);

  return index;
}


// inPuzzle: updates guesses and prints if guess is in puzzle, and how many
string inPuzzle (string puzzle, char guess, string guesses) {
  int count = 0;

  // using puzzle, checks if guess is right, then updates guesses if so
  for (int i = 0; i < int(puzzle.length()); i++) {
    if (puzzle[i] == guess) {
      guesses[i] = guess;
      count++;
    }
  }

  if (count > 0) {
    cout << count << " " << guess << " found in the puzzle." << endl;
  }
  else {
    cout << "No " << guess << " found in the puzzle." << endl;
  }

  return guesses;
}


// getInput: asks for an input, looping until it's valid
char getInput (int ascii_table[ASCII]) {
  char guess;

  // validates input by determining if it's within the range
  // of ASCII characters that we want
  do {
    cout << "What letter would you like to try?" << endl;
    cin >> guess;

    if (guess >= 'a' && guess <= 'z') {
      cout << "Enter an uppercase letter only." << endl;
    }

    if (ascii_table[int(guess)] == 1) {
      cout << guess << " already guessed." << endl;
    }
  } while (guess < 'A' || guess > 'Z');

  return guess;
}


// isCompleted: checks if guesses has any underscores left
// to determine whether to keep playing or not
bool isCompleted (string guesses) {
  for (char i : guesses) {
    if (i == '_') {
      return false;
    }
  }

  return true;
}


// printPuzzle: prints the current state of guesses
void printPuzzle (string puzzle, string guesses) {
  for (int i = 0; i < int(puzzle.length()); i++) {
    if (puzzle[i] == ' ') {
      cout << " ";
    }
    else {
      char current_guess = guesses[i];
      if (current_guess == '_') {
        cout << "_";
      }
      else {
        cout << current_guess;
      }
    }
  }
  cout << endl;
}
