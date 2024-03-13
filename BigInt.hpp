#include <iostream>
#include <string>
#include <inttypes.h>
#include "./BigUInt.hpp"

namespace AGA::ComplexMath
{
  class BigInt
  {
  private:
    AGA::ComplexMath::BigUInt value;
    bool isNegative = false;

  public:
    BigInt()
    {
      isNegative = false;
      value = AGA::ComplexMath::BigUInt("0");
    }
    BigInt(AGA::ComplexMath::BigUInt v) : value(v) {}
    BigInt(std::string s) : value(s)
    {
      if(s.empty()) s = "0";
      isNegative = s[0] == '-';
    };
    std::string to_string() const
    {
      return (isNegative ? "-" : "") + value.to_string();
    };
    size_t length() const { return to_string().length(); }
    BigInt negate() const
    {
      return (isNegative ? "" : "-") + value.to_string();
    }
    BigInt abs() const
    {
      return value.to_string();
    }
    BigInt operator-() const { return negate(); }
    BigInt operator+(const BigInt &other) const
    {
      // -x + y = y - x
      if (isNegative && !other.isNegative)
      {
        BigInt const negative = (*this).negate();
        return other - negative;
      }
      // x + (-y) = x - y
      if (!isNegative && other.isNegative)
      {
        BigInt const negative = (other).negate();
        return *this - negative;
      }
      BigUInt result = value + other.value;
      return (isNegative ? "-" : "") + result.to_string();
    };
    BigInt operator-(const BigInt &other) const
    {
      // -x - y = -(x + y)
      if (isNegative && !other.isNegative)
      {
        BigInt const negative = (*this).negate();
        return -(negative + other);
      }
      // x - (-y) = x + y
      if (!isNegative && other.isNegative)
      {
        BigInt const negative = (other).negate();
        return *this + negative;
      }
      if (*this == other)
        return BigInt("0");
      BigUInt result = value - other.value;
      return (*this < other ? "-" : "") + result.to_string();
    };
    BigInt operator*(const BigInt &other) const
    {
      BigUInt result = value * other.value;
      return (isNegative != other.isNegative ? "-" : "") + result.to_string();
    };
    BigInt operator/(const BigInt &other) const
    {
      BigUInt result = value / other.value;
      return (isNegative != other.isNegative ? "-" : "") + result.to_string();
    }
    BigInt operator%(const BigInt &other) const
    {
      std::cout << "this: " << to_string() << std::endl;
      std::cout << "other: " << other.to_string() << std::endl;
      BigInt aux = *this / other;
      std::cout << "*this / other: " << aux.to_string() << std::endl;
      BigInt aux2 = aux * other;
      std::cout << "(*this / other) * other: " << aux2.to_string() << std::endl;
      BigInt result = *this - aux2;
      std::cout << "*this - ((*this / other) * other): " << result.to_string() << std::endl;
      return result;
    };
    bool operator==(const BigInt &other) const
    {
      if (isNegative != other.isNegative)
        return false;
      return value == other.value;
    };
    bool operator!=(const BigInt &other) const { return !(*this == other); }
    bool operator<(const BigInt &other) const
    {
      if (isNegative && !other.isNegative)
        return true;
      if (!isNegative && other.isNegative)
        return false;
      return value < other.value;
    };
    bool operator<=(const BigInt &other) const { return *this < other || *this == other; }
    bool operator>(const BigInt &other) const { return other < *this; }
    bool operator>=(const BigInt &other) const { return *this > other || *this == other; }
    bool operator!() const { return *this == BigInt("0"); }
  };
}