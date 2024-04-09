/************************************************************
** File: Game.cpp
** Project: CMSC 202 Project 2, Spring 2024
** Author: Ravindu Gunasekara
** Date: 03/09/2024
** Section: 20/22
** E-mail: rgunase1@umbc.edu
**
** This file contains the Game class function definitions.
************************************************************/
#include "Game.h"

//Constructor

// Game
// Sets m_filename based on string passed.
Game::Game(string filename) {
  m_filename = filename;
}

//Game Functions

// LoadFile
// Opens file and reads in each Pokemon into m_pokeDex.
void Game::LoadFile() {
  ifstream file(m_filename);

  // Creates a Pokemon construct for all
  // Pokemon in the file.
  for(int i = 0; i < TOTAL_POKEMON; i++) {
    int num;
    string name;
    int cp;
    int rarity;

    file >> num >> name >> cp >> rarity;
    m_pokeDex[i] = Pokemon(num, name, cp, rarity);
  }

  file.close();
}

// DisplayPokeDex
// Display all Pokemon in m_pokeDex.
void Game::DisplayPokeDex() {
  cout << "Kanto Pokedex: " << endl;
  cout << setw(NUM_WIDTH) << "Number" << setw(NAME_WIDTH) << "Name" << setw(NUM_WIDTH) << "CP" << " " << "Rarity" << endl;
  cout << "-------------------------------" << endl;

  for(int i = 0; i < TOTAL_POKEMON; i++) {
    cout << setw(NUM_WIDTH) << m_pokeDex[i].GetNum() << setw(NAME_WIDTH) << m_pokeDex[i].GetName() << setw(NUM_WIDTH) << m_pokeDex[i].GetCP() << setw(NUM_WIDTH) << m_pokeDex[i].GetRarity() << endl;
  }
}

// MainMenu
// Displays the main menu.
void Game::MainMenu() {
  int choice = 0;

  cout << "Safari Zone!" << endl;
  cout << "Currently Available: Kanto Region Pokemon" << endl;

  // Nested loop so it loops until choice
  // is valid and == 6.
  while(choice != 6) {
    choice = 0;

    while(choice < 1 || choice > 6) {
      cout << "\nWhat would you like to do?" << endl;
      cout << "1. Display Complete PokeDex" << endl;
      cout << "2. Display Your Team" << endl;
      cout << "3. Search for a New Pokemon" << endl;
      cout << "4. Battle Your Pokemon" << endl;
      cout << "5. Train Your Pokemon" << endl;
      cout << "6. Exit" << endl;
      cin >> choice;
      cout << endl;
    }

    switch(choice) {
    case 1:
      DisplayPokeDex();
      break;
    case 2:
      DisplayTeam();
      break;
    case 3:
      CatchPokemon();
      break;
    case 4:
      BattlePokemon();
      break;
    case 5:
      TrainPokemon();
      break;
    case 6:
      break;
    default:
      cout << "ERROR: Invalid Input" << endl;
      break;
    }
  }
}

// CatchPokemon
// Main function for catching pokemon. Does the following:
// Calls CatchMenu and stores rarity chosen.
// Randomly chooses a number between 0 - 99.
// If random number is less than rarity, calls FoundPokemon.
//   Call AddPokemon if new Pokemon is caught.
// If random number is greater than rarity, indicates none found.
void Game::CatchPokemon() {
  int rarity = CatchMenu();
  int randNum = rand() % 100;

  if(randNum < rarity) {
    Pokemon newPokemon = FoundPokemon(rarity);
    AddPokemon(newPokemon);
  }
  else {
    cout << "You thought you sensed something, but nothing happened." << endl;
  }
}

// CatchMenu
// User chooses which rarity of Pokemon to try and catch.
int Game::CatchMenu() {
  int choice = 0;

  while(choice < 1 || choice > 3) {
    cout << "What rarity of Pokemon would you like to catch?" << endl;
    cout << "1. Common (High Probability)" << endl;
    cout << "2. Uncommon (Normal Probability)" << endl;
    cout << "3. Ultra Rare (Extremely Low Probability)" << endl;
    cin >> choice;
    cout << endl;
  }

  switch(choice) {
  case 1:
    return COMMON;
  case 2:
    return UNCOMMON;
  case 3:
    return ULTRA;
  default:
    cout << "ERROR: Invalid Input" << endl;
    return COMMON;
  }
}

