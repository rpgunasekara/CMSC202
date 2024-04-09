/*
 * Name: Route.cpp
 * Project: CMSC 202 Project 3, Spring 2024
 * Author: Ravindu Gunasekara
 * Date: 03/29/2024
 * Section: 20/22
 * E-mail: rgunase1@umbc.edu
 * Desc: This file contains the function
 *       definitions for the Route class.
 */

#include "Route.h"
using namespace std;

// Route
// Default constructor
Route::Route() {
  m_name = "Test";
  m_head = nullptr;
  m_tail = nullptr;
  m_size = 0;
}

// SetName
// Given the name, sets the airport's new name
void Route::SetName(string name) {
  m_name = name;
}

// ~Route
// Deconstructor
Route::~Route() {
  // Iterates through and deletes each object
  while(m_head != nullptr) {
    Airport *temp = m_head;
    m_head = m_head->GetNext();
    delete temp;
  }

  m_tail = nullptr;
  m_size = 0;
}

// InsertEnd
// Given data, creates and adds a new airport to the linked list
void Route::InsertEnd(string code, string name, string city, string country, double north, double west) {
  Airport *newAirport = new Airport(code, name, city, country, north, west);

  // Creates the list if it hasn't been made
  if(m_head == nullptr) {
    m_head = newAirport;
    m_tail = newAirport;
  }
  else {
    m_tail->SetNext(newAirport);
    m_tail = newAirport;
  }

  m_size++;
}

// RemoveAirport
// Given an index, iterates through and deletes
// the specified airport
void Route::RemoveAirport(int index) {
  Airport *prev = nullptr;
  Airport *curr = m_head;
  int currIndex = 0;

  if(index >= m_size || m_size <= 2 || index < 0) {
    cout << "Unable to remove airport." << endl;
    return;
  }

  // Traverses the linked list
  while(curr != nullptr && currIndex != index) {
    prev = curr;
    curr = curr->GetNext();
    currIndex++;
  }

  // Removes the airport and adjusts the list
  if(prev == nullptr) {
    m_head = curr->GetNext();
  }
  else {
    prev->SetNext(curr->GetNext());

    if(prev->GetNext() == nullptr) {
      m_tail = prev;
    }
  }

  delete curr;
  m_size--;
}

// GetName
// Returns the route's name
string Route::GetName() {
  return m_name;
}

// UpdateName
// Returns the name after updating the list values
string Route::UpdateName() {
  if(m_head != nullptr && m_tail != nullptr) {
    m_name = m_head->GetCity() + " to " + m_tail->GetCity();
  }

  return m_name;
}

// GetSize
// Returns the route's size
int Route::GetSize() {
  return m_size;
}

// ReverseRoute
// Reverses the list by making a new one
void Route::ReverseRoute() {
  Airport *prev = nullptr;
  Airport *curr = m_head;
  Airport *next = nullptr;

  while(curr != nullptr) {
    next = curr->GetNext();
    curr->SetNext(prev);
    prev = curr;
    curr = next;
  }

  // Updates the tail, head and name
  // values according the the new list
  m_tail = m_head;
  m_head = prev;
}

// GetData
// Given an index, iterates through and finds
// the specified airport
Airport* Route::GetData(int index) {
  Airport *curr = m_head;
  int currIndex = 0;

  if(index < 0 || index >= m_size) {
    return nullptr;
  }

  // Traverses through the list
  while(curr != nullptr && currIndex != index) {
    curr = curr->GetNext();
    currIndex++;
  }

  return curr;
}

// DisplayRoute
// Traverses the linked list and prints the airport information
void Route::DisplayRoute() {
  if(m_size == 0) {
    cout << "Unable to display route." << endl;
  }
  else {
    Airport *temp = m_head;
    int i = 1;

    // CODE, NAME, CITY, COUNTRY (# N, # W)
    while(temp != nullptr) {
      cout << i << ". " << temp->GetCode() << ", " << temp->GetName() << ", " << temp->GetCity() << ", " << temp->GetCountry() << " (" << temp->GetNorth() << " N, " << temp->GetWest() << " W)" << endl;
      temp = temp->GetNext();
      i++;
    }
  }
}
