#ifndef APPLYCOMMAND_H
#define APPLYCOMMAND_H

#include <windows.h>

#include "TranslationEntry.h"
#include "ReadFromFile.h"
#include "MyVector.h"

void applyCommand(MyVector< EngRusDict >& vector, std::string command, std::istream& in, std::ostream& out)
{
  if (command == "createDict")
  {
    std::string name;
    std::cin >> name;
    for (EngRusDict erd : vector)
    {
      if (erd.getName() == name)
      {
        throw std::runtime_error("������� �������� ���� �������� � ����������� ����������");
      }
    }
    EngRusDict newErd(name);
    vector.push_back(newErd);
  }
  else if (command == "removeDict")
  {
    std::string name;
    bool flag = true;
    std::cin >> name;
    for (size_t i = 0; i < vector.getSize(); i++)
    {
      if (vector[i].getName() == name)
      {
        vector.erase(i);
        flag = false;
        break;
      }
    }
    if (flag)
    {
      throw std::runtime_error("������� �� ������");
    }
  }
  else if (command == "add")
  {
    std::string name;
    bool flag = true;
    std::cin >> name;
    for (size_t i = 0; i < vector.getSize(); i++)
    {
      if (vector[i].getName() == name)
      {
        std::string key, translation;
        std::cin >> key >> translation;
        try
        {
          vector[i].addTranslation(key, translation);
        }
        catch (const std::invalid_argument&)
        {
          TranslationEntry te(key);
          te.addTranslation(translation);
          vector[i].addWord(te);
        }
        flag = false;
      }
    }
    if (flag)
    {
      throw std::runtime_error("������� �� ������");
    }
  }
  else if (command == "remove")
  {
    std::string name;
    bool flag = true;
    std::cin >> name;
    for (size_t i = 0; i < vector.getSize(); i++)
    {
      if (vector[i].getName() == name)
      {
        std::string key, translation;
        std::cin >> key >> translation;
        flag = false;
        try
        {
          vector[i].removeTranslation(key, translation);
        }
        catch (const std::invalid_argument&)
        {
          std::runtime_error("key �� ������");
        }
      }
    }
    if (flag)
    {
      throw std::runtime_error("������� �� ������"); // � ���� key �� ������?
    }
  }
  else if (command == "addWords")
  {
    std::string nameFirstDict, nameSecondDict;
    bool flag = true;
    std::cin >> nameFirstDict >> nameSecondDict;
    size_t size = vector.getSize();
    for (size_t i = 0; i < size; i++)
    {
      if (vector[i].getName() == nameFirstDict)
      {
        for (size_t j = 0; j < size; j++)
        {
          if (vector[j].getName() == nameSecondDict)
          {
            vector[i].addWordFromEngRusDict(vector[j]);
            flag = false;
          }
        }
      }
    }
    if (flag)
    {
      throw std::runtime_error("������� �� ������");
    }
  }
  else if (command == "removeWords")
  {
    std::string nameFirstDict, nameSecondDict;
    bool flag = true;
    std::cin >> nameFirstDict >> nameSecondDict;
    size_t size = vector.getSize();
    for (size_t i = 0; i < size; i++)
    {
      if (vector[i].getName() == nameFirstDict)
      {
        for (size_t j = 0; j < size; j++)
        {
          if (vector[j].getName() == nameSecondDict)
          {
            vector[i].removeWordFromEngRusDict(vector[j]);
            flag = false;
          }
        }
      }
    }
    if (flag)
    {
      throw std::runtime_error("������� �� ������");
    }
  }
  else if (command == "getIntersection")
  {
    std::string name, nameFirstDict, nameSecondDict;
    bool flag = true;
    std::cin >> name >> nameFirstDict >> nameSecondDict;
    size_t size = vector.getSize();
    for (size_t i = 0; i < size; i++)
    {
      if (vector[i].getName() == nameFirstDict)
      {
        for (size_t j = 0; j < size; j++)
        {
          if (vector[j].getName() == nameSecondDict)
          {
            EngRusDict newErd(getIntersectionWithEngRusDict(name, vector[i], vector[j]));
            vector.push_back(newErd);
            flag = false;
            break;
          }
        }
      }
    }
    if (flag)
    {
      throw std::runtime_error("������� �� ������");
    }
  }
  else if (command == "getDifference")
  {
    std::string name, nameFirstDict, nameSecondDict;
    bool flag = true;
    std::cin >> name >> nameFirstDict >> nameSecondDict;
    size_t size = vector.getSize();
    for (size_t i = 0; i < size; i++)
    {
      if (vector[i].getName() == nameFirstDict)
      {
        for (size_t j = 0; j < size; j++)
        {
          if (vector[j].getName() == nameSecondDict)
          {
            EngRusDict newErd(getDifferenceWithEngRusDict(name, vector[i], vector[j]));
            vector.push_back(newErd);
            flag = false;
          }
        }
      }
    }
    if (flag)
    {
      throw std::runtime_error("������� �� ������");
    }
  }
  else if (command == "clear")
  {
    std::string name;
    std::cin >> name;
    bool flag = true;
    for (size_t i = 0; i < vector.getSize(); i++)
    {
      if (vector[i].getName() == name)
      {
        vector[i].clear();
        flag = false;
      }
    }
    if (flag)
    {
      throw std::invalid_argument("������� �� ������");
    }
  }
  else if (command == "display")
  {
    for (size_t i = 0; i < vector.getSize(); i++)
    {
      vector[i].display();
    }
  }
  else if (command == "getTranslation")
  {
    std::string key;
    std::cin >> key;
    AVLTree< std::string > result;
    for (size_t i = 0; i < vector.getSize(); i++)
    {
      try
      {
        result.addElements(vector[i].getTranslations(key));
      }
      catch (std::invalid_argument& ex)
      {
        continue;
      }
    }
    if (result.getHeight() == 0)
    {
      throw std::runtime_error("�������� ����� �� ����������");
    }
    result.display();
  }
  else if (command == "readDicts")
  {
    std::string pathToFile;
    std::cin >> pathToFile;
    MyVector < EngRusDict > newVector = ReadEngRusDictFromFile(pathToFile);
    for (size_t i = 0; i < newVector.getSize(); i++)
    {
      vector.push_back(newVector[i]);
    }
  }
  else
  {
    throw std::invalid_argument("Incorrect command");
  }
}

#endif // !APPLYCOMMAND_H