// FoundPokemon
// Based on rarity passed in, randomly chooses one Pokemon
// from m_pokeDex, updates the CP, and returns the new
// Pokemon construct.
Pokemon Game::FoundPokemon(int rarity) {
  int randNum;

  // Convert the rarity % into
  // the rarity valid for a Pokemon
  // construct.
  switch(rarity) {
  case COMMON:
    rarity = 1;
    break;
  case UNCOMMON:
    rarity = 2;
    break;
  case ULTRA:
    rarity = 3;
    break;
  default:
    cout << "ERROR: Invalid Input" << endl;
    break;
  }

  do {
    randNum = rand() % TOTAL_POKEMON;
  } while(m_pokeDex[randNum].GetRarity() != rarity);

  cout << "You start searching your surroundings.\n.\n..\n..." << endl;
  cout << "You found a wild " << m_pokeDex[randNum].GetName() << "!" << endl;

  // Make sure the new Pokemon's CP is not max.
  int newCP = m_pokeDex[randNum].GetCP() * (rand() % (MAX_FIND + 1 - MIN_FIND) + MIN_FIND) / 100;
  Pokemon newPokemon = m_pokeDex[randNum];
  newPokemon.SetCP(newCP);

  return newPokemon;
}

// Setter
// AddPokemon
// Figures out where to insert newly found Pokemon.
// If m_team is full, inserts into first slot with lower CP.
// If m_team is full, and new Pokemon has lower CP, does not insert.
//   Tells user if not inserted.
// If m_team has opening, inserts into first open slot.
void Game::AddPokemon(Pokemon newPokemon) {
  if(TeamSize() == NUM_TEAM) {
    int minCP = m_team[0].GetCP();
    int minIndex = 0;
    bool minFound = false;

    // Searches for the team member with the lowest CP.
    for(int i = 0; i < NUM_TEAM; i++) {
      if(minCP > m_team[i].GetCP() && minFound == false) {
        minCP = m_team[i].GetCP();
        minIndex = i;
        minFound = true;
      }
    }

    if(newPokemon.GetCP() > minCP) {
      cout << newPokemon.GetName() << " added to your team! Goodbye " << m_team[minIndex].GetName() << "!" << endl;
      m_team[minIndex] = newPokemon;
    }
    else {
      cout << "Your team is full, " << newPokemon.GetName() << " cannot be added..." << endl;
    }
  }
  else {
    bool pokemonAdded = false;

    // Adds new Pokemon into the first empty slot.
    for(int i = 0; i < NUM_TEAM; i++) {
      if(m_team[i].GetNum() == 0 && pokemonAdded == false) {
        m_team[i] = newPokemon;
        pokemonAdded = true;
        cout << newPokemon.GetName() << " was added to your team!" << endl;
      }
    }
  }
}

// Getter
// TeamSize
// Iterates through m_team to see how many team members exist
// and returns that value.
int Game::TeamSize() {
  int size = 0;

  for(int i = 0; i < NUM_TEAM; i++) {
    if(m_team[i].GetNum() != 0) {
      size++;
    }
  }

  return size;
}

// DisplayTeam
// Iterates through m_team to display information about team.
void Game::DisplayTeam() {
  if(TeamSize() > 0) {
    cout << "Your Team: " << endl;
    cout << "  " << setw(NUM_WIDTH) << "Number" << setw(NAME_WIDTH) << "Name" << setw(NUM_WIDTH) << "CP" << " " << "Rarity" << endl;
    cout << "---------------------------------" << endl;

    for(int i = 0; i < TeamSize(); i++) {
      cout << i + 1 << "." << setw(NUM_WIDTH) << m_team[i].GetNum() << setw(NAME_WIDTH) << m_team[i].GetName() << setw(NUM_WIDTH) << m_team[i].GetCP() << setw(NUM_WIDTH) << m_team[i].GetRarity() << endl;
    }
  }
  else {
    cout << "You have no Pokemon, go out and explore!" << endl;
  }
}

