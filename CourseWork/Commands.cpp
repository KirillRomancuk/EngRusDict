#include "Commands.h"

#include "ReadEngRusDictFromFile.h"

void cmd::createDict(AVLTree< std::string, EngRusDict >& NamedEngRusDicts, std::istream& in)
{
  std::string name;
  in >> name;
  if (name == "ALL")
  {
    throw std::invalid_argument("������ ������� ������� � ������ \"ALL\"");
  }
  if (NamedEngRusDicts.contains(name))
  {
    throw std::runtime_error("������� �������� ���� �������� � ����������� ����������");
  }
  EngRusDict newErd;
  NamedEngRusDicts.INSERT(name, newErd);
}

void cmd::removeDict(AVLTree< std::string, EngRusDict >& NamedEngRusDicts, std::istream& in)
{
  std::string name;
  in >> name;
  if (!NamedEngRusDicts.contains(name))
  {
    throw std::runtime_error("������� �������� ������� � ����������� ����������");
  }
  NamedEngRusDicts.DELETE(name);
}

void cmd::add(AVLTree< std::string, EngRusDict >& NamedEngRusDicts, std::istream& in)
{
  std::string name;
  bool flag = true;
  in >> name;
  std::string key, translation;
  in >> key >> translation;
  try
  {
    NamedEngRusDicts.SEARCH(name).addTranslation(key, translation);
  }
  catch (const std::invalid_argument&)
  {
    EngRusDict& erd = NamedEngRusDicts.SEARCH(name);
    erd.addWord(key);
    erd.addTranslation(key, translation);
  }
}

void cmd::remove(AVLTree< std::string, EngRusDict >& NamedEngRusDicts, std::istream& in)
{
  std::string name;
  bool flag = true;
  in >> name;
  std::string key, translation;
  in >> key >> translation;
  if (translation == "ALL")
  {
    NamedEngRusDicts.SEARCH(name).removeWord(key);
  }
  else
  {
    try
    {
      NamedEngRusDicts.SEARCH(name).removeTranslation(key, translation);
    }
    catch (const std::invalid_argument&)
    {
      throw std::runtime_error("key �� ������ ��� �� ������������� �������");
    }
  }
}

void cmd::addWords(AVLTree< std::string, EngRusDict >& NamedEngRusDicts, std::istream& in)
{
  std::string nameFirstDict, nameSecondDict;
  in >> nameFirstDict >> nameSecondDict;
  NamedEngRusDicts.SEARCH(nameFirstDict).addWordFromEngRusDict(NamedEngRusDicts.SEARCH(nameSecondDict));
}

void cmd::removeWords(AVLTree< std::string, EngRusDict >& NamedEngRusDicts, std::istream& in)
{
  std::string nameFirstDict, nameSecondDict;
  in >> nameFirstDict >> nameSecondDict;
  NamedEngRusDicts.SEARCH(nameFirstDict).removeWordFromEngRusDict(NamedEngRusDicts.SEARCH(nameSecondDict));
}

void cmd::getIntersection(AVLTree< std::string, EngRusDict >& NamedEngRusDicts, std::istream& in)
{
  std::string name, nameFirstDict, nameSecondDict;
  in >> name;
  if (NamedEngRusDicts.contains(name))
  {
    throw std::runtime_error("������� �������� ���� �������� � ����������� ����������");
  }
  in >> nameFirstDict >> nameSecondDict;
  NamedEngRusDicts.INSERT(
    name, getIntersectionWithEngRusDict(NamedEngRusDicts.SEARCH(nameFirstDict), NamedEngRusDicts.SEARCH(nameSecondDict))
  );
}

void cmd::getDifference(AVLTree< std::string, EngRusDict >& NamedEngRusDicts, std::istream& in)
{
  std::string name, nameFirstDict, nameSecondDict;
  in >> name;
  if (NamedEngRusDicts.contains(name))
  {
    throw std::runtime_error("������� �������� ���� �������� � ����������� ����������");
  }
  in >> nameFirstDict >> nameSecondDict;
  NamedEngRusDicts.INSERT(
    name, getDifferenceWithEngRusDict(NamedEngRusDicts.SEARCH(nameFirstDict), NamedEngRusDicts.SEARCH(nameSecondDict))
  );
}

void cmd::clear(AVLTree< std::string, EngRusDict >& NamedEngRusDicts, std::istream& in)
{
  std::string name;
  in >> name;
  NamedEngRusDicts.SEARCH(name).clear();
}

void cmd::display(AVLTree< std::string, EngRusDict >& NamedEngRusDicts, std::istream& in, std::ostream& out)
{
  std::string name;
  in >> name;
  if (name == "ALL")
  {
    for (const std::string& key : NamedEngRusDicts.getAllKeys())
    {
      out << "Dictionary Name: \"" << key << "\"  Words: " << NamedEngRusDicts.SEARCH(key).getCountWords() << ":\n";
      NamedEngRusDicts.SEARCH(key).display(out);
    }
  }
  else
  {
    NamedEngRusDicts.SEARCH(name).display(out);
  }
}

void cmd::getTranslation(AVLTree< std::string, EngRusDict >& NamedEngRusDicts, std::istream& in, std::ostream& out)
{
  std::string key;
  std::cin >> key;
  MyVector< std::string > result;
  for (const std::string& name : NamedEngRusDicts.getAllKeys())
  {
    for (const std::string& translation : NamedEngRusDicts.SEARCH(name).getTranslations(key))
    {
      if (translation != "" && !result.contains(translation))
      {
        result.push_back(translation);
      }
    }
  }
  if (result.size() == 0)
  {
    throw std::runtime_error("�������� ����� �� �����������");
  }
  std::copy(result.begin(), result.end(), std::ostream_iterator< std::string >(out, "\n"));
}

void cmd::readDicts(AVLTree< std::string, EngRusDict >& NamedEngRusDicts, std::istream& in)
{
  std::string pathToFile;
  std::cin >> pathToFile;
  NamedEngRusDicts.addElements(ReadEngRusDictFromFile(pathToFile));
}

void cmd::help(std::ostream& out)
{
  out << "1. createDict <new dictionary>\n";
  out << "2. removeDict <dictionary>\n";
  out << "3. add <dictionary> <english word> <translation>\n";
  out << "4. remove <dictionary> <english word> <ALL>/<translation>\n";
  out << "5. addWords <dictionaryIn> <dictionaryOut>\n";
  out << "6. removeWords <dictionaryIn> <dictionaryOut>\n";
  out << "7. getIntersection <new dictionary> <dictionaryOut> "
         "<dictionaryOut>\n";
  out << "8. getDifference <new dictionary> <dictionaryOut> <dictionaryOut>\n";
  out << "9. clear <dictionary>\n";
  out << "10. getTranslation <english word>\n";
  out << "11. readDicts <Path to the file>\n";
  out << "12. display <ALL>/<dictionary>\n";
  out << "13. help\n";
}
