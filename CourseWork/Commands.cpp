#include "Commands.h"

#include "ReadFromFile.h"

void cmd::createDict(AVLTree< std::string, EngRusDict >& vector, std::istream& in)
{
  std::string name;
  in >> name;
  if (vector.contains(name))
  {
    throw std::runtime_error("Попытка создания двух словарей с одинаковыми названиями");
  }
  EngRusDict newErd;
  vector.insert(name, newErd);
}

void cmd::removeDict(AVLTree< std::string, EngRusDict >& vector, std::istream& in)
{
  std::string name;
  in >> name;
  if (!vector.contains(name))
  {
    throw std::runtime_error("Попытка удаления словаря с одинаковыми названиями");
  }
  vector.remove(name);
}

void cmd::add(AVLTree< std::string, EngRusDict >& vector, std::istream& in)
{
  std::string name;
  bool flag = true;
  in >> name;
  std::string key, translation;
  in >> key >> translation;
  try
  {
    vector.at(name).addTranslation(key, translation);
  }
  catch (const std::invalid_argument&)
  {
    EngRusDict& erd = vector.at(name);
    erd.addWord(key);
    erd.addTranslation(key, translation);
  }
}

void cmd::remove(AVLTree< std::string, EngRusDict >& vector, std::istream& in)
{
  std::string name;
  bool flag = true;
  in >> name;
  std::string key, translation;
  in >> key >> translation;
  if (translation == "ALL")
  {
    vector.at(name).removeWord(key);
  }
  else
  {
    try
    {
      vector.at(name).removeTranslation(key, translation);
    }
    catch (const std::invalid_argument&)
    {
      throw std::runtime_error("key не найден или не соответствует формату");
    }
  }
}

void cmd::addWords(AVLTree< std::string, EngRusDict >& vector, std::istream& in)
{
  std::string nameFirstDict, nameSecondDict;
  in >> nameFirstDict >> nameSecondDict;
  vector.at(nameFirstDict).addWordFromEngRusDict(vector.at(nameSecondDict));
}

void cmd::removeWords(AVLTree< std::string, EngRusDict >& vector, std::istream& in)
{
  std::string nameFirstDict, nameSecondDict;
  in >> nameFirstDict >> nameSecondDict;
  vector.at(nameFirstDict).removeWordFromEngRusDict(vector.at(nameSecondDict));
}

void cmd::getIntersection(AVLTree< std::string, EngRusDict >& vector, std::istream& in)
{
  std::string name, nameFirstDict, nameSecondDict;
  in >> name;
  if (vector.contains(name))
  {
    throw std::runtime_error("Попытка создания двух словарей с одинаковыми названиями");
  }
  in >> nameFirstDict >> nameSecondDict;
  vector.insert(name, getIntersectionWithEngRusDict(vector.at(nameFirstDict), vector.at(nameSecondDict)));
}

void cmd::getDifference(AVLTree< std::string, EngRusDict >& vector, std::istream& in)
{
  std::string name, nameFirstDict, nameSecondDict;
  in >> name;
  if (vector.contains(name))
  {
    throw std::runtime_error("Попытка создания двух словарей с одинаковыми названиями");
  }
  in >> nameFirstDict >> nameSecondDict;
  vector.insert(name, getDifferenceWithEngRusDict(vector.at(nameFirstDict), vector.at(nameSecondDict)));
}

void cmd::clear(AVLTree< std::string, EngRusDict >& vector, std::istream& in)
{
  std::string name;
  in >> name;
  vector.at(name).clear();
}

void cmd::display(AVLTree< std::string, EngRusDict >& vector, std::istream& in, std::ostream& out)
{
  std::string name;
  in >> name;
  if (name == "ALL")
  {
    for (const std::string& key : vector.getAllKeys())
    {
      out << "Name: \"" << key << "\"\tWords: " << vector.at(key).getCountWords() << ":\n";
      vector.at(key).display(out);
    }
  }
  else
  {
    vector.at(name).display(out);
  }
}

void cmd::getTranslation(AVLTree< std::string, EngRusDict >& vector, std::istream& in, std::ostream& out)
{
  std::string key;
  std::cin >> key;
  MyVector <std::string> result;
  for (const std::string& name : vector.getAllKeys())
  {
    for (const std::string& translation : vector.at(name).getTranslations(key))
    {
      if (translation != "" && std::find(result.begin(), result.end(), translation) == result.end())
      {
        result.push_back(translation);
      }
    }
  }
  if (result.getSize() == 0)
  {
    throw std::runtime_error("");
  }
  std::copy(result.begin(), result.end(), std::ostream_iterator< std::string >(out, "\n"));
}

void cmd::readDicts(AVLTree< std::string, EngRusDict >& vector, std::istream& in)
{
  std::string pathToFile;
  std::cin >> pathToFile;
  vector.addElements(ReadEngRusDictFromFile(pathToFile));
}

void cmd::help(std::ostream& out)
{
  out << "1 - createDict <new dictionary>\n";
  out << "2 - removeDict <dictionary>\n";
  out << "3 - add <dictionary> <english word> <translation>\n";
  out << "4 - remove <dictionary> <english word> <ALL>/<translation>\n";
  out << "5 - addWords <dictionaryIn> <dictionaryOut>\n";
  out << "6 - removeWords <dictionaryIn> <dictionaryOut>\n";
  out << "7 - getIntersection <new dictionary> <dictionaryOut> "
         "<dictionaryOut>\n";
  out << "8 - getDifference <new dictionary> <dictionaryOut> <dictionaryOut>\n";
  out << "9 - clear <dictionary>\n";
  out << "10 - getTranslation <english word>\n";
  out << "11 - readDicts <Path to the file>\n";
  out << "12 - display <ALL>/<dictionary>\n";
  out << "13 - help\n";
}
