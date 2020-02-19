//------------------------------Class Heap-------------------------
//This class accepts a template of whatever data type is passed to
//it and build a binary heap from that data. It's constructor is
//called by using a function pointer which will later be used to
//help build the heap. (assests greater than or less than depending
//on what function pointer is passed in from main.
#ifndef HEAP_H
#define HEAP_H
#include <vector>
#include <iostream>
template <typename Data>
class Heap{
public:
  Heap(bool(*compare)(Data*, Data*));
  ~Heap();
  void push(Data);
  void push_priority(Data*);
  Data* pop(int);
  void bubble_down(int, int);
  bool bubble_up(int);
  bool is_empty()const;
  int size()const;
  Data* location(int);
  void fill_priority();
  std::vector<Data*> heap_sort();

private:
  std::vector<Data*> heaparray;
  bool (*datacompare)(Data*, Data*);
};


//----------------------Heap Constructor---------------------------
//precondition:empty vector(represents the heap) and empty function
//pointer.
//postcondition:vector[0] holds NULL and function pointer is set to
//the function pointer passed into the Heap class.

template <typename Data>
Heap<Data>::Heap(bool(*compare)(Data*, Data*)) {
  datacompare = compare;
  heaparray.push_back(NULL);
}

//------------------------Heap Destructor--------------------------
//precondition:full vector of pointers with allocated memory
//postcondition:all memory freed

template <typename Data>
Heap<Data>::~Heap() {
  while(!is_empty()){
    delete heaparray.back();
    heaparray.pop_back();
  }
}
//---------------------------Push----------------------------------
//precondition: Data type is passed in from caller
//postcondition: Data passed in is put into heap and is moved to
//its correct position within the Binary Heap.

template <typename Data>
void Heap<Data>::push(Data current) {
  //holds value for a swap if needed
  Data* temp;
  //holds position that needs to be moved up in the array
  int spot;
  heaparray.push_back(new Data(current));
  //compare and swap if left has lower priority
  if (heaparray.size() >= 3) {
    if (!datacompare(heaparray.at(1), heaparray.back())) {
      temp = heaparray.at(1);
      heaparray.at(1) = heaparray.back();
      heaparray.back() = temp;
      spot = heaparray.size() - 1;
      while (bubble_up(spot)) {
        spot = spot / 2;
      }
    }
    else {
      spot=heaparray.size() - 1;
      while (bubble_up(spot)) {
        spot = spot / 2;
      }
    }
  }
  fill_priority();
}

//---------------------------Push_Priority----------------------------
//precondition: Data type is passed in from caller
//postcondition: Data passed in is put into heap and is moved to
//its correct position within the Binary Heap.

template <typename Data>
void Heap<Data>::push_priority(Data* current) {
  //holds value for a swap if needed
  Data* temp;
  //holds position that needs to be moved up in the array
  int spot;
  heaparray.push_back(current);
  //compare and swap if left has lower priority
  if (heaparray.size() >= 3) {
    if (!datacompare(heaparray.at(1), heaparray.back())) {
      temp = heaparray.at(1);
      heaparray.at(1) = heaparray.back();
      heaparray.back() = temp;
      spot = heaparray.size() - 1;
      while (bubble_up(spot)) {
        spot = spot / 2;
      }
    }
    else {
      spot = heaparray.size() - 1;
      while (bubble_up(spot)) {
        spot = spot / 2;
      }
    }
  }
  fill_priority();
}


//----------------------------pop----------------------------------
//precondition:binary heap with highest priority in first position
//postcondition:pointer to original first position is passed back
//to the caller and the second highest priority value is replaced
//at the top of the heap.

template<typename Data>
Data* Heap<Data>::pop(int shrink) {
  Data* temp = heaparray.at(1);
    heaparray.at(1) = heaparray.at(heaparray.size()-1);
    heaparray.pop_back();
    bubble_down(1, shrink);
    fill_priority();
  return temp;
}

//------------------------------is_empty()-------------------------
//precondition:full or empty binary heap
//postcondition:if not empty return false, else return true

template<typename Data>
bool Heap<Data>::is_empty()const {
  //since the heap[0] is a NULL pointer a size of 1 is considered
  //empty
  return heaparray.size() == 1;
}

//-------------------------bubbledown------------------------------
//precondition:A binary heap whose highest priority value is not in
//the first position.
//postcondition:A properly formed binary heap
//This function helps reform the binary heap from the first position
//down towards the bottom of the heap.

template<typename Data>
void Heap<Data>::bubble_down(int spot, int shrink) {
  Data* temp;
  bool ontop = true;
  //if the current position being checked would compare pass limit
  if (spot * 2 > heaparray.size()-1-shrink) {
    return;
  }
  //compare current position and swap if left has a lower priority
  if (!datacompare(heaparray.at(spot), heaparray.at(spot *2))) {
    temp = heaparray.at(spot);
    heaparray.at(spot) = heaparray.at(spot * 2);
    heaparray.at(spot * 2) = temp;
    bubble_down(spot * 2, shrink);
    bubble_down(spot, shrink);
    return;
  }
  if (spot * 2 == heaparray.size()-1-shrink) {
    return;
  }
  //compare current position and swap if left has a lower priority
  if(!datacompare(heaparray.at(spot), heaparray.at(spot * 2+1))) {
    temp = heaparray.at(spot);
    heaparray.at(spot) = heaparray.at(spot * 2+1);
    heaparray.at(spot * 2+1) = temp;
    bubble_down(spot*2+1, shrink);
    bubble_down(spot,shrink);
    return;
  }
}

//-----------------------------bubbleup----------------------------
//precondition:improperly formed binary heap
//postcondition:properly formed binary heap
//this function takes a data value from the bottom of the heap
//and moves it up the binary heap as needed.

template<typename Data>
bool Heap<Data>::bubble_up(int spot) {
  Data* temp;
  bool ontop = false;
  //compare and swap values if left has a higher priority
  if (spot != 1) {
    if (datacompare(heaparray.at(spot), heaparray.at(spot / 2))) {
      temp = heaparray.at(spot / 2);
      heaparray.at(spot / 2) = heaparray.at(spot);
      heaparray.at(spot) = temp;
      ontop = true;
    }
  }
  fill_priority();
  return ontop;
}

//---------------------------heapsort------------------------------
//precondition:unsorted binary heap
//postcondition:sorted binary heap
//this function sorts the binary heap by using the pop function and
//artificially shrinking the array while moving the highest
//priority values from the front of the array to the back.

template<typename Data>
std::vector<Data*> Heap<Data>::heap_sort(){
  Data* value;
  //used to artificially shrink the heaparray size
  int shrink=1;
  while (heaparray.size()-shrink > 1) {
    value = pop(shrink);
    heaparray.at(heaparray.size() - shrink)=value;
    shrink++;
  }
  return heaparray;
}

template<typename Data>
int Heap<Data>::size()const{
  return heaparray.size();
}

template<typename Data>
Data* Heap<Data>::location(int spot) {
  Data* temp;
  temp = heaparray.at(spot);
  return temp;
}

template<typename Data>
void Heap<Data>::fill_priority() {
  for (int i = 1; i < heaparray.size(); i++) {

    heaparray.at(i)->set_priority(i);
  }
}
#endif