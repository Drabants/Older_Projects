#include "dijkstra.h"
using namespace std;


//used to pass the Heap class a compare function
bool compare_time(Planet* left, Planet* right) {
  return left->get_cost() <= right->get_cost();
}

Dijkstra::Dijkstra() {
  Heap<Planet> routeheap(compare_time);
}


//precondition:unevaluated vector<Planets*>
//postcondition:Exit_Failure if one planet is not reachable from an origin planet
//Exit_Success with the longest, shortest route saved
int   Dijkstra::run_routes(std::vector<Planet*>planetsandflights) {
  Heap<Planet> routeheap(compare_time);
  Planet* temp = NULL;
  for (int i = 0; i < planetsandflights.size(); i++) {
    reset_heap(routeheap, planetsandflights, i);
    while (!routeheap.is_empty()) {
      temp = routeheap.pop(0);
      //check if planet was visited before checking all routes
      if (temp->get_cost() == INT_MAX) {
        cout << "Planet: " << temp->planetname << "was not reachable from origin planet: " << planetsandflights.at(i)->planetname;
        return EXIT_FAILURE;
      }
      update_routes(temp, temp->get_cost(), routeheap);
    }
    check_longest(temp->get_cost(), temp);
  }
  return EXIT_SUCCESS;
}

//precondition:unfilled heap of planets
//postcondition:all planets from vector<Planet*> put into the heap with flightstaken reset
void Dijkstra::reset_heap(Heap<Planet>& routeheap, vector<Planet*> planetsandflights, int startplanet) {
  for (int i = 0; i < planetsandflights.size(); i++) {
    if (i == startplanet) {
      planetsandflights.at(i)->set_cost(0);
      routeheap.push_priority(planetsandflights.at(i));
      planetsandflights.at(i)->flighttaken = NULL;
    }
    else {
      planetsandflights.at(i)->set_cost(INT_MAX);
      routeheap.push_priority(planetsandflights.at(i));
      planetsandflights.at(i)->flighttaken = NULL;
    }
  }

}

//precondition:unevaluated routes from Planet* passed in
//postcondition:All routes with eligible departure times evaluated and heap positions adjusted
void Dijkstra::update_routes(Planet* currentplanet, int cost, Heap<Planet>& routeheap) {
  for (int i = 0; i < currentplanet->flights.size(); i++) {
    if (currentplanet->flights.at(i)->dtime +4 >= cost) {
      if ((currentplanet->flights.at(i)->atime) < currentplanet->flights.at(i)->destination->get_cost()) {
        currentplanet->flights.at(i)->destination->set_cost(currentplanet->flights.at(i)->atime);
        while (routeheap.bubble_up(currentplanet->flights.at(i)->destination->get_priority()));
        currentplanet->flights.at(i)->destination->flighttaken = currentplanet->flights.at(i);
      }
    }
  }
}

//precondition:possible new longest shortest route
//postcondition: if past in cost is greater, replace cost and route
//otherwise leave cost and route as is.
void  Dijkstra::check_longest(int tempcost, Planet* tempschedule) {
  Planet* temp = NULL;
  if (highestcost < tempcost) {
    highestcost = tempcost;
    longestshortest.clear();
    temp = tempschedule;
    while(temp->flighttaken != NULL) {
      longestshortest.push_back(temp->flighttaken);
      temp = temp->flighttaken->origin;
    }
  }
}

//postcondition:print schedule of flights taken to cout
void  Dijkstra::print_schedule() {
  for (int i = longestshortest.size()-1; i>=0; i--) {
    cout << longestshortest.at(i)->shipname << " : " << "Leaves " << longestshortest.at(i)->origin->planetname << " at " << longestshortest.at(i)->dtime;
    cout << " Arrives at " << longestshortest.at(i)->destination->planetname << " at " << longestshortest.at(i)->atime << endl;
  }
}