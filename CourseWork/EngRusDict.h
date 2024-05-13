#ifndef ENGRUSDICT_H
#define ENGRUSDICT_H

#include "TranslationEntry.h"

class EngRusDict
{
public:
	EngRusDict() = delete;
	EngRusDict(std::string name);
	EngRusDict(EngRusDict& other) = delete;
	EngRusDict(EngRusDict&& other) noexcept;
	~EngRusDict();
	void clear();

	size_t getCountWords();
	size_t getCountTranslations(std::string eng);

	void addWord(const TranslationEntry& wp);
	void removeWord(std::string keyEng);

	void addWordFromEngRusDict(EngRusDict& other);
	void removeWordFromEngRusDict(EngRusDict& other);

	friend EngRusDict getIntersectionWithEngRusDict(std::string name, EngRusDict& erd1, EngRusDict& erd2);
	friend EngRusDict getDifferenceWithEngRusDict(std::string name, EngRusDict& erd1, EngRusDict& erd2);

	void display();

private:
  std::string name_;
  AVLTree< TranslationEntry > words_;
};

#endif // !ENGRUSDICT_H
