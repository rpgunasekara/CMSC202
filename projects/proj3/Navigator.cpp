/*
 * Name: Navigator.cpp
 * Project: CMSC 202 Project 3, Spring 2024
 * Author: Ravindu Gunasekara
 * Date: 03/29/2024
 * Desc: This file contains the function
 *       definitions for the Navigator
 *       class.
 */

#include "Navigator.h"
using namespace std;

// Navigator
// Overloaded constructor
Navigator::Navigator(string fileName) : m_fileName(fileName) {
  cout << "File Received (" << m_fileName << ")" << endl;
}

// ~Navigator
// Deconstructor
Navigator::~Navigator() {
  // Iterates through airport and route vectors
  for(Airport *tempAirport : m_airports) {
    delete tempAirport;
  }

  for(Route *tempRoute : m_routes) {
    delete tempRoute;
  }

  m_fileName = "";
}

// Start
// Begins the airline manager
void Navigator::Start() {
  ReadFile();
  MainMenu();
}

// DisplayAirports
// Iterates through airports and prints basic information
void Navigator::DisplayAirports() {
  int i = 1;
  for(Airport *temp : m_airports) {
    cout << i << ". " << *temp << endl;
    i++;
  }
}

// ReadFile
// Reads through file to create airport objects
void Navigator::ReadFile() {
  ifstream file(m_fileName);

  if(!file.is_open()) {
    cout << "Error opening file." << endl;
    return;
  }
  else {
    cout << "Opened File" << endl;
  }

  int i = 1;
  while(i <= 40) {
    // Takes data in as strings, converts coordinates after
    string code, name, city, country, northStr, westStr;
    getline(file, code, ',');
    getline(file, name, ',');
    getline(file, city, ',');
    getline(file, country, ',');
    getline(file, northStr, ',');
    getline(file, westStr);
    double north = stod(northStr);
    double west = stod(westStr);

    // Creates and adds object to vector
    Airport *newAirport = new Airport(code, name, city, country, north, west);
    m_airports.push_back(newAirport);
    i++;
  }

  cout << "Airports Loaded: 40" << endl;

  file.close();
}

// InsertNewRoute
// Adds an airport to an existing route
void Navigator::InsertNewRoute() {
  Route *newRoute = new Route();
  int numOfAirports = 0;
  int choice = 0;

  DisplayAirports();
  do {
    cout << "What airport do you want to add to your route? (1 - 40, -1 to end): " << endl;
    cin >> choice;

    // Validates choice
    if(choice >= 1 && choice <= int(m_airports.size())) {
      Airport *airport = m_airports[choice - 1];
      newRoute->InsertEnd(airport->GetCode(), airport->GetName(), airport->GetCity(), airport->GetCountry(), airport->GetNorth(), airport->GetWest());
      numOfAirports++;
    }
    else if(choice != -1) {
      cout << "Unable to add airport to route." << endl;
    }

  } while(numOfAirports < ROUTE_MIN || choice != -1);

  newRoute->UpdateName();
  m_routes.push_back(newRoute);
  cout << "You've created a route from " << newRoute->GetName() << "." << endl;
}

// MainMenu
// Main part of the program, runs until user specifies to exit
void Navigator::MainMenu() {
  int choice;

  cout << "Welcome to UMBC Airline Manager!" << endl;

  do {
    cout << "What would you like to do? (1 - 4, 5 to exit): " << endl;
    cout << "1. Create New Route" << endl;
    cout << "2. Display Route" << endl;
    cout << "3. Remove Airport From Route" << endl;
    cout << "4. Reverse Route" << endl;
    cout << "5. Exit" << endl;
    cin >> choice;

    switch(choice) {
    case 1:
      InsertNewRoute();
      break;
    case 2:
      DisplayRoute();
      break;
    case 3:
      RemoveAirportFromRoute();
      break;
    case 4:
      ReverseRoute();
      break;
    case 5:
      cout << "Deleting Airports...Done." << endl;
      cout << "Deleting Routes...Done." << endl;
      cout << "Routes removed from memory, exiting program." << endl;
      break;
    default:
      cout << "ERROR: INVALID CHOICE" << endl;
      break;
    }
  } while(choice != 5);
}

// ChooseRoute
// Helper function to select from an existing route
int Navigator::ChooseRoute() {
  int choice;

  cout << "Select a route: " << endl;

  for(int i = 0; i < int(m_routes.size()); i++) {
    cout << i + 1 << ". " << m_routes[i]->GetName() << endl;
  }

  cin >> choice;

  // Validates choice
  if(choice >= 1 && choice <= int(m_routes.size())) {
    return choice - 1;
  }
  else {
    cout << "ERROR: INVALID CHOICE" << endl;
    return -1;
  }

  return -1;
}

// DisplayRoute
// Display information for a total flight
void Navigator::DisplayRoute() {
  int index = ChooseRoute();

  if(index != -1) {
    Route *route = m_routes[index];

    cout << route->GetName() << endl;
    route->DisplayRoute();

    double distance = RouteDistance(route);
    cout << "The total miles of this route is " << distance << " miles." << endl;
  }
  else {
    cout << "Unable to display route." << endl;
  }
}

// RemoveAirportFromRoute
// Allows user to reduce the number of stops on their route
void Navigator::RemoveAirportFromRoute() {
  int index = ChooseRoute();

  if(index != -1) {
    Route *route = m_routes[index];
    int airportIndex;
    bool removeValid = false;

    cout << route->GetName() << endl;
    route->DisplayRoute();

    // Loops until a valid choice is made
    do {
      cout << "Which airport would you like to remove? (1 - " << route->GetSize() << "):" << endl;
      cin >> airportIndex;

      if(airportIndex >= 1 && airportIndex <= route->GetSize()) {
        route->RemoveAirport(airportIndex - 1);
        route->UpdateName();
        cout << "Removing airport...Done." << endl;
        route->DisplayRoute();
        cout << "Route is now " << route->GetName() << "." << endl;
        removeValid = true;
      }
      else {
        cout << "ERROR: INVALID CHOICE" << endl;
      }
    } while(removeValid == false);
  }
  else {
    cout << "Unable to remove airport." << endl;
  }
}

// RouteDistance
// Returns the total distance of a trip
double Navigator::RouteDistance(Route *route) {
  double total = 0;

  if(route->GetSize() < ROUTE_MIN) {
    cout << "Unable to calculate route distance." << endl;
    return total;
  }

  // Iterates and calculates distance from airport to airport
  for(int i = 0; i < route->GetSize() - 1; i++) {
    Airport *airport1 = route->GetData(i);
    Airport *airport2 = route->GetData(i + 1);
    double distance = CalcDistance(airport1->GetNorth(), airport1->GetWest(), airport2->GetNorth(), airport2->GetWest());
    total += distance;
  }

  return total;
}

// ReverseRoute
// User selects an existing route to reverse
void Navigator::ReverseRoute() {
  int index = ChooseRoute();

  if(index != -1) {
    Route *route = m_routes[index];
    route->ReverseRoute();

    cout << "Reversing route...Done." << endl;
    cout << "Route is now " << route->UpdateName() << "." << endl;
  }
  else {
    cout << "Unable to reverse route." << endl;
  }
}
