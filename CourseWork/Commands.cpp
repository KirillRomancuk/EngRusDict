#include "Commands.h"

#include "ReadFromFile.h"

void cmd::createDict(MyVector<EngRusDict>& vector, std::istream& in) {
  std::string name;
  in >> name;
  for (size_t i = 0; i < vector.getSize(); i++) {
    if (vector[i].getName() == name) {
      throw std::runtime_error(
          "������� �������� ���� �������� � ����������� ����������");
    }
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
    throw std::runtime_error("������� �� ������");
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
      } catch (const std::invalid_argument&) {
        TranslationEntry te(key);
        te.addTranslation(translation);
        vector[i].addWord(te);
      }
      flag = false;
    }
  }
  if (flag) {
    throw std::runtime_error("������� �� ������");
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
      } catch (const std::invalid_argument&) {
        throw std::runtime_error("key �� ������");
      }
    }
  }
  if (flag) {
    throw std::runtime_error("������� �� ������");  // � ���� key �� ������?
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
    throw std::runtime_error("������� �� ������");
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
    throw std::runtime_error("������� �� ������");
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
    throw std::runtime_error("������� �� ������");  //
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
    throw std::runtime_error("������� �� ������");
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
    throw std::runtime_error("������� �� ������");
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
    throw std::runtime_error("�������� ����� �� ����������");
  }
  result.display(out);
  out << "\n";
}

void cmd::readDicts(MyVector<EngRusDict>& vector, std::istream& in) {
  std::string pathToFile;
  std::cin >> pathToFile;
  MyVector<EngRusDict> newVector = ReadEngRusDictFromFile(pathToFile);
  for (size_t i = 0; i < newVector.getSize(); i++) {
    vector.push_back(newVector[i]);
  }
}
