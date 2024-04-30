#include <iostream>

#include "EngRusDict.h"

int main()
{
  TranslationEntry te;
  std::cin >> te;
  if (std::cin.fail())
  {
    std::cin.clear();
    std::cin.ignore(std::numeric_limits< std::streamsize >::max(), '\n');
    std::cout << "'If' worked\n";
  }
  std::cin >> te;
  std::cout << te;

  return 0;
}