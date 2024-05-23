#include "EngRusDict.h"

#include <functional>

EngRusDict::EngRusDict()
{}

EngRusDict::EngRusDict(const EngRusDict& other)
{
  words_ = other.words_;
}

EngRusDict::EngRusDict(EngRusDict&& other) noexcept
{
  words_ = std::move(other.words_);
  other.clear();
}

EngRusDict::~EngRusDict()
{}

void EngRusDict::clear()
{
  words_.clear();
}

MyVector< std::string > EngRusDict::getTranslations(const std::string& eng) const
{
  try
  {
    return words_.at(eng);
  }
  catch (const std::invalid_argument&)
  {
    return MyVector<std::string>();
  }
}

size_t EngRusDict::getCountWords() const
{
  return words_.size();
}

size_t EngRusDict::getCountTranslations(const std::string& eng) const
{
  try
  {
    return words_.at(eng).getSize();
  }
  catch (const std::invalid_argument&)
  {
    return 0;
  }
}

void EngRusDict::addTranslation(const std::string& eng, const std::string& translation)
{
  if (!words_.contains(eng))
  {
    std::string errorMessege = "Слово \"" + eng + "\" не найдено";
    throw std::invalid_argument(errorMessege);
  }
  if (!containsOnlyRussianLetters(translation))
  {
    throw std::invalid_argument("");
  }
  MyVector< std::string >& translations = words_.at(eng);
  translations.push_back(getLettersToLower(translation));
  std::sort(translations.begin(), translations.end());
}

void EngRusDict::removeTranslation(const std::string& eng, const std::string& translation)
{
  if (!words_.contains(eng))
  {
    std::string errorMessege = "Слово \"" + eng + "\" не найдено";
    throw std::invalid_argument(errorMessege);
  }
  MyVector< std::string >& translations = words_.at(eng);
  translations.erase(translations.findIndexElement(translation));
}

void EngRusDict::addWord(const std::string& eng)
{
  if (!containsOnlyEnglishLetters(eng))
  {
    throw std::invalid_argument("");
  }
  words_.insert(getLettersToLower(eng), MyVector< std::string >());
}

void EngRusDict::removeWord(const std::string& eng)
{
  words_.remove(eng);
}

void EngRusDict::addWordFromEngRusDict(EngRusDict& other)
{
  words_.addElements(other.words_);
}

void EngRusDict::removeWordFromEngRusDict(EngRusDict& other)
{
  words_.removeElements(other.words_);
}

void EngRusDict::display(std::ostream& out) const
{
  words_.display(out, "\n");
  out << "\n";
}

EngRusDict& EngRusDict::operator=(const EngRusDict& other)
{
  if (this != &other)
  {
    words_ = other.words_;
  }
  return *this;
}

EngRusDict getIntersectionWithEngRusDict(EngRusDict& erd1, EngRusDict& erd2)
{
  EngRusDict result;
  result.words_ = getIntersectionTree(erd1.words_, erd2.words_);
  return result;
}

EngRusDict getDifferenceWithEngRusDict(EngRusDict& erd1, EngRusDict& erd2)
{
  EngRusDict result;
  result.words_ = getDifferenceTree(erd1.words_, erd2.words_);
  return result;
}

std::string EngRusDict::getLettersToLower(std::string word)
{
  std::transform(word.begin(), word.end(), word.begin(), std::bind(std::tolower, std::placeholders::_1));
  return word;
}

bool EngRusDict::containsOnlyRussianLetters(const std::string& word) const
{
  bool result = true;
  for (const char& c : word)
  {
    if (!(c >= 'a' && c <= 'я' || c >= 'А' && c <= 'Я'))
    {
      result = false;
      break;
    }
  }
  return result;
}

bool EngRusDict::containsOnlyEnglishLetters(const std::string& word) const
{
  bool result = true;
  for (const char& c : word)
  {
    if (!(c >= 'a' && c <= 'z' || c >= 'A' && c <= 'Z'))
    {
      result = false;
      break;
    }
  }
  return result;
}