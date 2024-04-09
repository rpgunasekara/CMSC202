/************************************************************
** File: Pokemon.cpp
** Project: CMSC 202 Project 2, Spring 2024
** Author: Ravindu Gunasekara
** Date: 03/09/2024
** Section: 20/22
** E-mail: rgunase1@umbc.edu
**
** This file contains the Pokemon class function definitions.
************************************************************/
#include "Pokemon.h"

// Constructors

// Pokemon
// Constructs an empty Pokemon.
Pokemon::Pokemon() {
  m_num = 0;
  m_name = "MissingNo.";
  m_CP = 9999;
  m_rarity = 3;
}

// Pokemon
// Constructs a populated Pokemon.
Pokemon::Pokemon(int num, string name, int cp, int rarity) {
  m_num = num;
  m_name = name;
  m_CP = cp;
  m_rarity = rarity;
}

// Getters

// GetCP
// Returns CP.
int Pokemon::GetCP() {
  return m_CP;
}

// GetRarity
// Returns rarity.
int Pokemon::GetRarity() {
  return m_rarity;
}

// GetName
// Returns name.
string Pokemon::GetName() {
  return m_name;
}

// GetNum
// Returns num.
int Pokemon::GetNum() {
  return m_num;
}

// Setters

// SetRarity
// Updates the rarity (between 1 and 3).
void Pokemon::SetRarity(int newRarity) {
  m_rarity = newRarity;
}

// SetName
// Updates the name.
void Pokemon::SetName(string newName) {
  m_name = newName;
}

// SetCP
// Updates the combat power (CP).
void Pokemon::SetCP(int newCP) {
  m_CP = newCP;
}

// Train
// Increases the CP by TRAIN_VALUE up to maxCP.
void Pokemon::Train(int maxCP) {
  m_CP = (m_CP + TRAIN_VALUE <= maxCP) ? m_CP + TRAIN_VALUE : maxCP;
}
