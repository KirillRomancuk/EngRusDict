#ifndef ENGRUSDICT_H
#define ENGRUSDICT_H

#include <string>
#include "AVLTree.h"
#include "MyVector.h"

class EngRusDict
{
public:
  EngRusDict();
  EngRusDict(const EngRusDict& other);
  EngRusDict(EngRusDict&& other) noexcept;
  ~EngRusDict();
  void clear();

  MyVector<std::string> getTranslations(const std::string& eng) const;

  size_t getCountWords() const;
  size_t getCountTranslations(const std::string& eng) const;

  void addTranslation(const std::string& eng, const std::string& translation);
  void removeTranslation(const std::string& eng, const std::string& translation);
  void addWord(const std::string& eng);
  void removeWord(const std::string& eng);

  void addWordFromEngRusDict(EngRusDict& other);
  void removeWordFromEngRusDict(EngRusDict& other);

  friend EngRusDict getIntersectionWithEngRusDict(EngRusDict& erd1, EngRusDict& erd2);
  friend EngRusDict getDifferenceWithEngRusDict(EngRusDict& erd1, EngRusDict& erd2);

  void display(std::ostream& out) const;

  EngRusDict& operator=(const EngRusDict& other);

private:
  AVLTree< std::string, MyVector< std::string > > words_;

  std::string getLettersToLower(std::string word);
  bool containsOnlyRussianLetters(const std::string& word) const;
  bool containsOnlyEnglishLetters(const std::string& word) const;
};

#endif  // !ENGRUSDICT_H
