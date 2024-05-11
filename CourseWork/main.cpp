#include <iostream>

#include "ReadFromFile.h"
#include "ApplyCommand.h"

int main()
{
  system("chcp 1251");
  system("cls");
  MyVector < EngRusDict > EngRusDicts = ReadEngRusDictFromFile("Input.txt");
  while (true)
  {
    std::string command;
    std::cin >> command;
    if (command == "exit")
    {
      break;
    }
    try
    {
      applyCommand(EngRusDicts, command, std::cin, std::cout);
    }
    catch (const std::exception&)
    {
      std::cout << "<INVALID COMMAND>\n";
      cleanIStream(std::cin);
    }
  }
  return 0;
}