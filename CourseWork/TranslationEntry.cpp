#include "TranslationEntry.h"

TranslationEntry::TranslationEntry(const std::string& eng)
{
  if (!containsOnlyEnglishLetters(eng))
  {
    throw std::invalid_argument("");
  }
  english = eng;
}

TranslationEntry::~TranslationEntry()
{
}

void TranslationEntry::addTranslation(const std::string& rus)
{
  if (!containsOnlyRussianLetters(rus))
  {
    throw std::invalid_argument("");
  }
  translations.insert(rus);
}

void TranslationEntry::removeTranslation(const std::string& rus)
{
  translations.remove(rus);
}

bool TranslationEntry::operator<(const TranslationEntry& other) const
{
  return english < other.english;
}

bool TranslationEntry::operator>(const TranslationEntry& other) const
{
  return english > other.english;
}

bool TranslationEntry::operator==(const TranslationEntry& other) const
{
  return english == other.english;
}

void TranslationEntry::addTranslations(const TranslationEntry& other)
{
  if (english != other.english)
  {
    throw std::invalid_argument("");
  }
  translations.addElements(other.translations);
}

void TranslationEntry::removeTranslations(const TranslationEntry& other)
{
  if (english != other.english)
  {
    throw std::invalid_argument("");
  }
  translations.removeElements(other.translations);
}

bool TranslationEntry::containsOnlyEnglishLetters(const std::string& word)
{
  bool result = true;
  for (char c : word)
  {
    if (!((c >= 'A' && c <= 'Z') || (c >= 'a' && c <= 'z')))
    {
      result = false;
      break;
    }
  }
  return result;
}

bool TranslationEntry::containsOnlyRussianLetters(const std::string& word)
{
  bool result = true;
  for (char c : word)
  {
    if (!((c >= 'À' && c <= 'ß') || (c >= 'à' && c <= 'ÿ')))
    {
      result = false;
      break;
    }
  }
  return result;
}

TranslationEntry getIntersectionTranslations(const TranslationEntry& te1, const TranslationEntry& te2)
{
  if (te1.english != te2.english)
  {
    throw std::invalid_argument("");
  }
  TranslationEntry result(te1.english);
  result.translations = getIntersectionTree(te1.translations, te2.translations);
  return result;
}

TranslationEntry getDifferenceTranslations(const TranslationEntry& te1, const TranslationEntry& te2)
{
  if (te1.english != te2.english)
  {
    throw std::invalid_argument("");
  }
  TranslationEntry result(te1.english);
  result.translations = getDifferenceTree(te1.translations, te2.translations);
  return result;
}

std::ostream& operator<<(std::ostream& os, const TranslationEntry& te)
{
  os << te.english << ": " << te.translations;
  return os;
}
