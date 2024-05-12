#ifndef COMMANDS_H
#define COMMANDS_H

#include "EngRusDict.h"
#include "MyVector.h"

namespace cmd // command
{
  void createDict(MyVector< EngRusDict >& vector, std::istream& in);
  void removeDict(MyVector< EngRusDict >& vector, std::istream& in);
  void add(MyVector< EngRusDict >& vector, std::istream& in);
  void remove(MyVector< EngRusDict >& vector, std::istream& in);
  void addWords(MyVector< EngRusDict >& vector, std::istream& in);
  void removeWords(MyVector< EngRusDict >& vector, std::istream& in);
  void getIntersection(MyVector< EngRusDict >& vector, std::istream& in);
  void getDifference(MyVector< EngRusDict >& vector, std::istream& in);
  void clear(MyVector< EngRusDict >& vector, std::istream& in);
  void display(MyVector< EngRusDict >& vector, std::ostream& out);
  void getTranslation(MyVector< EngRusDict >& vector, std::istream& in, std::ostream& out);
  void readDicts(MyVector< EngRusDict >& vector, std::istream& in);
}


#endif // !COMMANDS_H