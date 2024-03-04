#include <iostream>
#include <vector>
#include <string>
#include <inttypes.h>
#include "./biInt.hpp"
#include "./util.hpp"

namespace AGA::ComplexMath
{
  class BigInt
  {
  private:
    AGA::Util::List<AGA::ComplexMath::biInt> digits;
    bool isNegative;

  public:
    BigInt()
    {
      digits.addEnd(AGA::ComplexMath::biInt());
      isNegative = false;
    }
    BigInt(std::string s)
    {
      isNegative = s[0] == '-';
      if (isNegative)
      {
        s = s.substr(1);
      }
      int size = s.size();
      for (int i = 1; i <= size; ++i)
      {
        char c = s[size - i];
        if (i % 2)
        {
          AGA::ComplexMath::biInt x;
          x.set_second_digit((AGA::ComplexMath::Base10)(c - '0'));
          digits.addStart(x);
        }
        else
        {
          AGA::ComplexMath::biInt x = digits.get(0);
          x.set_first_digit((AGA::ComplexMath::Base10)(c - '0'));
          digits.set(0, x);
        }
      }
    };
    std::string to_string()
    {
      int size = digits.length();
      std::string s;
      for (int i = 0; i < size; ++i)
      {
        AGA::ComplexMath::biInt x = digits.get(i);
        s = x.to_string() + s;
      }
      return isNegative ? "-" + s : s;
    };
    BigInt operator-() { return BigInt(to_string().substr(0, 1) == "-" ? to_string().substr(1) : "-" + to_string()); };
    BigInt operator+(const BigInt &other)
    {
      int size = digits.length();
      int otherSize = other.digits.length();
      int maxSize = size > otherSize ? size : otherSize;
      BigInt result;
      biInt carry;
      for (int i = 0; i < maxSize; ++i)
      {
      }
      return result;
    };
    BigInt operator-(const BigInt &other);
    BigInt operator*(const BigInt &other);
    BigInt operator/(const BigInt &other);
    BigInt operator%(const BigInt &other);
    BigInt operator+(const int &other);
    BigInt operator-(const int &other);
    BigInt operator*(const int &other);
    BigInt operator/(const int &other);
    BigInt operator%(const int &other);
    bool operator==(const BigInt &other);
    bool operator!=(const BigInt &other) { return !(*this == other); }
    bool operator<(const BigInt &other);
    bool operator<=(const BigInt &other) { return *this < other || *this == other; }
    bool operator>(const BigInt &other);
    bool operator>=(const BigInt &other) { return *this > other || *this == other; }
    bool operator!();
  };
}