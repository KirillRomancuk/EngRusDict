#include <iostream>

#include "ReadFromFile.h"
#include "ApplyCommand.h"

int main()
{
  setlocale(LC_ALL, "RU");
  MyVector < EngRusDict > EngRusDicts = ReadEngRusDictFromFile("Input.txt");
  
  for (EngRusDict erd : EngRusDicts)
  {
    erd.display();
  }
  while (true)
  {
    std::string command;
    std::cin >> command;
    applyCommand(EngRusDicts, command);
  }
  
  return 0;
}