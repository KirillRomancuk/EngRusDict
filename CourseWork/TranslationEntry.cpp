#include "TranslationEntry.h"

#include <sstream>

TranslationEntry::TranslationEntry()
{
}

TranslationEntry::TranslationEntry(const std::string& eng)
{
  std::string lowerEng = getLettersToLower(eng);
  if (!containsOnlyEnglishLetters(lowerEng))
  {
    throw std::invalid_argument("Incorrect word format");
  }
  english_ = lowerEng;
}

TranslationEntry::~TranslationEntry()
{
}

std::string TranslationEntry::getEnglishWord() const
{
  return english_;
}

AVLTree<std::string> TranslationEntry::getTranslations() const
{
    return translations_;
}

size_t TranslationEntry::getCountTranslations() const
{
  return translations_.getCountElements();
}

void TranslationEntry::addTranslation(const std::string& rus)
{
  std::string lowerRus = getLettersToLower(rus);
  if (!containsOnlyRussianLetters(lowerRus))
  {
    throw std::invalid_argument("Incorrect word format");
  }
  translations_.insert(lowerRus);
}

void TranslationEntry::removeTranslation(const std::string& rus)
{
  std::string lowerRus = getLettersToLower(rus);
  if (!containsOnlyRussianLetters(lowerRus))
  {
    throw std::invalid_argument("Incorrect word format");
  }
  translations_.remove(lowerRus);
}

void TranslationEntry::addTranslations(const TranslationEntry& other)
{
  if (english_ != other.english_)
  {
    throw std::invalid_argument("Different english words");
  }
  translations_.addElements(other.translations_);
}

void TranslationEntry::removeTranslations(const TranslationEntry& other)
{
  if (english_ != other.english_)
  {
    throw std::invalid_argument("Different english words");
  }
  translations_.removeElements(other.translations_);
}

TranslationEntry getIntersectionTranslations(const TranslationEntry& te1, const TranslationEntry& te2)
{
  if (te1.english_ != te2.english_)
  {
    throw std::invalid_argument("Different english words");
  }
  TranslationEntry result(te1.english_);
  result.translations_ = getIntersectionTree(te1.translations_, te2.translations_);
  return result;
}

TranslationEntry getDifferenceTranslations(const TranslationEntry& te1, const TranslationEntry& te2)
{
  if (te1.english_ != te2.english_)
  {
    throw std::invalid_argument("Different english words");
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

std::istream& operator>>(std::istream& is, TranslationEntry& te)
{
  std::istream::sentry sentry(is);
  if (!sentry)
  {
    return is;
  }
  try
  {
    std::string eng, rus;
    std::getline(is, eng, ':');
    te = TranslationEntry(eng);
    while (std::getline(is, rus, ',') && !rus.empty())
    {
      rus.erase(0, 1);
      te.addTranslation(rus);
    }
  }
  catch (std::invalid_argument& ex)
  {
    is.setstate(std::ios::failbit);
    te = TranslationEntry();
  }
  return is;
}

bool TranslationEntry::containsOnlyEnglishLetters(const std::string& word)
{
  bool result = true;
  for (char c : word)
  {
    if (!(c >= 'a' && c <= 'z'))
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
    if (!(c >= 'à' && c <= 'ÿ'))
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
