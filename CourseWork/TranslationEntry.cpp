#include "TranslationEntry.h"

TranslationEntry::TranslationEntry(const std::string& eng)
{
  if (!containsOnlyEnglishLetters(eng))
  {
    throw std::invalid_argument("");
  }
  english_ = eng;
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
  translations_.insert(rus);
}

void TranslationEntry::removeTranslation(const std::string& rus)
{
  translations_.remove(rus);
}

void TranslationEntry::addTranslations(const TranslationEntry& other)
{
  if (english_ != other.english_)
  {
    throw std::invalid_argument("");
  }
  translations_.addElements(other.translations_);
}

void TranslationEntry::removeTranslations(const TranslationEntry& other)
{
  if (english_ != other.english_)
  {
    throw std::invalid_argument("");
  }
  translations_.removeElements(other.translations_);
}

TranslationEntry getIntersectionTranslations(const TranslationEntry& te1, const TranslationEntry& te2)
{
  if (te1.english_ != te2.english_)
  {
    throw std::invalid_argument("");
  }
  TranslationEntry result(te1.english_);
  result.translations_ = getIntersectionTree(te1.translations_, te2.translations_);
  return result;
}

TranslationEntry getDifferenceTranslations(const TranslationEntry& te1, const TranslationEntry& te2)
{
  if (te1.english_ != te2.english_)
  {
    throw std::invalid_argument("");
  }
  TranslationEntry result(te1.english_);
  result.translations_ = getDifferenceTree(te1.translations_, te2.translations_);
  return result;
}

bool TranslationEntry::operator<(const TranslationEntry& other) const
{
  return english_ < other.english_;
}

bool TranslationEntry::operator>(const TranslationEntry& other) const
{
  return english_ > other.english_;
}

bool TranslationEntry::operator==(const TranslationEntry& other) const
{
  return english_ == other.english_;
}

std::ostream& operator<<(std::ostream& os, const TranslationEntry& te)
{
  os << te.english_ << ": " << te.translations_;
  return os;
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

std::string TranslationEntry::getLettersToLower(const std::string& word)
{
  std::string result;
  for (char c : word)
  {
    result += std::tolower(c);
  }
  return result;
}
