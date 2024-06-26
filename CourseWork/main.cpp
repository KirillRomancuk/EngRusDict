﻿#include <functional>
#include <iostream>
#include <map>

#include "Commands.h"

void invalidCommand()
{
  std::cout << "<INVALID COMMAND>\n";
  std::cin.clear();
  std::cin.ignore(std::numeric_limits< std::streamsize >::max(), '\n');
}

namespace mapCommands
{
  using mapCmd = std::map< std::string, std::function< void(std::istream&, std::ostream&) > >;
  mapCmd createMapOfCommands(AVLTree< std::string, EngRusDict >& NamedEngRusDicts, std::istream& in, std::ostream& out)
  {
    mapCmd commands;
    using namespace std::placeholders;
    commands["createDict"] = std::bind(cmd::createDict, std::ref(NamedEngRusDicts), _1);
    commands["removeDict"] = std::bind(cmd::removeDict, std::ref(NamedEngRusDicts), _1);
    commands["add"] = std::bind(cmd::add, std::ref(NamedEngRusDicts), _1);
    commands["remove"] = std::bind(cmd::remove, std::ref(NamedEngRusDicts), _1);
    commands["addWords"] = std::bind(cmd::addWords, std::ref(NamedEngRusDicts), _1);
    commands["removeWords"] = std::bind(cmd::removeWords, std::ref(NamedEngRusDicts), _1);
    commands["getIntersection"] = std::bind(cmd::getIntersection, std::ref(NamedEngRusDicts), _1);
    commands["getDifference"] = std::bind(cmd::getDifference, std::ref(NamedEngRusDicts), _1);
    commands["clear"] = std::bind(cmd::clear, std::ref(NamedEngRusDicts), _1);
    commands["getTranslation"] = std::bind(cmd::getTranslation, std::ref(NamedEngRusDicts), _1, _2);
    commands["readDicts"] = std::bind(cmd::readDicts, std::ref(NamedEngRusDicts), _1);
    commands["display"] = std::bind(cmd::display, std::ref(NamedEngRusDicts), _1, _2);
    commands["help"] = std::bind(cmd::help, _2);
    commands["1"] = std::bind(cmd::createDict, std::ref(NamedEngRusDicts), _1);
    commands["2"] = std::bind(cmd::removeDict, std::ref(NamedEngRusDicts), _1);
    commands["3"] = std::bind(cmd::add, std::ref(NamedEngRusDicts), _1);
    commands["4"] = std::bind(cmd::remove, std::ref(NamedEngRusDicts), _1);
    commands["5"] = std::bind(cmd::addWords, std::ref(NamedEngRusDicts), _1);
    commands["6"] = std::bind(cmd::removeWords, std::ref(NamedEngRusDicts), _1);
    commands["7"] = std::bind(cmd::getIntersection, std::ref(NamedEngRusDicts), _1);
    commands["8"] = std::bind(cmd::getDifference, std::ref(NamedEngRusDicts), _1);
    commands["9"] = std::bind(cmd::clear, std::ref(NamedEngRusDicts), _1);
    commands["10"] = std::bind(cmd::getTranslation, std::ref(NamedEngRusDicts), _1, _2);
    commands["11"] = std::bind(cmd::readDicts, std::ref(NamedEngRusDicts), _1);
    commands["12"] = std::bind(cmd::display, std::ref(NamedEngRusDicts), _1, _2);
    commands["13"] = std::bind(cmd::help, _2);
    return commands;
  }
} // namespace mapCommands

int main()
{
  system("chcp 1251");
  system("cls");
  AVLTree< std::string, EngRusDict > NamedEngRusDicts;
  std::map< std::string, std::function< void(std::istream&, std::ostream&) > > commands;
  commands = mapCommands::createMapOfCommands(NamedEngRusDicts, std::cin, std::cout);
  commands["help"](std::cin, std::cout);
  while (true)
  {
    std::string command;
    std::cin >> command;
    if (std::cin.eof())
    {
      break;
    }
    try
    {
      commands.at(command)(std::cin, std::cout);
    }
    catch (const std::out_of_range&)
    {
      invalidCommand();
    }
    catch (const std::runtime_error&)
    {
      invalidCommand();
    }
    catch (const std::invalid_argument&)
    {
      invalidCommand();
    }
  }
  return 0;
}
