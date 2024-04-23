#include <iostream>

#include "TranslationEntry.h"

int main()
{
  setlocale(LC_ALL, "Russian");

  TranslationEntry te("Cat");
  te.addTranslation("Кот");
  TranslationEntry copyTe(te);
  copyTe.addTranslation("Котяра");
  te.addTranslations(copyTe);

  std::cout << te << "\n";
  
  copyTe.removeTranslations(te);

  std::cout << copyTe << "\n";
  std::cout << te << "\n";
  std::cout << "\n------------------------------\n\n";
  
  TranslationEntry te1("Book");
  TranslationEntry te2(te1);

  te1.addTranslation("Книга");
  te1.addTranslation("Книженька");
  te1.addTranslation("Книжуличка");
  te1.addTranslation("Буук");
  te1.addTranslation("Книжонка");
  te1.addTranslation("Букваръ");
  te1.addTranslation("Книжонка");


  te2.addTranslation("Книга");
  te2.addTranslation("Книженька");
  te2.addTranslation("Книжонка");
  std::cout << "te1: " << te1 << "\n";
  std::cout << "te2: " << te2 << "\n";
  std::cout << getIntersectionTranslations(te1, te2) << "\n";
  std::cout << getDifferenceTranslations(te1, te2) << "\n";
  std::cout << getIntersectionTranslations(te2, te1) << "\n";
  std::cout << getDifferenceTranslations(te2, te1) << "\n";

  std::cout << te1.getEnglishWord() << " " << te.getEnglishWord() << "\n";

  std::cout << "te1: " << te1.getCountTranslations() << " te2: " << te2.getCountTranslations() << "\n";

  return 0;
}