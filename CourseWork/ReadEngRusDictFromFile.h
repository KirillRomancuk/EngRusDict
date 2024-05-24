#ifndef READENGRUSDICTFROMFILE_H
#define READENGRUSDICTFROMFILE_H

#include <fstream>
#include <sstream>
#include <string>

#include "EngRusDict.h"
#include "MyVector.h"

AVLTree< std::string, EngRusDict > ReadEngRusDictFromFile(std::string pathToFile)
{
  std::ifstream file(pathToFile);
  if (!file.is_open())
  {
    throw std::invalid_argument("�� ������� ������� ����");
  }
  AVLTree< std::string, EngRusDict > EngRusDicts;
  std::string name;
  while (getline(file, name))
  {
    if (EngRusDicts.contains(name))
    {
      throw std::invalid_argument("������� ��� ����� � ������");
    }
    EngRusDict newErd;
    std::string words;
    while (std::getline(file, words) && !words.empty())
    {
      std::stringstream ss(words);
      std::string eng, rus;
      std::getline(ss, eng, ':');
      try
      {
        newErd.addWord(eng);
      }
      catch (const std::invalid_argument&)
      {
        continue;
      }
      try
      {
        while (std::getline(ss, rus, ',') && !rus.empty())
        {
          rus.erase(0, 1);
          newErd.addTranslation(eng, rus);
        }
      }
      catch (const std::invalid_argument&)
      {
        newErd.removeWord(eng);
      }
    }
    EngRusDicts.insert(name, newErd);
  }
  file.close();
  return EngRusDicts;
}

#endif // !READENGRUSDICTFROMFILE_H
