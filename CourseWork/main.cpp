#include <iostream>

#include "ReadFromFile.h"

int main()
{
  setlocale(LC_ALL, "RU");
  MyVector < EngRusDict > EngRusDicts = ReadEngRusDictFromFile("Input.txt");
  
  for (EngRusDict erd : EngRusDicts)
  {
    erd.display();
  }
  return 0;
}