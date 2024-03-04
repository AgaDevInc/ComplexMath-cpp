#include <iostream>
#include <string>
#include <variant>
#include "./BigInt.hpp"
#include "./util.hpp"

namespace AGA
{
  using number = std::variant<int, double, float>;
  class DecimalNumber
  {
  private:
    std::string m_number;
    std::string m_decimal;
    bool m_negative;

  public:
    DecimalNumber(std::string number);
    DecimalNumber(number number);
    std::string to_string();
    void print();
    BigInt bigInt(int decimals) const;
    DecimalNumber operator-() { return DecimalNumber(m_negative ? to_string().substr(1) : "-" + to_string()); };
    DecimalNumber operator-(const DecimalNumber &other);
    DecimalNumber operator+(const DecimalNumber &other);
    DecimalNumber operator*(const DecimalNumber &other);
    DecimalNumber operator/(const DecimalNumber &other);
    DecimalNumber operator%(const DecimalNumber &other);
    DecimalNumber operator-(const number &other);
    DecimalNumber operator+(const number &other);
    DecimalNumber operator*(const number &other);
    DecimalNumber operator/(const number &other);
    DecimalNumber operator%(const number &other);
    bool operator==(const DecimalNumber &other);
    bool operator!=(const DecimalNumber &other) { return !(*this == other); }
    bool operator<(const DecimalNumber &other);
    bool operator<=(const DecimalNumber &other) { return *this < other || *this == other; }
    bool operator>(const DecimalNumber &other);
    bool operator>=(const DecimalNumber &other) { return *this > other || *this == other; }
    bool operator!() { return BigInt(0) == 0; }
  };
}

AGA::DecimalNumber::DecimalNumber(std::string number)
{
  m_negative = number[0] == '-';
  if (m_negative)
    number = number.substr(1);
  int dot = number.find('.');
  if (dot == std::string::npos)
  {
    number = AGA::Util::removeCharStart(number, '0');
    m_number = number.length() > 0 ? number : "0";
    m_decimal = "0";
  }
  else
  {
    m_number = AGA::Util::removeCharStart(number.substr(0, dot), '0');
    m_number = m_number.length() > 0 ? m_number : "0";
    std::string decimal = AGA::Util::removeCharEnd(number.substr(dot + 1), '0');
    m_decimal = decimal.length() > 0 ? decimal : "0";
  }
}
AGA::DecimalNumber::DecimalNumber(number number)
{
  if (std::holds_alternative<int>(number))
    *this = DecimalNumber(std::to_string(std::get<int>(number)));
  if (std::holds_alternative<double>(number))
    *this = DecimalNumber(std::to_string(std::get<double>(number)));
  if (std::holds_alternative<float>(number))
    *this = DecimalNumber(std::to_string(std::get<float>(number)));
}
std::string AGA::DecimalNumber::to_string()
{
  std::string value = m_negative ? "-" : "";
  value += m_number;
  int decimal = m_decimal.length() > 0 ? std::stoi(m_decimal) : 0;
  if (decimal > 0)
    value += "." + (m_decimal);
  return value;
}
void AGA::DecimalNumber::print()
{
  std::cout << to_string() << std::endl;
}
AGA::BigInt AGA::DecimalNumber::bigInt(int decimals) const
{
  AGA::BigInt result = AGA::BigInt(m_number);
  for (int i = 0; i < decimals; i++)
  {
    result *= 10;
  }
  result += std::stoi(m_decimal);
  if (m_negative)
    result *= -1;
  return result;
}

