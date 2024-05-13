#include "EngRusDict.h"

EngRusDict::EngRusDict() { name_ = ""; }

EngRusDict::EngRusDict(std::string name) : name_(name) {}

EngRusDict::EngRusDict(EngRusDict& other) {
  name_ = other.name_;
  words_ = other.words_;
}

EngRusDict::EngRusDict(EngRusDict&& other) noexcept {
  name_ = std::move(other.name_);
  words_ = std::move(other.words_);
  other.clear();
}

EngRusDict::~EngRusDict() {}

void EngRusDict::clear() { words_.clear(); }

std::string EngRusDict::getName() const { return name_; }

AVLTree<std::string> EngRusDict::getTranslations(std::string eng) const {
  try {
    TranslationEntry te(eng);
    return words_.search(te).getTranslations();
  }
  catch (const std::invalid_argument&) {
    return AVLTree<std::string>();
  }
}

size_t EngRusDict::getCountWords() { return words_.getCountElements(); }

size_t EngRusDict::getCountTranslations(std::string eng) {
  TranslationEntry te(eng);
  return words_.search(te).getCountTranslations();
}

void EngRusDict::addTranslation(std::string eng, std::string translation) {
  TranslationEntry te(eng);
  if (!words_.contains(te)) {
    throw std::invalid_argument("");
  }
  TranslationEntry oldTe = words_.search(te);
  words_.remove(te);
  oldTe.addTranslation(translation);
  words_.insert(oldTe);
}

void EngRusDict::removeTranslation(std::string eng, std::string translation) {
  TranslationEntry te(eng);
  if (!words_.contains(te)) {
    throw std::invalid_argument("");
  }
  TranslationEntry oldTe = words_.search(te);
  words_.remove(te);
  oldTe.removeTranslation(translation);
  words_.insert(oldTe);
}

void EngRusDict::addWord(const TranslationEntry& te) {
  if (te.getEnglishWord() != "") {
    words_.insert(te);
  }
}

void EngRusDict::removeWord(std::string keyEng) {
  TranslationEntry te(keyEng);
  words_.remove(te);
}

void EngRusDict::addWordFromEngRusDict(EngRusDict& other) {
  words_.addElements(other.words_);
}

void EngRusDict::removeWordFromEngRusDict(EngRusDict& other) {
  words_.removeElements(other.words_);
}

void EngRusDict::display(std::ostream& out) {
  out << "Name of dict: \"" << name_ << "\" Words: " << getCountWords()
    << ":\n";
  words_.display(out, "\n");
  out << "\n";
}

EngRusDict& EngRusDict::operator=(const EngRusDict& other) {
  if (this != &other) {
    name_ = other.name_;
    words_ = other.words_;
  }
  return *this;
}

EngRusDict getIntersectionWithEngRusDict(std::string name, EngRusDict& erd1,
  EngRusDict& erd2) {
  EngRusDict result(name);
  result.words_ = getIntersectionTree(erd1.words_, erd2.words_);
  return result;
}

EngRusDict getDifferenceWithEngRusDict(std::string name, EngRusDict& erd1,
  EngRusDict& erd2) {
  EngRusDict result(name);
  result.words_ = getDifferenceTree(erd1.words_, erd2.words_);
  return result;
}
