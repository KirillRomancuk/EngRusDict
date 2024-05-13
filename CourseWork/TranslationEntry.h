#ifndef TRANSLATIONENTRY_H
#define TRANSLATIONENTRY_H

#include "AVLTree.h"

class TranslationEntry {
 public:
  TranslationEntry();
  TranslationEntry(const std::string& eng);
  ~TranslationEntry();

  std::string getEnglishWord() const;
  AVLTree<std::string> getTranslations() const;
  size_t getCountTranslations() const;

  void addTranslation(const std::string& rus);
  void removeTranslation(const std::string& rus);

  void addTranslations(const TranslationEntry& other);
  void removeTranslations(const TranslationEntry& other);

  friend TranslationEntry getIntersectionTranslations(
      const TranslationEntry& te1, const TranslationEntry& te2);
  friend TranslationEntry getDifferenceTranslations(
      const TranslationEntry& te1, const TranslationEntry& te2);

  bool operator<(const TranslationEntry& other) const;
  bool operator>(const TranslationEntry& other) const;
  bool operator==(const TranslationEntry& other) const;

  friend std::ostream& operator<<(std::ostream& os, const TranslationEntry& te);
  friend std::istream& operator>>(std::istream& is, TranslationEntry& te);

 private:
  std::string english_;
  AVLTree<std::string> translations_;

  bool containsOnlyEnglishLetters(const std::string& word);
  bool containsOnlyRussianLetters(const std::string& word);

  std::string getLettersToLower(const std::string& word);
};

#endif  // TRANSLATIONENTRY_H
