#include <iostream>
#include <vector>
#include <string>
#include <inttypes.h>
#include "./biInt.hpp"
#include "./util.hpp"

namespace AGA
{
  class BigInt
  {
  private:
    AGA::Util::List<biInt> digits;
    bool isNegative;

  public:
    BigInt();
    BigInt(std::string);
    std::string to_string();
    BigInt operator-() { return BigInt(to_string().substr(0, 1) == "-" ? to_string().substr(1) : "-" + to_string()); };
    BigInt operator-(const BigInt &other);
    BigInt operator+(const BigInt &other);
    BigInt operator*(const BigInt &other);
    BigInt operator/(const BigInt &other);
    BigInt operator%(const BigInt &other);
    BigInt operator-(const int &other);
    BigInt operator+(const int &other);
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

AGA::BigInt::BigInt()
{
  digits.addEnd(AGA::biInt());
  isNegative = false;
}
AGA::BigInt::BigInt(std::string s)
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
      AGA::biInt x;
      x.set_second_digit((AGA::Base10)(c-'0'));
      digits.addStart(x);
    }
    else
    {
      AGA::biInt x = digits.get(0);
      x.set_first_digit((AGA::Base10)(c-'0'));
      digits.set(0, x);
    }
  }
}
std::string AGA::BigInt::to_string()
{
  int size = digits.length();
  std::string s;
  for (int i = 0; i < size; ++i)
  {
    AGA::biInt x = digits.get(i);
    s = x.to_string() + s;
  }
  return isNegative ? "-" + s : s;
}
AGA::BigInt AGA::BigInt::operator+(const BigInt &other)
{
  int size = digits.length();
  int otherSize = other.digits.length();
  int maxSize = size > otherSize ? size : otherSize;
  AGA::BigInt result;
  AGA::biInt carry;
  for (int i = 0; i < maxSize; ++i)
  {
  }
  return result;
}