// Getter
// FindPokemon
// Iterates through m_pokeDex to see if passed name
// exists, returns index if found, else -1.
int Game::FindPokemon(string name) {
  for(int i = 0; i < TOTAL_POKEMON; i++) {
    if(m_pokeDex[i].GetName() == name) {
      return i;
    }
  }

  return -1;
}

// TrainPokemon
// If m_team size is 0. If 0, tells user and returns to main menu.
// If m_team size > 0, displays team (DisplayTeam).
//   Asks user to chose one team member.
//   Calls Train on chosen team member and passes corresponding CP
//   value from m_pokeDex (m_pokeDex holds max CP for all).
void Game::TrainPokemon() {
  if(TeamSize() == 0) {
    cout << "You have no Pokemon, go out and explore!" << endl;
  }
  else {
    int choice = 0;

    while(choice < 1 || choice > TeamSize()) {
      cout << "Which of your Pokemon would you like to use?" << endl;
      DisplayTeam();
      cin >> choice;
      cout << endl;
    }

    // If the Pokemon chosen has fainted, return to main menu.
    if(m_team[choice - 1].GetCP() == 0) {
      cout << m_team[choice - 1].GetName() << " is unable to train, find a new Pokemon to replace it with." << endl;
    }
    else {
      int maxCP = m_pokeDex[FindPokemon(m_team[choice - 1].GetName())].GetCP();
      m_team[choice - 1].Train(maxCP);

      cout << "The training begins.\n.\n..\n..." << endl;
      cout << m_team[choice - 1].GetName() << " got a little stronger!\n" << endl;
      cout << setw(NUM_WIDTH) << "Number" << setw(NAME_WIDTH) << "Name" << setw(NUM_WIDTH) << "CP" << " " << "Rarity" << endl;
      cout << "-------------------------------" << endl;
      cout << setw(NUM_WIDTH) << m_team[choice - 1].GetNum() << setw(NAME_WIDTH) << m_team[choice - 1].GetName() << setw(NUM_WIDTH) << m_team[choice - 1].GetCP() << setw(NUM_WIDTH) << m_team[choice - 1].GetRarity() << endl;
    }
  }
}

// BattlePokemon
// If m_team size is 0. If 0, tells user and returns to main menu.
// If m_team size > 0, randomly chooses Pokemon to fight from
// m_pokeDex.
//   Random enemy has a CP of 0 - max CP + 200.
//   Asks which team member to use in battle.
//   Compares CP for random enemy and team member.
//     If team member wins, indicates and returns to main menu.
//     If team member loses, indicates, sets CP to 0, returns to menu.
void Game::BattlePokemon() {
  if(TeamSize() == 0) {
    cout << "You have no Pokemon, go out and explore!" << endl;
  }
  else {
    // Create the enemy Pokemon construct and set its CP.
    Pokemon enemy = m_pokeDex[rand() % TOTAL_POKEMON];
    enemy.SetCP(rand() % (0 - enemy.GetCP()) + 200);

    cout << "A hostile " << enemy.GetName() << " appears!" << endl;
    cout << "The enemy has a CP of " << enemy.GetCP() << ".\n\n";

    int choice = 0;

    while(choice < 1 || choice > TeamSize()) {
      cout << "Which of your Pokemon would you like to use?" << endl;
      DisplayTeam();
      cin >> choice;
      cout << endl;
    }

    // If the Pokemon chosen has fainted, return to main menu.
    if(m_team[choice - 1].GetCP() == 0) {
      cout << m_team[choice - 1].GetName() << " is unable to battle, find a new Pokemon to replace it with." << endl;
    }
    else if(m_team[choice - 1].GetCP() <= enemy.GetCP()) {
      cout << "The battle begins.\n.\n..\n..." << endl;
      m_team[choice - 1].SetCP(0);

      cout << m_team[choice - 1].GetName() << " fainted!" << endl;
      cout << "You panicked and dropped $XXX.XX..." << endl;
    }
    else {
      cout << "The battle begins.\n.\n..\n...\n" << endl;
      cout << "You won the battle!" << endl;
      cout << m_team[choice - 1].GetName() << " celebrates its triumph!" << endl;
    }
  }
}

// Start
// Calls LoadFile then MainMenu.
void Game::Start() {
  LoadFile();
  MainMenu();
}
