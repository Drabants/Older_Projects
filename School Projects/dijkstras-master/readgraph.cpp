#include <iostream>
#include <fstream>
#include <string>
#include "graph.h"
#include "astrograph.h"

using namespace std;


int main(int argc, char *argv[]) {
  map<string, Planet*> galacticroutes;
  ifstream galacticfile(argv[1]);
  Astrograph galacticmap(galacticfile);
  ifstream infile(argv[2]);
    string shipname;
    string departplanet = "begin";
    string arriveplanet = "begin";
    int dtime;
    int atime;
    infile >> shipname;
    while (shipname != "END") {
      atime = -4;
      infile >> departplanet;
      while (departplanet != "NEXT") {
        infile >> dtime;
        if (dtime - 4 != atime) {
          cout << "depart time does not account for refueling at " << departplanet;
          return EXIT_FAILURE;
        }
        infile >> arriveplanet;
        infile >> atime;
        if (galacticmap.validate_route(departplanet, arriveplanet)) {
          if (galacticroutes[departplanet] == NULL) {
            galacticroutes[departplanet] = new Planet(departplanet);
          }
          if (galacticroutes[arriveplanet] == NULL) {
            galacticroutes[arriveplanet] = new Planet(arriveplanet);
          }
        }
        else {
          cout << "error in routing from " << departplanet << " to " << arriveplanet;
          return EXIT_FAILURE;
        }
        if (galacticmap.validate_time(departplanet, arriveplanet, atime - dtime)){
          galacticroutes[departplanet]->add_route(shipname, galacticroutes[arriveplanet], dtime, atime);
        }
        else {
          cout << "error in travel time " << departplanet << " to " << arriveplanet << " took " << dtime - atime << " hours";
          return EXIT_FAILURE;
        }
        infile >> departplanet;
      }
      infile >> shipname;
    }
    for (map<string, Planet*>::iterator planet = galacticroutes.begin(); planet != galacticroutes.end(); planet++) {
      planet->second->dump();
    }
  return 0;
}