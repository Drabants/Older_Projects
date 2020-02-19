//Graph
//Contains multiple classes related to building a graph
//out of the flights schedules provided by the file
#pragma once
#ifndef GRAPH_H
#define GRAPH_H
#include <iostream>
#include <fstream>
#include <map>
#include <string>
#include <vector>
#include <algorithm>
#include <climits>
#include "astrograph.h"

class GalacticFlights;
class Edge;
class Planet;

//compare function used for sort call
bool compare_depart_time(Edge*, Edge*);

//GalacticFlights
//This class generates the entire flight graph and returns
class GalacticFlights {
public:
  GalacticFlights();
  int generate_flight_graph(std::string, std::string);
  std::vector<Planet*> retrieve_flight_map();
  void  destroy_flight_map(std::vector<Planet*>);
private:
  std::map<std::string, Planet*> galacticroutes;
};

//Planet
//This class holds the name of the planet and a list of
//edges that act as routes throughout the galaxy
class Planet {
public:
  friend class Dijkstra;
  friend class GalacticFlights;
  Planet(std::string);
  void  add_route(std::string, Planet*, int, int);
  void  dump();
  int   get_cost();
  void  set_cost(int);
  int   get_priority();
  void  set_priority(int);
  std::string planetname;
private:
  int priority = 0;
  int cost =  INT_MAX;
  bool visited = false;
  std::vector<Edge*> flights;
  Edge* flighttaken=NULL;
};

//Edge
//This class holds the information of the routes within the graph
class Edge {
  friend class GalacticFlights;
  public:
  Edge(std::string,Planet*, Planet*, int, int);
  void dump();
  Planet* origin=NULL;
  std::string shipname;
  Planet* destination=NULL;
  int dtime;
  int atime;
};





#endif