#ifndef ENGRUSDICT_H
#define ENGRUSDICT_H

#include "TranslationEntry.h"

class EngRusDict
{
public:
	EngRusDict();
	EngRusDict(std::string name);
	EngRusDict(EngRusDict& other);
	EngRusDict(EngRusDict&& other) noexcept;
	~EngRusDict();
	void clear();

	std::string getName() const;
	AVLTree< std::string > getTranslations(std::string eng) const;

	size_t getCountWords();
	size_t getCountTranslations(std::string eng);

	void addTranslation(std::string eng, std::string translation);
	void removeTranslation(std::string eng, std::string translation);
	void addWord(const TranslationEntry& wp);
	void removeWord(std::string keyEng);

	void addWordFromEngRusDict(EngRusDict& other);
	void removeWordFromEngRusDict(EngRusDict& other);

	friend EngRusDict getIntersectionWithEngRusDict(std::string name, EngRusDict& erd1, EngRusDict& erd2);
	friend EngRusDict getDifferenceWithEngRusDict(std::string name, EngRusDict& erd1, EngRusDict& erd2);

	void display(std::ostream& out);

	EngRusDict& operator=(const EngRusDict& other);

private:
  std::string name_;
  AVLTree< TranslationEntry > words_;
};

#endif // !ENGRUSDICT_H
