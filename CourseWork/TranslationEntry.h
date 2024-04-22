  #ifndef TRANSLATIONENTRY_H
  #define TRANSLATIONENTRY_H

  #include "AVLTree.h"

  struct TranslationEntry
  {
    std::string english;
    AVLTree< std::string > translations;

    TranslationEntry() = delete;
    TranslationEntry(const std::string& eng);
    ~TranslationEntry();

    void addTranslation(const std::string& rus);
    void removeTranslation(const std::string& rus);

    bool operator<(const TranslationEntry& other) const;
    bool operator>(const TranslationEntry& other) const;
    bool operator==(const TranslationEntry& other) const;

    void addTranslations(const TranslationEntry& other);
    void removeTranslations(const TranslationEntry& other);

    friend TranslationEntry getIntersectionTranslations(const TranslationEntry& te1, const TranslationEntry& te2);
    friend TranslationEntry getDifferenceTranslations(const TranslationEntry& te1, const TranslationEntry& te2);
    friend std::ostream& operator<<(std::ostream& os, const TranslationEntry& wp);
  };

  #endif // !TRANSLATIONENTRY_H
