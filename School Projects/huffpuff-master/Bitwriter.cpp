#include "Bitstream.h"
using namespace std;



Bitwriter::Bitwriter(string output) {
  out.open(output+".huff", ios::binary);
  nbits = 0;
  buff = 0;
};

void Bitwriter::write_bit(uint8_t c) {
  buff = (buff << 1 | c);
  if (++nbits == 8) {
    flush();
  }
}

void Bitwriter::write_byte(uint8_t c) {
  flush();
  out.write((char*)&c,sizeof(char));
}

void Bitwriter::write_int32_binary(uint32_t c) {
  uint8_t byte=0;
  for (int i = 0; i <= 3; i++) {
    byte = c >> i * 8;
   // byte = byte & (long)15;
    write_byte(byte);
    byte = 0;
  }
}

void Bitwriter::flush() {
  if (nbits > 0) {
    buff = buff << (8 - nbits);
    out.put(buff);
  }
  nbits = 0;
  buff = 0;
}

