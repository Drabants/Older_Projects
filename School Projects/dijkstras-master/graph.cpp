#include"graph.h"
using namespace std;

GalacticFlights::GalacticFlights(){}

//precondition:none generated graph of the flight schedule
//postcondition:if the flight schedule is valid then return 0
//otherwise return EXIT_FAILURE and print out where the error was
int GalacticFlights::generate_flight_graph(string astrofile, string flightsfile) {
  ifstream galacticfile(astrofile);
  Astrograph galacticmap(galacticfile);
  ifstream infile(flightsfile);
  string shipname;
  string departplanet = "begin";
  string arriveplanet = "begin";
  int dtime;
  int atime;
  infile >> shipname;
  //go through file and validate/build graph
  while (shipname != "END") {
    atime = 0;
    infile >> departplanet;
    while (departplanet != "NEXT") {
      infile >> dtime;
      if (!dtime - atime >= 4) {
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
        cout << "error in routing from " << departplanet << " to " << arriveplanet << endl;
        return EXIT_FAILURE;
      }
      if (galacticmap.validate_time(departplanet, arriveplanet, atime - dtime)) {
        galacticroutes[departplanet]->add_route(shipname, galacticroutes[arriveplanet], dtime, atime);
      }
      else {
        cout << "error in travel time " << departplanet << " to " << arriveplanet << " took " << dtime - atime << " hours" << endl;
        return EXIT_FAILURE;
      }
      infile >> departplanet;
    }
    infile >> shipname;
  }
  return 0;
}

//precondition:map containing graph information
//postconidtion:return vector of planet pointers aka grpah information
vector<Planet*> GalacticFlights::retrieve_flight_map() {
  vector<Planet*> flightmap;
  for (map<string, Planet*>::iterator planetpoint = galacticroutes.begin(); planetpoint != galacticroutes.end(); planetpoint++) {
    flightmap.push_back(planetpoint->second);
  }
  return flightmap;
}

//precondition:vector filled with planets holding edge pointers
//postcondition:memory freed from the edge pointers then the planet pointers
void  GalacticFlights::destroy_flight_map(vector<Planet*> planetsandflights) {
  while (planetsandflights.size() > 0) {
    for (int i = 0; i < planetsandflights.at(planetsandflights.size() - 1)->flights.size(); i++) {
      delete planetsandflights.at(planetsandflights.size() - 1)->flights.at(i);
      planetsandflights.at(planetsandflights.size() - 1)->flights.at(i) = NULL;
    }
    delete planetsandflights.at(planetsandflights.size() - 1);
    planetsandflights.at(planetsandflights.size() - 1) = NULL;
    planetsandflights.pop_back();
  }
}
//postcondtion:planet name set
Planet::Planet(string name) {
  planetname = name;
}

//precondition:missing route for planet
//postconidtion:new route added to planet's vectore of edges
void Planet::add_route(string ship, Planet* dest, int depart, int arrive) {
  flights.push_back(new Edge(ship, this, dest, depart, arrive));
  sort(flights.begin(), flights.end(), compare_depart_time);
}


//precondition:unprinted flights from each planet
//postcondition:printed flights from each planet
void Planet::dump() {
  cout << "Flights from " << planetname << "---------------------------"<< flights.size()<<endl;
  for (int i = 0; i < flights.size(); i++) {
    flights.at(i)->dump();
  }
}

int Planet::get_cost() {
  return cost;
}

void  Planet::set_cost(int temp) {
  cost = temp;
}

int Planet::get_priority() {
  return priority;
}

void Planet::set_priority(int setter) {
  priority = setter;
}

Edge::Edge(string ship, Planet* oplanet, Planet* dest, int depart, int arrive) {
  
  origin = oplanet;
  shipname = ship;
  destination = dest;
  dtime = depart;
  atime = arrive;
}

void Edge::dump() {
  cout << "Ship:" << shipname << endl << "Destination:" << destination->planetname << " Leaves at " << dtime << " arrives at " << atime << endl;
}

bool  compare_depart_time(Edge* left, Edge* right) {
  return left->dtime < right->dtime;
}