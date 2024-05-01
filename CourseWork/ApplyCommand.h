#ifndef APPLYCOMMAND_H
#define APPLYCOMMAND_H

#include "ReadFromFile.h"
#include "MyVector.h"

/*
'If in func' worked
Name of dict: "First" Words: 2:
book: книга, книженька
home: дом

Name of dict: "Second" Words: 2:
bed: кровать
cat: кот, кошара, кошка

Name of dict: "Third" Words: 2:
book: книга, книженька, книжище
home: дом

removeWords First Third
display
Name of dict: "First" Words: 0:


Name of dict: "Second" Words: 2:
bed: кровать
cat: кот, кошара, кошка

Name of dict: "Third" Words: 2:
book: книга, книженька, книжище
home: дом

addWords First Third
display
Name of dict: "First" Words: 2:
book: книга, книженька, книжище
home: дом

Name of dict: "Second" Words: 2:
bed: кровать
cat: кот, кошара, кошка

Name of dict: "Third" Words: 2:
book: книга, книженька, книжище
home: дом

remove Third book книжище
display
Name of dict: "First" Words: 2:
book: книга, книженька, книжище
home: дом

Name of dict: "Second" Words: 2:
bed: кровать
cat: кот, кошара, кошка

Name of dict: "Third" Words: 2:
book: книга, книженька, книжище
home: дом

add Third book книжище
display
Name of dict: "First" Words: 2:
book: книга, книженька, книжище
home: дом

Name of dict: "Second" Words: 2:
bed: кровать
cat: кот, кошара, кошка

Name of dict: "Third" Words: 2:
book: , книга, книженька, книжище
home: дом


*/

void applyCommand(MyVector< EngRusDict >& vector, std::string command)
{
  if (command == "createDict")
  {
    std::string name;
    std::cin >> name;
    for (EngRusDict erd : vector)
    {
      if (erd.getName() == name)
      {
        throw std::runtime_error("Попытка создания двух словарей с одинаковыми названиями");
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
      throw std::runtime_error("Словарь не найден");
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
        std::cin >> key, translation;
        vector[i].addTranslation(key, translation);
        flag = false;
      }
    }
    if (flag)
    {
      throw std::runtime_error("Словарь не найден");
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
        std::cin >> key, translation;
        vector[i].removeTranslation(key, translation);
        flag = false;
      }
    }
    if (flag)
    {
      throw std::runtime_error("Словарь не найден"); // а если key не верный?
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
      throw std::runtime_error("Словарь не найден");
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
      throw std::runtime_error("Словарь не найден");
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
      throw std::runtime_error("Словарь не найден");
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
      throw std::invalid_argument("Словарь не найден");
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
      throw std::runtime_error("Перевода слова не обнаружено");
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
}

#endif // !APPLYCOMMAND_H
