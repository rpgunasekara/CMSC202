//Title: proj2.cpp
//Author: Jeremy Dixon
//Date: 2/23/2024
//Description: This is main for project 2.
#include "Pokemon.h" //Pokemon class
#include "Game.h" //Game class
#include <iostream>
#include <ctime>
#include <cstdlib>
#include <string>
#include <fstream>
using namespace std;

//Inside the parameters for main, we can pass arguments
//argc is the count of arguments
//argv are the parameters themselves
int main(int argc, char* argv[]) {
  srand(time(NULL)); //Seeds the random number generator
  cout << "Welcome to the UMBC Pokemon" << endl;
  while (argc < 2) { //Checks to make sure the user passes a file to load
    cout << "You are missing a data file." << endl;
    cout << "Expected usage ./proj2 proj2_pokeDex.txt" << endl;
    cout << "File 1 should be a file with one or more Pokemon" << endl;
    return 0;
  }
  Game myGame(argv[1]); //Creates a new game passing the filename
  myGame.Start(); //Starts game
  return 0;
}
