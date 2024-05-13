#ifndef READFROMFILE_H
#define READFROMFILE_H

#include <fstream>
#include <sstream>
#include <string>

#include "EngRusDict.h"
#include "MyVector.h"

MyVector<EngRusDict> ReadEngRusDictFromFile(std::string pathToFile) {
  std::ifstream file(pathToFile);
  if (!file.is_open()) {
    std::cout << "Error opening file" << std::endl;
  }
  MyVector<EngRusDict> EngRusDicts;
  std::string name;
  while (getline(file, name)) {
    EngRusDict newErd(name);
    std::string words;
    while (std::getline(file, words) && !words.empty()) {
      std::stringstream ss(words);
      TranslationEntry te;
      ss >> te;
      if (ss.fail() && !ss.eof()) {
        ss.clear();
        ss.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
      }
      newErd.addWord(te);
    }
    EngRusDicts.push_back(newErd);
  }
  file.close();
  return EngRusDicts;
}

#endif  // !READFROMFILE_H
