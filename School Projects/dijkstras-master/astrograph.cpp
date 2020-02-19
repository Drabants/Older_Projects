#include "astrograph.h"
using namespace std;


//precondition:unread file containing astrograph information
//postcondition:completed astrograph
Astrograph::Astrograph(ifstream& readfile) {
  string temp;
  readfile >> temp;
  while (temp != "END") {
    add_planet(temp);
    readfile >> temp;
  }
  readfile >> temp;
  while (temp != "END") {
    add_routes(readfile, temp);
    readfile >> temp;
  }
}

//precondition:map not containing planet whose name is passed in
//postcondition:planet added to map
void Astrograph::add_planet(string planetname) {
    galaxy[planetname];
}

//precondition:planet in the map missing a route
//postconidtion:route added to both destination and origin planet
//with times added as well
void Astrograph::add_routes(ifstream& infile, string planetname) {
  string destination;
  int time;
  infile >> destination;
  infile >> time;
  while (destination != "NEXT") {
    galaxy[planetname][destination]=time;
    galaxy[destination][planetname] = time;
    infile >> destination;
    infile >> time;
  }
}

//precondition:two strings comparing planets for route connection
//postcondition:Return false if no connection is found and true if one is
bool Astrograph::validate_route(string originplanet, string destination) {
  return galaxy[originplanet][destination] != 0;
}

//precondition:an origin planet, destination and travel time are passed in
//postcondition:If the time does not == the proper time for travel in the galaxy map
//return false, otherwise return true.
bool Astrograph::validate_time(string originplanet, string destination, int time) {
  return time == galaxy[originplanet][destination];
}

//precondition:no text sent to cout
//postcondition:a list of all planets and their routes and how long travel time will take
void Astrograph::dump() {
  string currentplanet;
  for (map<string, map<string, int> >::iterator planet = galaxy.begin(); planet != galaxy.end(); planet++) {
    currentplanet = planet->first;
    cout << "-------------------------" << endl<< "Origin Planet " << currentplanet << endl;
    for (map<string, int>::iterator destination = galaxy[currentplanet].begin(); destination != galaxy[currentplanet].end(); destination++){
      cout << destination->first << " will take " << destination->second << " hours" << endl;
    }
  }
}