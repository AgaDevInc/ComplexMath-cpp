#include <iostream>
#include "./DecimalNumber.hpp"

int main()
{
  //AGA::ComplexMath::DecimalNumber a("1.5");
  //AGA::ComplexMath::DecimalNumber b("1");
  //std::cout << a.to_string()+" + "+b.to_string()+" = " << (a + b).to_string() << std::endl;
  //std::cout << a.to_string()+" - "+b.to_string()+" = " << (a - b).to_string() << std::endl;
  //std::cout << a.to_string()+" * "+b.to_string()+" = " << (a * b).to_string() << std::endl;
  //std::cout << a.to_string()+" / "+b.to_string()+" = " << (a / b).to_string() << std::endl;
  
  //std::cout << a.to_string()+" % "+b.to_string()+" = " << (a % b).to_string() << std::endl;

  AGA::ComplexMath::BigUInt c("15");
  AGA::ComplexMath::BigUInt d("10");
  std::cout << "c/d: " + (c/d).to_string() << std::endl;
  return 0;
}