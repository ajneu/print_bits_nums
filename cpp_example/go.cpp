// Just a brief example using C++.
// It uses character arrays, just to show that it can be done.

// Of course using a std::string, or banging out to std::cout immediately
// is a much better way to do this!
//
// Also note: don't use char as a number. Use signed char, or unsigned char instead.
// If you really want to output e.g. char c = 67; as a number, add 0
// i.e. use: std::cout << c + 0;


#include <iostream>
#include <algorithm>
#include <climits>
#include <iomanip>
#include <bitset>
#include <cassert>

constexpr unsigned BUFLEN_PRINTBITS ((sizeof(unsigned long long) * CHAR_BIT) + 1);


// http://stackoverflow.com/a/8765699
struct membuf: public std::streambuf {
  template <size_t Size> membuf(char (&array)[Size]) {
    this->setp(array, array + Size - 1);

    assert( array           == pbase());
    assert((array + Size-1) == epptr());

    //std::fill_n(array, Size, 0); // we can leave this, if we carefully use std::ends below
  }
};

// http://stackoverflow.com/a/8765699 (also)
struct omemstream: virtual membuf, std::ostream {
  template <size_t Size> omemstream(char (&array)[Size]):
    membuf(array),
    std::ostream(this)
  {
  }

  void rewind() {
    this->setp(pbase(), epptr());
  }
};

template <size_t Size, typename T>
void sprint_bits(char (&array)[Size], T num)
{
  omemstream out(array);
  constexpr unsigned numbits = CHAR_BIT*sizeof(T);
  out << std::bitset<numbits>(num) << std::ends;
}

template <size_t Size, typename T>
void sprint_oct(char (&array)[Size], T num)
{
  omemstream out(array);
  constexpr unsigned numbits = (CHAR_BIT*sizeof(T)+2) / 3;
  out << std::oct << std::setfill('0') << std::setw(numbits) << num+0 << std::ends;
}

template <size_t Size, typename T>
void sprint_hex(char (&array)[Size], T num)
{
  omemstream out(array);
  constexpr unsigned numbits = CHAR_BIT*sizeof(T) / 4;
  out << std::hex << std::uppercase << std::setfill('0') << std::setw(numbits) << num + 0 << std::ends;
}

template <size_t Size, typename T>
void sprint_num(char (&array)[Size], T num)
{
  omemstream out(array);
  out << std::dec << num + 0 << std::ends;
}

int main()
{
  char array[BUFLEN_PRINTBITS];

  unsigned char x=15;
  std::cout << "Binary: " << (sprint_bits(array, x), array) << std::endl;
  //                                                \
  //                                           comma operator
  std::cout << "Hex   : " << (sprint_hex( array, x), array) << std::endl;
  std::cout << "Oct   : " << (sprint_oct( array, x), array) << std::endl;

  std::cout << "Binary: " << (sprint_bits(array, -1+11), array) << std::endl;
  std::cout << "Hex   : " << (sprint_hex( array, -1+11), array) << std::endl;
  std::cout << "Oct   : " << (sprint_oct( array, -1+11), array) << std::endl;

  unsigned long long ull = 0x8000000000000000;
  std::cout << "Unsigned number : " << (sprint_num(array, ull), array) << std::endl;

  signed long long sll = 0x8000000000000000;
  std::cout << "Signed number   : " << (sprint_num(array, sll), array) << std::endl;

  std::cout << "understanding integer promotion: -2+0U = " << (sprint_num(array, -2+0U), array) << std::endl;
  
  return 0;
}
