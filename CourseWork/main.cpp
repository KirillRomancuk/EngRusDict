#include <iostream>

#include "EngRusDict.h"

int main()
{
  setlocale(LC_ALL, "Russian");
  TranslationEntry te("Cat");
  te.addTranslation("Кот");
  TranslationEntry copyTe(te);
  copyTe.addTranslation("Котяра");
  te.addTranslations(copyTe);

  EngRusDict first("first");

  first.addWord(te);

  first.display();
  EngRusDict moveFirst(std::move(first));
  first.display();
  moveFirst.display();

  EngRusDict  second("second");

  second.addWordFromEngRusDict(moveFirst);

  TranslationEntry book("Book");
  book.addTranslation("Книга");
  book.addTranslation("Книжонка");
  book.addTranslation("Книженька");

  TranslationEntry home("home");
  home.addTranslation("дом");
  home.addTranslation("ДОМИНА");
  home.addTranslation("домик");

  TranslationEntry bed("bed");
  bed.addTranslation("кровать");
  bed.addTranslation("КРОВАТИНА");
  bed.addTranslation("бэд");

  second.addWord(bed);
  second.addWord(book);
  second.addWord(home);
  second.addWordFromEngRusDict(moveFirst);

  moveFirst.addWord(bed);

  moveFirst.display();
  second.display();
  
  getDifferenceWithEngRusDict("test", moveFirst, second).display();
  getIntersectionWithEngRusDict("test", moveFirst, second).display();
  getDifferenceWithEngRusDict("test", second, moveFirst).display();
  getIntersectionWithEngRusDict("test", second, moveFirst).display();
  return 0;
}