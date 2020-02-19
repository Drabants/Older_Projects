//Shelby Drabant
//This program takes two arguements from the command line
//the first arguement should be a file that will help construct an
//astrograph used for comparisons later. The second file will contain
//ship name then a series of departure planet departure time destination planet
//arrival time. It will then build a graph based on the ship file and compare it
//to the astrograph file. Once all data has been verified, it will then run 
//Dijkstras to find the longest shortest route from the ship file and display it

#include <vector>
#include <iostream>
#include <string>
#include "astrograph.h"
#include "graph.h"
#include "dijkstra.h"
using namespace std;

int main(int argc, char *argv[]) {
  GalacticFlights flightmap;
  vector<Planet*> planetsandflights;
  if (flightmap.generate_flight_graph(argv[1], argv[2]) == EXIT_FAILURE) {
    return EXIT_FAILURE;
  }
  planetsandflights = flightmap.retrieve_flight_map();
  Dijkstra fastesttrip;
  if (fastesttrip.run_routes(planetsandflights) == EXIT_FAILURE) {
    return EXIT_FAILURE;
  }
  fastesttrip.print_schedule();
  flightmap.destroy_flight_map(planetsandflights);

  return 0;
}