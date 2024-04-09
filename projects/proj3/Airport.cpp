/*
 * File: Airport.cpp
 * Project: CMSC 202 Project 3, Spring 2024
 * Author: Ravindu Gunasekara
 * Date: 03/29/2024
 * Section: 20/22
 * E-mail: rgunase1@umbc.edu
 * Desc: This file contains the function
 *       definitions for the Airport
 *       class.
 */

#include "Airport.h"
using namespace std;

// Airport
// Default constructor
Airport::Airport() {
  m_code = "NEW";
  m_name = "NEW NAME";
  m_city = "NEW CITY";
  m_country = "NEW COUNTRY";
  m_north = 0;
  m_west = 0;
  m_next = nullptr;
}

// Airport
// Overloaded constructor
Airport::Airport(string code, string name, string city, string country, double north, double west) {
  m_code = code;
  m_name = name;
  m_city = city;
  m_country = country;
  m_north = north;
  m_west = west;
  m_next = nullptr;
}

// ~Airport
// Deconstructor
Airport::~Airport() {

}

// GetCode
// Returns the airport's code
string Airport::GetCode() {
  return m_code;
}

// GetName
// Returns the airport's name
string Airport::GetName() {
  return m_name;
}

// GetNext
// Returns the airport's connection
Airport* Airport::GetNext() {
  return m_next;
}

// GetNorth
// Returns the airport's north coordinate
double Airport::GetNorth() {
  return m_north;
}

// GetWest
// Returns the airport's west coordinate
double Airport::GetWest() {
  return m_west;
}

// GetCity
// Returns the airport's city
string Airport::GetCity() {
  return m_city;
}

// GetCountry
// Returns the airport's country
string Airport::GetCountry() {
  return m_country;
}

// SetNext
// Given the connection, sets the airport's new connection
void Airport::SetNext(Airport *nextAirport) {
  m_next = nextAirport;
}
