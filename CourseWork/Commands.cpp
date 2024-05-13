#include "Commands.h"

#include "ReadFromFile.h"

void cmd::createDict(MyVector<EngRusDict>& vector, std::istream& in) {
  std::string name;
  in >> name;
  if (subcmd::containsEngRusDict(vector, name)) {
    throw std::runtime_error(
      "Попытка создания двух словарей с одинаковыми названиями");
  }
  EngRusDict newErd(name);
  vector.push_back(newErd);
}

void cmd::removeDict(MyVector<EngRusDict>& vector, std::istream& in) {
  std::string name;
  bool flag = true;
  in >> name;
  for (size_t i = 0; i < vector.getSize(); i++) {
    if (vector[i].getName() == name) {
      vector.erase(i);
      flag = false;
      break;
    }
  }
  if (flag) {
    throw std::runtime_error("Словарь не найден");
  }
}

void cmd::add(MyVector<EngRusDict>& vector, std::istream& in) {
  std::string name;
  bool flag = true;
  in >> name;
  for (size_t i = 0; i < vector.getSize(); i++) {
    if (vector[i].getName() == name) {
      std::string key, translation;
      in >> key >> translation;
      try {
        vector[i].addTranslation(key, translation);
      }
      catch (const std::invalid_argument&) {
        TranslationEntry te(key);
        te.addTranslation(translation);
        vector[i].addWord(te);
      }
      flag = false;
    }
  }
  if (flag) {
    throw std::runtime_error("Словарь не найден");
  }
}

void cmd::remove(MyVector<EngRusDict>& vector, std::istream& in) {
  std::string name;
  bool flag = true;
  in >> name;
  for (size_t i = 0; i < vector.getSize(); i++) {
    if (vector[i].getName() == name) {
      std::string key, translation;
      in >> key >> translation;
      flag = false;
      try {
        vector[i].removeTranslation(key, translation);
      }
      catch (const std::invalid_argument&) {
        throw std::runtime_error("key не найден или не соответствует формату");
      }
    }
  }
  if (flag) {
    throw std::runtime_error("Словарь не найден");
  }
}

void cmd::addWords(MyVector<EngRusDict>& vector, std::istream& in) {
  std::string nameFirstDict, nameSecondDict;
  bool flag = true;
  in >> nameFirstDict >> nameSecondDict;
  size_t size = vector.getSize();
  for (size_t i = 0; i < size; i++) {
    if (vector[i].getName() == nameFirstDict) {
      for (size_t j = 0; j < size; j++) {
        if (vector[j].getName() == nameSecondDict) {
          vector[i].addWordFromEngRusDict(vector[j]);
          flag = false;
        }
      }
    }
  }
  if (flag) {
    throw std::runtime_error("Словарь не найден");
  }
}

void cmd::removeWords(MyVector<EngRusDict>& vector, std::istream& in) {
  std::string nameFirstDict, nameSecondDict;
  bool flag = true;
  in >> nameFirstDict >> nameSecondDict;
  size_t size = vector.getSize();
  for (size_t i = 0; i < size; i++) {
    if (vector[i].getName() == nameFirstDict) {
      for (size_t j = 0; j < size; j++) {
        if (vector[j].getName() == nameSecondDict) {
          vector[i].removeWordFromEngRusDict(vector[j]);
          flag = false;
        }
      }
    }
  }
  if (flag) {
    throw std::runtime_error("Словарь не найден");
  }
}

void cmd::getIntersection(MyVector<EngRusDict>& vector, std::istream& in) {
  std::string name, nameFirstDict, nameSecondDict;
  bool flag = true;
  in >> name >> nameFirstDict >> nameSecondDict;
  size_t size = vector.getSize();
  for (size_t i = 0; i < size; i++) {
    if (vector[i].getName() == nameFirstDict) {
      for (size_t j = 0; j < size; j++) {
        if (vector[j].getName() == nameSecondDict) {
          EngRusDict newErd(
            getIntersectionWithEngRusDict(name, vector[i], vector[j]));
          vector.push_back(newErd);
          flag = false;
          break;
        }
      }
    }
  }
  if (flag) {
    throw std::runtime_error("Оба или один из словарей не найден");
  }
}

void cmd::getDifference(MyVector<EngRusDict>& vector, std::istream& in) {
  std::string name, nameFirstDict, nameSecondDict;
  bool flag = true;
  in >> name >> nameFirstDict >> nameSecondDict;
  size_t size = vector.getSize();
  for (size_t i = 0; i < size; i++) {
    if (vector[i].getName() == nameFirstDict) {
      for (size_t j = 0; j < size; j++) {
        if (vector[j].getName() == nameSecondDict) {
          EngRusDict newErd(
            getDifferenceWithEngRusDict(name, vector[i], vector[j]));
          vector.push_back(newErd);
          flag = false;
        }
      }
    }
  }
  if (flag) {
    throw std::runtime_error("Оба или один из словарей не найден");
  }
}

void cmd::clear(MyVector<EngRusDict>& vector, std::istream& in) {
  std::string name;
  in >> name;
  bool flag = true;
  for (size_t i = 0; i < vector.getSize(); i++) {
    if (vector[i].getName() == name) {
      vector[i].clear();
      flag = false;
    }
  }
  if (flag) {
    throw std::runtime_error("Словарь не найден");
  }
}

void cmd::display(MyVector<EngRusDict>& vector, std::ostream& out) {
  for (size_t i = 0; i < vector.getSize(); i++) {
    vector[i].display(out);
  }
}

void cmd::getTranslation(MyVector<EngRusDict>& vector, std::istream& in,
  std::ostream& out) {
  std::string key;
  std::cin >> key;
  AVLTree<std::string> result;
  for (size_t i = 0; i < vector.getSize(); i++) {
    AVLTree<std::string> tree = vector[i].getTranslations(key);
    if (tree.getHeight() != 0) {
      result.addElements(tree);
    }
  }
  if (result.getHeight() == 0) {
    throw std::runtime_error("Перевода слова не обнаружено");
  }
  result.display(out);
  out << "\n";
}

void cmd::readDicts(MyVector<EngRusDict>& vector, std::istream& in) {
  std::string pathToFile;
  std::cin >> pathToFile;
  MyVector<EngRusDict> newVector = ReadEngRusDictFromFile(pathToFile);
  for (size_t i = 0; i < newVector.getSize(); i++) {
    if (!subcmd::containsEngRusDict(vector, newVector[i].getName())) {
      vector.push_back(newVector[i]);
    }
  }
}

void cmd::help(std::ostream& out)
{
  out << "1. createDict <new dictionary>\n";
  out << "2. removeDict <dictionary>\n";
  out << "3. add <dictionary> <english word> <translation>\n";
  out << "4. remove <dictionary> <english word> <>/<translation>\n";
  out << "5. addWords <dictionaryIn> <dictionaryOut>\n";
  out << "6. getIntersection <new dictionary> <dictionaryOut> <dictionaryOut>\n";
  out << "7. getDifference <new dictionary> <dictionaryOut> <dictionaryOut>\n";
  out << "8. clear <dictionary>\n";
  out << "9. getTranslation <english word>\n";
  out << "10. readDicts <Path to the file>\n";
  out << "11. display <>/<dictionary>\n";
  out << "12. help\n";
}

bool cmd::subcmd::containsEngRusDict(MyVector<EngRusDict>& vector,
  std::string name) {
  for (size_t i = 0; i < vector.getSize(); i++) {
    if (vector[i].getName() == name) {
      return true;
    }
  }
  return false;
}
