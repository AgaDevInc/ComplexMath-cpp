#include <iostream>
#include <string>
#include <inttypes.h>

namespace AGA::ComplexMath
{
  enum Base10
  {
    Zero = 0,
    One = 1,
    Two = 2,
    Three = 3,
    Four = 4,
    Five = 5,
    Six = 6,
    Seven = 7,
    Eight = 8,
    Nine = 9
  };
  class biInt
  {
  private:
    uint8_t digits;
  public:
    biInt()
    {
      digits = 0;
    }
    biInt(Base10 n1, Base10 n2)
    {
      digits = n1 << 4;
      digits += n2;
    }
    std::string to_string()
    {
      std::string s;
      s += std::to_string(digits >> 4);
      s += std::to_string(digits & 0x0F);
      return s;
    }
    uint8_t get_first_digit()
    {
      return digits >> 4;
    }
    uint8_t get_second_digit()
    {
      return digits & 0x0F;
    }
    void set_first_digit(Base10 n)
    {
      digits = get_second_digit();
      digits += n << 4;
    }
    void set_second_digit(Base10 n)
    {
      digits = get_first_digit() << 4;
      digits += n;
    }
  };
}
