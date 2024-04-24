#include "EngRusDict.h"

EngRusDict::EngRusDict(std::string name) : name_(name) {}

EngRusDict::EngRusDict(EngRusDict&& other) noexcept
{
  name_ = std::move(other.name_);
  words_ = std::move(other.words_);
  other.clear();
}

EngRusDict::~EngRusDict()
{
}

void EngRusDict::clear()
{
  words_.clear();
}

size_t EngRusDict::getCountWords()
{
  return words_.getCountElements();
}

size_t EngRusDict::getCountTranslations(std::string eng)
{
  TranslationEntry te(eng);
  return words_.search(te).getCountTranslations();
}

void EngRusDict::addWord(const TranslationEntry& te)
{
  words_.insert(te);
}

void EngRusDict::removeWord(std::string keyEng)
{
  TranslationEntry te(keyEng);
  words_.remove(te);
}

void EngRusDict::addWordFromEngRusDict(EngRusDict& other)
{
  words_.addElements(other.words_);
}

void EngRusDict::removeWordFromEngRusDict(EngRusDict& other)
{
  words_.removeElements(other.words_);
}

void EngRusDict::display()
{
  std::cout << "Name of dict: \"" << name_ << "\" Words: " << getCountWords() << "\n";
  words_.display("; ");
  std::cout << "\n";
}

EngRusDict getIntersectionWithEngRusDict(std::string name, EngRusDict& erd1, EngRusDict& erd2)
{
  EngRusDict result(name);
  result.words_ = getIntersectionTree(erd1.words_, erd2.words_);
  return result;
}

EngRusDict getDifferenceWithEngRusDict(std::string name, EngRusDict& erd1, EngRusDict& erd2)
{
  EngRusDict result(name);
  result.words_ = getDifferenceTree(erd1.words_, erd2.words_);
  return result;
}
