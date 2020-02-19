//Astrograph
//This class is used to build a map of the possible routes within the galaxy
//This map will then be used to help compare possible ship flights when
//constructing the graph
#pragma once
#ifndef ASTROGRAPH_H
#define ASTROGRAPH_H
#include <iostream>
#include <fstream>
#include <string>
#include <map>

class Astrograph {
public:
  Astrograph(std::ifstream&);
  void add_planet(std::string);
  void add_routes(std::ifstream&, std::string);
  bool validate_route(std::string, std::string);
  bool validate_time(std::string, std::string, int);
  void dump();
private:
  //uses a map within a map. first string is the planetname a
  //second string is the destination and the int serves as the time
  //of travel between both.
  std::map<std::string, std::map<std::string, int > > galaxy;
};





















#endif