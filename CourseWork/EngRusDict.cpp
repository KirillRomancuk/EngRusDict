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
    return MyVector< std::string >();
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
    return words_.at(eng).size();
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
  if (!isOnlyRussianCharacters(translation))
  {
    throw std::invalid_argument("Неверный формат слова");
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
  if (!isOnlyEnglishCharacters(eng))
  {
    throw std::invalid_argument("Неверный формат слова");
  }
  words_.insert(getLettersToLower(eng), MyVector< std::string >());
}

void EngRusDict::removeWord(const std::string& eng)
{
  words_.remove(eng);
}

void EngRusDict::addWordFromEngRusDict(const EngRusDict& other) // Точно ли всё верно?
{
  for (const std::string& key : other.words_.getAllKeys())
  {
    if (words_.contains(key))
    {
      MyVector< std::string >& translations = words_.at(key);
      for (const std::string& translation : other.words_.at(key))
      {
        if (!translations.contains(translation))
        {
          translations.push_back(translation);
        }
      }
      std::sort(translations.begin(), translations.end());
    }
    else
    {
      words_.insert(key, other.words_.at(key));
    }
  }
}

void EngRusDict::removeWordFromEngRusDict(const EngRusDict& other) // Точно ли всё верно?
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

EngRusDict getIntersectionWithEngRusDict(const EngRusDict& erd1, const EngRusDict& erd2)
{
  EngRusDict result;
  for (std::string& key : erd2.words_.getAllKeys())
  {
    if (erd1.words_.contains(key))
    {
      result.addWord(key);
      for (std::string& translation : getIntersectionVector(erd1.words_.at(key), erd2.words_.at(key)))
      {
        result.addTranslation(key, translation);
      }
    }
  }
  return result;
}

EngRusDict getDifferenceWithEngRusDict(const EngRusDict& erd1, const EngRusDict& erd2)
{
  EngRusDict result;
  for (std::string& key : erd2.words_.getAllKeys())
  {
    if (!erd1.words_.contains(key))
    {
      result.addWord(key);
      for (std::string& translation : erd2.words_.at(key))
      {
        result.addTranslation(key, translation);
      }
    }
  }
  for (std::string& key : erd1.words_.getAllKeys())
  {
    if (!erd2.words_.contains(key))
    {
      result.addWord(key);
      for (std::string& translation : erd1.words_.at(key))
      {
        result.addTranslation(key, translation);
      }
    }
  }
  return result;
}

std::string EngRusDict::getLettersToLower(std::string word)
{
  std::transform(word.begin(), word.end(), word.begin(), std::bind(std::tolower, std::placeholders::_1));
  return word;
}

bool EngRusDict::isOnlyEnglishCharacters(const std::string& word) const
{
  for (char letter : word)
  {
    if ((letter < 'a' || letter > 'z') && (letter < 'A' || letter > 'Z'))
    {
      return false;
    }
  }
  return true;
}

bool EngRusDict::isOnlyRussianCharacters(const std::string& word) const
{
  for (char letter : word)
  {
    if ((letter < 'а' || letter > 'я') && (letter < 'А' || letter > 'Я') && letter != 'ё' && letter != 'Ё')
    {
      return false;
    }
  }
  return true;
}
