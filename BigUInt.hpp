#include <iostream>
#include <string>
#include <inttypes.h>
#include "./biInt.hpp"
#include "./Util/List.hpp"
#include "./Util/string.hpp"

namespace AGA::ComplexMath
{
  class BigUInt
  {
  private:
    AGA::Util::List<AGA::ComplexMath::biInt> digits;

  public:
    BigUInt()
    {
      digits.addEnd(AGA::ComplexMath::biInt());
    }
    BigUInt(std::string s)
    {
      if (s.empty())
        s = "0";
      if (s[0] == '-')
        s[0] = '0';
      // 00123 -> 123
      s = AGA::Util::String::removeCharStart(s, '0');
      if (s.empty())
        s = "0";
      int size = s.size();
      for (int i = 1; i <= size; ++i)
      {
        char c = s[size - i];
        if (!std::isdigit(c))
          throw std::invalid_argument("The char \"" + std::string(1, c) + "\" is not a digit");
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
    std::string to_string() const
    {
      int size = digits.length();
      std::string s = "";
      for (int i = 0; i < size; ++i)
      {
        AGA::ComplexMath::biInt x = digits.get(i);
        s += x.to_string();
      }
      s = AGA::Util::String::removeCharStart(s, '0');
      if (s.empty())
        s = "0";
      return s;
    };
    size_t length() const
    {
      return to_string().length();
    }
    BigUInt operator+(const BigUInt &other) const
    {
      int size = digits.length();
      int otherSize = other.digits.length();
      int maxSize = size > otherSize ? size : otherSize;
      std::string result = "";
      int8_t carry = 0;
      for (int i = 1; i <= maxSize; ++i)
      {
        int this_i = size - i;
        int other_i = otherSize - i;

        // if i > size, then value_i < 0
        int8_t a = this_i >= 0 ? digits.get(this_i).get_first_digit() : 0;
        int8_t b = this_i >= 0 ? digits.get(this_i).get_second_digit() : 0;

        int8_t c = other_i >= 0 ? other.digits.get(other_i).get_first_digit() : 0;
        int8_t d = other_i >= 0 ? other.digits.get(other_i).get_second_digit() : 0;

        int8_t second = b + d + carry;
        carry = second / 10;
        second %= 10;

        int8_t first = a + c + carry;
        carry = first / 10;
        first %= 10;

        result = std::to_string(first) + std::to_string(second) + result;
      }

      return std::to_string(carry) + result;
    };
    BigUInt operator-(const BigUInt &other) const
    {
      if (*this == other)
        return BigUInt("0");
      BigUInt x(to_string());
      BigUInt y(other.to_string());
      if (x < y)
      {
        BigUInt temp = x;
        x = y;
        y = temp;
      }
      int size = x.digits.length();
      int otherSize = y.digits.length();
      int maxSize = size > otherSize ? size : otherSize;
      std::string result = "";
      int8_t carry = 0;
      for (int i = 1; i <= maxSize; ++i)
      {
        int this_i = size - i;
        int other_i = otherSize - i;

        // if i > size, then value_i < 0
        int8_t a = this_i < x.digits.length() ? x.digits.get(this_i).get_first_digit() : 0;
        int8_t b = this_i < x.digits.length() ? x.digits.get(this_i).get_second_digit() : 0;

        int8_t c = other_i >= 0 ? y.digits.get(other_i).get_first_digit() : 0;
        int8_t d = other_i >= 0 ? y.digits.get(other_i).get_second_digit() : 0;

        int8_t second = b - d - carry;
        carry = second < 0;
        second = second < 0 ? second + 10 : second;

        int8_t first = a - c - carry;
        carry = first < 0;
        first = first < 0 ? first + 10 : first;

        result = std::to_string(first) + std::to_string(second) + result;
      }
      return std::to_string(carry) + result;
    };
    BigUInt operator*(const BigUInt &other) const
    {
      int size = digits.length();
      int otherSize = other.digits.length();
      std::string result = "";
      int8_t carry = 0;
      for (int i = 1; i <= size; ++i)
      {
        int this_i = size - i;
        int8_t a = this_i >= 0 ? digits.get(this_i).get_first_digit() : 0;
        int8_t b = this_i >= 0 ? digits.get(this_i).get_second_digit() : 0;

        std::string other_a = "";
        for (int j = 1; j <= otherSize; ++j)
        {
          int other_i = otherSize - j;
          int8_t c = other_i >= 0 ? other.digits.get(other_i).get_first_digit() : 0;
          int8_t d = other_i >= 0 ? other.digits.get(other_i).get_second_digit() : 0;

          int8_t second = a * d + carry;
          carry = second / 10;
          second %= 10;

          int8_t first = a * c + carry;
          carry = first / 10;
          first %= 10;

          other_a = std::to_string(first) + std::to_string(second) + other_a;
        }
        other_a = std::to_string(carry) + other_a + std::string((i * 2) - 1, '0');
        carry = 0;

        std::string other_b = "";
        for (int j = 1; j <= otherSize; ++j)
        {
          int other_i = otherSize - j;
          int8_t c = other_i >= 0 ? other.digits.get(other_i).get_first_digit() : 0;
          int8_t d = other_i >= 0 ? other.digits.get(other_i).get_second_digit() : 0;

          int8_t second = b * d + carry;
          carry = second / 10;
          second %= 10;

          int8_t first = b * c + carry;
          carry = first / 10;
          first %= 10;

          other_b = std::to_string(first) + std::to_string(second) + other_b;
        }
        other_b = std::to_string(carry) + other_b + std::string((i - 1) * 2, '0');
        carry = 0;

        result = (BigUInt(other_a) + BigUInt(other_b) + BigUInt(result)).to_string();
      }
      return result;
    };
    BigUInt operator/(const BigUInt &other) const
    {
      if (other == BigUInt("0"))
        throw std::invalid_argument("Division by zero");
      if (*this == BigUInt("0") || *this < other)
        return BigUInt("0");

      BigUInt a = (*this).to_string();
      BigUInt b = other.to_string();
      std::string result;

      int diff = a.length() - b.length();
      for (int i = 0; i <= diff; ++i)
      {
        BigUInt aux(b.to_string() + std::string(diff - i, '0'));
        int8_t count = 0;
        while (a >= aux)
        {
          a = a - aux;
          count++;
        }
        result += std::to_string(count);
      }
      return result;
    }
    BigUInt operator%(const BigUInt &other) const
    {
      BigUInt aux = *this / other;
      BigUInt aux2 = aux * other;
      BigUInt result = *this - aux2;
      return result;
    };
    bool operator==(const BigUInt &other) const
    {
      int size = length();
      int otherSize = other.length();
      if (size != otherSize)
        return false;
      for (int i = 0; i < size; ++i)
      {
        if (digits.get(i) != other.digits.get(i))
          return false;
      }
      return true;
    };
    bool operator!=(const BigUInt &other) const { return !(*this == other); }
    bool operator<(const BigUInt &other) const
    {
      int size = digits.length();
      int otherSize = other.digits.length();
      if (size < otherSize)
        return true;
      if (size > otherSize)
        return false;
      for (int i = 0; i < size; ++i)
      {
        // 246 < 247
        // 02 < 02, 46 < 47
        if (digits.get(i) < other.digits.get(i))
          return true;
        // 246 < 245
        // 02 < 02, 46 > 45
        if (digits.get(i) > other.digits.get(i))
          return false;
      }
      return false;
    };
    bool operator<=(const BigUInt &other) const { return *this < other || *this == other; }
    bool operator>(const BigUInt &other) const { return other < *this; }
    bool operator>=(const BigUInt &other) const { return *this > other || *this == other; }
    bool operator!() const { return *this == BigUInt("0"); }
  };
}