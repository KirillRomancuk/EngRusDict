#ifndef COMMANDS_H
#define COMMANDS_H

#include "EngRusDict.h"
#include "MyVector.h"

namespace cmd // command
{
  void createDict(AVLTree< std::string, EngRusDict >& NamedEngRusDicts, std::istream& in);
  void removeDict(AVLTree< std::string, EngRusDict >& NamedEngRusDicts, std::istream& in);
  void add(AVLTree< std::string, EngRusDict >& NamedEngRusDicts, std::istream& in);
  void remove(AVLTree< std::string, EngRusDict >& NamedEngRusDicts, std::istream& in);
  void addWords(AVLTree< std::string, EngRusDict >& NamedEngRusDicts, std::istream& in);
  void removeWords(AVLTree< std::string, EngRusDict >& NamedEngRusDicts, std::istream& in);
  void getIntersection(AVLTree< std::string, EngRusDict >& NamedEngRusDicts, std::istream& in);
  void getDifference(AVLTree< std::string, EngRusDict >& NamedEngRusDicts, std::istream& in);
  void clear(AVLTree< std::string, EngRusDict >& NamedEngRusDicts, std::istream& in);
  void display(AVLTree< std::string, EngRusDict >& NamedEngRusDicts, std::istream& in, std::ostream& out);
  void getTranslation(AVLTree< std::string, EngRusDict >& NamedEngRusDicts, std::istream& in, std::ostream& out);
  void readDicts(AVLTree< std::string, EngRusDict >& NamedEngRusDicts, std::istream& in);
  void help(std::ostream& out);
} // namespace cmd

#endif // !COMMANDS_H
