#include "Bitstream.h"
using namespace std;

Bitreader::Bitreader(string file) {
  in.open(file);
  nbits = 0;
  buff = 0;
}
int Bitreader::get_bit() {
  if (nbits == 0) {
    int c = get_byte();
    if (c < 0) {
      return -1;
    }
    buff = c;
    nbits = 8;
  }
  return (buff >> --nbits) & 1;
}

uint8_t Bitreader::get_byte() {
 // flush();
  char c;
  in.get(c);
  if (!in) {
    return -1;
  }
  return (c);
}

/*int Bitreader::flush() {
  if (nbits > 0) {
    buff = buff << (8 - nbits);
  }
  nbits = 0;
  buff = 0;
}*/