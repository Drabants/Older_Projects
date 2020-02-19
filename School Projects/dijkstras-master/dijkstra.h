//Dijkstra
//This class takes a vector of Planet pointers and evaluates their
//edges in order to find the longest shortest routes

#pragma once
#ifndef DIJKSTRA_H
#define DIJKSTRA_H
#include "Heap.h"
#include "graph.h"
#include <iostream>
#include <vector>
#include <string>
#include <climits>

bool compare_time(Planet*, Planet*);

class Dijkstra {
public:
  Dijkstra();
  int   run_routes(std::vector<Planet*>);
  void  update_routes(Planet*, int, Heap<Planet>&);
  void  reset_heap(Heap<Planet>&, std::vector<Planet*>, int);
  void  check_longest(int, Planet*);
  void  print_schedule();
private:
  int highestcost = 0;
  std::vector<Edge*> longestshortest;
};















#endif