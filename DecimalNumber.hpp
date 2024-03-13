#include <iostream>
#include <string>
#include <variant>
#include "./Util/string.hpp"
#include "./BigInt.hpp"

namespace AGA::ComplexMath
{
  class DecimalNumber
  {
  private:
    std::string m_number;
    std::string m_decimal;
    bool m_negative;

  public:
    DecimalNumber(std::string number)
    {
      m_negative = number[0] == '-';
      if (m_negative)
        number = number.substr(1);
      int dot = number.find('.');
      if (dot == std::string::npos)
      {
        number = AGA::Util::String::removeCharStart(number, '0');
        m_number = number.length() > 0 ? number : "0";
        m_decimal = "0";
      }
      else
      {
        m_number = AGA::Util::String::removeCharStart(number.substr(0, dot), '0');
        m_number = m_number.length() > 0 ? m_number : "0";
        std::string decimal = AGA::Util::String::removeCharEnd(number.substr(dot + 1), '0');
        m_decimal = decimal.length() > 0 ? decimal : "0";
      }
    };
    std::string to_string() const
    {
      std::string value = m_negative ? "-" : "";
      std::string integer = AGA::Util::String::removeCharStart(m_number, '0');
      value += integer.length() > 0 ? integer : "0";
      std::string decimal = AGA::Util::String::removeCharEnd(m_decimal, '0');
      value += decimal.length() > 0 ? "." + decimal : "";
      return value;
    };
    BigInt bigInt(int decimals) const
    {
      std::string str_decimal = m_decimal.length() > decimals
                                    ? m_decimal.substr(0, decimals)
                                    : m_decimal + std::string(decimals - m_decimal.length(), '0');
      return m_number + str_decimal;
    };
    DecimalNumber operator-() const { return DecimalNumber(m_negative ? to_string().substr(1) : "-" + to_string()); };
    DecimalNumber operator-(const DecimalNumber &other) const
    {
      int decimals = std::max(m_decimal.length(), other.m_decimal.length());
      AGA::ComplexMath::BigInt bigInt1 = bigInt(decimals);
      AGA::ComplexMath::BigInt bigInt2 = other.bigInt(decimals);
      AGA::ComplexMath::BigInt result = bigInt1 - bigInt2;

      AGA::ComplexMath::BigInt divisor("1" + std::string(decimals + 100, '0'));
      AGA::ComplexMath::BigInt number = result / divisor;
      AGA::ComplexMath::BigInt decimal = result % divisor;
      std::string value = number.to_string() + "." + decimal.to_string();
      return value;
    };
    DecimalNumber operator+(const DecimalNumber &other) const
    {
      int decimals = std::max(m_decimal.length(), other.m_decimal.length());
      AGA::ComplexMath::BigInt bigInt1 = bigInt(decimals);
      AGA::ComplexMath::BigInt bigInt2 = other.bigInt(decimals);
      AGA::ComplexMath::BigInt result = bigInt1 + bigInt2;

      AGA::ComplexMath::BigInt divisor("1" + std::string(decimals + 100, '0'));
      AGA::ComplexMath::BigInt number = result / divisor;
      AGA::ComplexMath::BigInt decimal = result % divisor;
      std::string value = number.to_string() + "." + decimal.to_string();
      return value;
    };
    DecimalNumber operator*(const DecimalNumber &other) const
    {
      int decimals = std::max(m_decimal.length(), other.m_decimal.length());
      AGA::ComplexMath::BigInt bigInt1 = bigInt(decimals);
      AGA::ComplexMath::BigInt bigInt2 = other.bigInt(decimals);
      AGA::ComplexMath::BigInt result = bigInt1 * bigInt2;

      AGA::ComplexMath::BigInt divisor("1" + std::string(decimals + 100, '0'));
      AGA::ComplexMath::BigInt number = result / divisor;
      AGA::ComplexMath::BigInt decimal = result % divisor;
      std::string value = number.to_string() + "." + decimal.to_string();
      return value;
    };
    DecimalNumber operator/(const DecimalNumber &other) const
    {
      int decimals = std::max(m_decimal.length(), other.m_decimal.length());
      AGA::ComplexMath::BigInt bigInt1 = bigInt(decimals + 100);
      std::cout << "bigIng1: " << bigInt1.to_string() << std::endl;
      AGA::ComplexMath::BigInt bigInt2 = other.bigInt(decimals);
      std::cout << "bigIng2: " << bigInt2.to_string() << std::endl;
      AGA::ComplexMath::BigInt result = bigInt1 / bigInt2;
      std::cout << "result: " << result.to_string() << std::endl;

      AGA::ComplexMath::BigInt divisor("1" + std::string(decimals + 99, '0'));
      std::cout << "divisor: " << divisor.to_string() << std::endl;
      AGA::ComplexMath::BigInt number = result / divisor;
      std::cout << "number: " << number.to_string() << std::endl;
      AGA::ComplexMath::BigInt decimal = result % divisor;
      std::cout << "decimal: " << decimal.to_string() << std::endl;
      std::string value = number.to_string() + "." + decimal.to_string();
      std::cout << "value: " << value << std::endl;
      return value;
    }
    DecimalNumber operator%(const DecimalNumber &other) const
    {
      int decimals = std::max(m_decimal.length(), other.m_decimal.length());
      AGA::ComplexMath::BigInt bigInt1 = bigInt(decimals+100);
      AGA::ComplexMath::BigInt bigInt2 = other.bigInt(decimals);
      AGA::ComplexMath::BigInt result = bigInt1 % bigInt2;

      AGA::ComplexMath::BigInt divisor("1" + std::string(decimals + 100, '0'));
      AGA::ComplexMath::BigInt number = result / divisor;
      AGA::ComplexMath::BigInt decimal = result % divisor;
      std::string value = number.to_string() + "." + decimal.to_string();
      return value;
    };
    bool operator==(const DecimalNumber &other)
    {
      int decimals = std::max(m_decimal.length(), other.m_decimal.length());
      return bigInt(decimals) == other.bigInt(decimals);
    };
    bool operator!=(const DecimalNumber &other) { return !(*this == other); }
    bool operator<(const DecimalNumber &other)
    {
      int decimals = std::max(m_decimal.length(), other.m_decimal.length());
      return bigInt(decimals) < other.bigInt(decimals);
    };
    bool operator<=(const DecimalNumber &other) { return *this < other || *this == other; }
    bool operator>(const DecimalNumber &other)
    {
      int decimals = std::max(m_decimal.length(), other.m_decimal.length());
      return bigInt(decimals) < other.bigInt(decimals);
    };
    bool operator>=(const DecimalNumber &other) { return *this > other || *this == other; }
    bool operator!() { return to_string() == "0"; }
  };
}