AGA::DecimalNumber AGA::DecimalNumber::operator-(const AGA::DecimalNumber &other)
{
  int decimals = std::max(m_decimal.length(), other.m_decimal.length());
  AGA::BigInt bigInt1 = bigInt(decimals);
  AGA::BigInt bigInt2 = other.bigInt(decimals);
  AGA::BigInt result = bigInt1 - bigInt2;

  int divisor = (decimals+100) * 10;
  AGA::BigInt number = result / divisor;
  AGA::BigInt decimal = result % divisor;
  std::string value = number.str() + "." + decimal.str();
  return DecimalNumber(value);
}
AGA::DecimalNumber AGA::DecimalNumber::operator+(const AGA::DecimalNumber &other)
{
  int decimals = std::max(m_decimal.length(), other.m_decimal.length());
  AGA::BigInt bigInt1 = bigInt(decimals);
  AGA::BigInt bigInt2 = other.bigInt(decimals);
  AGA::BigInt result = bigInt1 + bigInt2;

  int divisor = (decimals+100) * 10;
  AGA::BigInt number = result / divisor;
  AGA::BigInt decimal = result % divisor;
  std::string value = number.str() + "." + decimal.str();
  return DecimalNumber(value);
}
AGA::DecimalNumber AGA::DecimalNumber::operator*(const AGA::DecimalNumber &other)
{
  int decimals = std::max(m_decimal.length(), other.m_decimal.length());
  AGA::BigInt bigInt1 = bigInt(decimals);
  AGA::BigInt bigInt2 = other.bigInt(decimals);
  AGA::BigInt result = bigInt1 * bigInt2;

  int divisor = (decimals+100) * 10;
  AGA::BigInt number = result / divisor;
  AGA::BigInt decimal = result % divisor;
  std::string value = number.str() + "." + decimal.str();
  return DecimalNumber(value);
}
AGA::DecimalNumber AGA::DecimalNumber::operator/(const AGA::DecimalNumber &other)
{
  int decimals = std::max(m_decimal.length(), other.m_decimal.length());
  AGA::BigInt bigInt1 = bigInt(decimals+100);
  AGA::BigInt bigInt2 = other.bigInt(decimals);
  AGA::BigInt result = bigInt1 / bigInt2;

  AGA::BigInt divisor = AGA::BigInt("1" + std::string(decimals+100, '0'));
  std::cout << "divisor: " << divisor << std::endl;
  AGA::BigInt number = result / divisor;
  AGA::BigInt decimal = result % divisor;
  std::string value = number.str() + "." + decimal.str();
  return DecimalNumber(value);
}
AGA::DecimalNumber AGA::DecimalNumber::operator%(const AGA::DecimalNumber &other)
{
  int decimals = std::max(m_decimal.length(), other.m_decimal.length());
  AGA::BigInt bigInt1 = bigInt(decimals);
  AGA::BigInt bigInt2 = other.bigInt(decimals);
  AGA::BigInt result = bigInt1 % bigInt2;

  int divisor = (decimals+100) * 10;
  AGA::BigInt number = result / divisor;
  AGA::BigInt decimal = result % divisor;
  std::string value = number.str() + "." + decimal.str();
  return DecimalNumber(value);
}
AGA::DecimalNumber AGA::DecimalNumber::operator-(const number &other)
{
  return *this - DecimalNumber(other);
}
AGA::DecimalNumber AGA::DecimalNumber::operator+(const number &other)
{
  return *this + DecimalNumber(other);
}
AGA::DecimalNumber AGA::DecimalNumber::operator*(const number &other)
{
  return *this * DecimalNumber(other);
}
AGA::DecimalNumber AGA::DecimalNumber::operator/(const number &other)
{
  return *this / DecimalNumber(other);
}
AGA::DecimalNumber AGA::DecimalNumber::operator%(const number &other)
{
  return *this % DecimalNumber(other);
}
bool AGA::DecimalNumber::operator==(const AGA::DecimalNumber &other)
{
  int decimals = std::max(m_decimal.length(), other.m_decimal.length());
  return bigInt(decimals) == other.bigInt(decimals);
}
bool AGA::DecimalNumber::operator<(const AGA::DecimalNumber &other)
{
  int decimals = std::max(m_decimal.length(), other.m_decimal.length());
  return bigInt(decimals) < other.bigInt(decimals);
}
bool AGA::DecimalNumber::operator>(const AGA::DecimalNumber &other)
{
  int decimals = std::max(m_decimal.length(), other.m_decimal.length());
  return bigInt(decimals) > other.bigInt(decimals);
}