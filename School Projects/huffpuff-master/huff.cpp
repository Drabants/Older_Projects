#include <iostream>
#include <fstream>
#include <iomanip>
#include <string>
#include <vector>
#include <cmath>
#include <bitset> 
#include "Heap.h"
#include "Bitstream.h"
using namespace std;

struct Node{
  Node* left;
  Node* right;
  int frequency;
  int symbol;
  Node(int a=0, int b=0, Node* first=NULL, Node* second=NULL) {
    frequency = a;
    symbol= b;
    left = first;
    right = second;
  }
};

//Symbol
//hold huffman code and number of bitcount within that huffman code
//huffman code is big endian
struct Symbol{
  unsigned int bitcount;
  uint64_t charcode;
  Symbol(int count=0, int code=0) {
    bitcount = count;
    charcode = code;
  }
};

bool compare(Node*, Node*);
void build_frequency_heap(int*, Heap<Node>&);
void build_tree(Heap<Node>&);
void build_table(Node*, Symbol*, int&, uint64_t);
void display_tree(Node*, ofstream&);
void print_table(Symbol*, Bitwriter&);
void print_count(Bitwriter&, uint32_t);
void print_encoding(ifstream&, Symbol*, Bitwriter&);
void dump(int*, Symbol*, Node*);
void destroy_tree(Node*);


int main(int argc, char *argv[]) {
  Heap<Node> priorityqueue(compare);
  char temp;
  unsigned long long huffcode = 0;
  int frequency[256] = { 0 };
  Symbol table[256];
  unsigned long long codetable[256] = { 0 };
  uint32_t charcount=0;
  int bitadjust = 64;
  Node* huffroot;
  Bitwriter binarywrite(argv[1]);
  ifstream filename(argv[1]);
  if (!filename.is_open()) {
    cout << "File could not be opened. Now exiting" << endl;
    return EXIT_FAILURE;
  }
  //build frequency table
  while (filename.get(temp)) {
    frequency[(int)temp]++;
    charcount++;
  }
  build_frequency_heap(frequency, priorityqueue);
  build_tree(priorityqueue);
  huffroot = priorityqueue.pop(0);
  build_table(huffroot, table, bitadjust, huffcode);
  print_table(table, binarywrite);
  binarywrite.write_int32_binary(charcount);
  print_encoding(filename, table, binarywrite);
  dump(frequency, table, huffroot);
  destroy_tree(huffroot);
  return 0;
}

bool compare(Node* left, Node* right) {
  return left->frequency <= right->frequency;
}

void build_frequency_heap(int* frequency, Heap<Node>& priorityqueue) {
  Node charleaf;
  for (int i = 0; i < 256; i++) {
    if (frequency[i] != 0) {
      charleaf.frequency = frequency[i];
      charleaf.symbol = i;
      priorityqueue.push(charleaf);
    }
  }
}

void build_tree(Heap<Node>& priorityqueue) {
  while (priorityqueue.size()>2){
    Node* first= priorityqueue.pop(0);
    Node* second= priorityqueue.pop(0);
    Node innernode( first->frequency +second->frequency , 0, first, second);
    cout << (char)first->symbol <<first->frequency<<"+" <<  (char)second->symbol <<second->frequency<< "pop " <<innernode.frequency << endl;
    priorityqueue.push(innernode);
    cout << (char)innernode.right->symbol<< (char)innernode.left->symbol << endl;
  }
}

void build_table(Node* hufftree, Symbol* table, int& shifter, uint64_t code) {
  if (hufftree->left == NULL && hufftree->right == NULL) {
    shifter++;
    table[hufftree->symbol].charcode = code;
    table[hufftree->symbol].bitcount = 65 - shifter;
    return;
  }
  if (hufftree->left != NULL) {
    shifter--;
    build_table(hufftree->left, table, shifter, code);
  }
  if (hufftree->right != NULL) {
    shifter--;
  //  cout << "right" << shifter << endl;
    code = code + pow(2,shifter);
    build_table(hufftree->right, table, shifter, code);
  }
  shifter++;
}


void print_table(Symbol* table, Bitwriter& write) {
  uint8_t bits = 0;
  int bytes;
  for (int i = 0; i < 256; i++) {
    bits = 0;
    if (table[i].bitcount == 0) {
      write.write_byte(bits);
    }
    else {
      write.write_byte(bits = table[i].bitcount);
      bytes = ceil((float)table[i].bitcount / 8.0);
      cout << bytes << endl;
      for (int s = 1; s <= bytes; s++) {
        write.write_byte(bits = table[i].charcode >> 64-8*s);
      }
    }
  }
}

void print_encoding(ifstream& filename, Symbol* table, Bitwriter& write) {
  filename.clear();
  filename.seekg(0, ios::beg);
  uint8_t bit;
  char temp;
  int bits=0;
  while (filename.get(temp)) {
    bits= table[(int)temp].bitcount; 
  //  cout << temp << ": bits : ";
    for (int i = 1; i <= bits; i++) {
      bit = table[(int)temp].charcode >> 64 - i;
      bit = bit & 1;
   //   cout << unsigned(bit);
      write.write_bit(bit);
    }
//    cout << endl;
  }
}

void dump(int* frequency, Symbol* table, Node* huffroot) {
  ofstream debugg("dump.huff");
  debugg << "displaying frequency table" << endl;
  for (int i = 0; i < 256; i++) {
    debugg << (char)i << " : " << frequency[i] << endl;
  }
  debugg << "displaying tree" << endl;
  display_tree(huffroot, debugg);
  debugg << "displaying huffcode table " << endl;
  for (int i = 0; i < 256; i++) {
    debugg << char(i) <<dec << table[i].bitcount << " : " <<hex << table[i].charcode << endl;
  }
}

void display_tree(Node* hufftree, ofstream& debugg) {
  if (hufftree->left == NULL&& hufftree->right == NULL) {
    debugg << (char)hufftree->symbol << endl;
    return;
  }
  if (hufftree->left != NULL) {
    debugg << "----1";
    display_tree(hufftree->left,debugg);
  }
  if (hufftree->right != NULL) {
    debugg << "----0";
    display_tree(hufftree->right,debugg);
  }
}

void destroy_tree(Node* root) {
  if (root == NULL) return;
  destroy_tree(root->left);
  destroy_tree(root->right);
  delete root;
}