#include <iostream>
#include <fstream>
#include <string>
#include <cmath>
#include <queue>
#include "Bitstream.h"
#include "Heap.h"
using namespace std;

struct Symbol {
  unsigned int bitcount;
  uint64_t ceil;
  Symbol(int count = 0, int code = 0) {
    bitcount = count;
    ceil = code;
  }
};

struct Node {
  Node* left;
  Node* right;
  int frequency;
  int symbol;
  Node(int a = 0, int b = 0, Node* first = NULL, Node* second = NULL) {
    frequency = a;
    symbol = b;
    left = first;
    right = second;
  }
};

void build_table(Bitreader& ,Symbol*);
void build_huff_tree(Node*&, Symbol*);
void get_number_char(uint32_t&, Bitreader&);
void print_message(Node*, uint32_t, Bitreader&, ofstream&);
void display_tree(Node*);
void destroy_tree(Node*);

int main(int argc, char *argv[]){
  Node* huffroot;
  uint32_t charcount;
  Symbol codetable[256]{ 0 };
  string namecheck = argv[1];
  Bitreader decode(namecheck);
  ofstream puffwrite;
  if (namecheck.substr(namecheck.find_last_of(".") + 1) != "huff") {
    cout << namecheck << " does not contain the proper extention .huff" << endl;
    return EXIT_FAILURE;
  }
  puffwrite.open((namecheck.erase(namecheck.find_last_of("."))) + ".puff");
  build_table(decode, codetable);
  build_huff_tree(huffroot, codetable);
  display_tree(huffroot);
  get_number_char(charcount, decode);
  print_message(huffroot, charcount, decode, puffwrite);
  destroy_tree(huffroot);
  return 0;
}



void build_table(Bitreader& decode, Symbol* table) {
  for (int i = 0; i < 256; i++) {
    table[i].bitcount = decode.get_byte();
    if (table[i].bitcount != 0) {
      for (int s = 0; s < (int)ceil(table[i].bitcount / 8.0); s++) {
        table[i].ceil = table[i].ceil + decode.get_byte();
        if (s < 7) {
          table[i].ceil = table[i].ceil << 8;
        }
      }
      table[i].ceil = table[i].ceil << 56 - 8 * (int)ceil(table[i].bitcount / 8.0);
    }
    cout << (char)i << table[i].bitcount << ":" << hex << table[i].ceil << endl;
  }
}
void build_huff_tree(Node*& root, Symbol* table) {
  Node* walker;
  int currentbits;
  uint64_t currentcode;
  root = new Node;
  for (int i = 0; i < 256; i++) {
    walker = root;
    currentbits = table[i].bitcount;
    if (currentbits != 0) {
      for (int s = 0; s < currentbits; s++) {
        currentcode = table[i].ceil>>63-s;
        currentcode = currentcode & 1;
        cout << currentcode;
        if (currentcode == 0) {
          if (walker->left == NULL) {
            walker->left = new Node;
            walker = walker->left;
          }
          else {
            walker = walker->left;
          }
        }
        else {
          if (walker->right == NULL) {
            walker->right = new Node;
            walker = walker->right;
          }
          else {
            walker = walker->right;
          }
        }
      }
      cout << endl;
      walker->symbol = i;
    }
  }
}

void get_number_char(uint32_t& charcount, Bitreader& decode) {
  uint32_t temp;
  for (int i = 0; i < 3; i++) {
    temp = decode.get_byte();
    charcount = (temp<<8*i)+charcount;
    cout << charcount << endl;
  }
  temp = decode.get_byte();
  charcount = charcount + (temp << 24);
  cout<< charcount<<endl;
}

void print_message(Node* root, uint32_t charcount, Bitreader& decode, ofstream& puffwriter) {
  bool charprint;
  Node* walk;
  int temp;
  for (int i = 0; i < charcount; i++) {
    charprint = false;
    walk = root;
    while (!charprint) {
      temp = decode.get_bit();
      cout << temp;
      if (temp==0) {
          walk = walk->left;
        }
        else {
          walk = walk->right;
        }
      if (walk->left == NULL) {
          puffwriter << (char)walk->symbol;
          charprint = true;
      }
    }
  }
}

void display_tree(Node* hufftree) {
  if (hufftree->left == NULL&& hufftree->right == NULL) {
    cout << (char)hufftree->symbol << endl;
    return;
  }
  if (hufftree->left != NULL) {
    cout << "----0";
    display_tree(hufftree->left);
  }
  if (hufftree->right != NULL) {
    cout << "----1";
    display_tree(hufftree->right);
  }
}

void destroy_tree(Node* root) {
  if (root == NULL) return;
  destroy_tree(root->left);
  destroy_tree(root->right);
  delete root;
}