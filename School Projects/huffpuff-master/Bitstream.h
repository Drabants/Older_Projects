#ifndef BITSTREAM_H
#define BITSTREAM_H
#include <iostream>
#include <fstream>
#include <string>

class Bitwriter {
public:   
  Bitwriter(std::string);
  ~Bitwriter() { flush(); }
  void write_bit(uint8_t);
  void write_byte(uint8_t);
  void write_int32_binary(uint32_t);
  void flush();
private:
  unsigned char buff;
  unsigned char nbits;
  std::ofstream out;
};

class Bitreader {
public:
  Bitreader(std::string);
 // ~Bitreader();
  int get_bit();
  uint8_t get_byte();
 // void flush();
private:
  unsigned char nbits;
  unsigned char buff;
  std::ifstream in;
};


#endif