#include <iostream>
#include "./BigInt.hpp"

int main()
{
  std::string s = "1";
  AGA::BigInt x(s);

  std::cout << "string: " << s << ", size: " << sizeof(s) << "bytes" << std::endl;
  std::cout <<  "BigInt: " << x.to_string() << ", size: " << sizeof(x) << "bytes" << std::endl;
  return 0;
}