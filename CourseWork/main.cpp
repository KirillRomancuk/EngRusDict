#include <iostream>

#include "AVLTree.h"

int main()
{
  setlocale(LC_ALL, "Russian");

  AVLTree<std::string> tree;

  tree.insert("A");
  tree.insert("B");
  tree.insert("D");
  tree.insert("C");
  tree.insert("J");
  tree.insert("E");

  tree.display();

  AVLTree<std::string> deleteTree(tree);

  deleteTree.remove("A");
  deleteTree.remove("D");
  deleteTree.remove("J");

  tree.removeElements(deleteTree);

  tree.display();

  AVLTree<std::string> addTree(std::move(deleteTree));

  tree.addElements(addTree);

  deleteTree = tree;

  tree.display();

  tree = addTree;

  tree.display();

  std::cout << "\n--------------------------------------------------\n\n";

  std::cout << "deleteTree: ";
  deleteTree.display();
  std::cout << "tree: ";
  tree.display();

  getIntersectionTree(tree, deleteTree).display();
  getDifferenceTree(tree, deleteTree).display();

  getIntersectionTree(deleteTree, tree).display();
  getDifferenceTree(deleteTree, tree).display();

  std::cout << "\n--------------------------------------------------\n\n";

  if (tree.contains("B") && tree.contains("C") && tree.contains("E"))
  {
    std::cout << "TRUE\n";
  }
  else
  {
    std::cout << "FALSE\n";
  }

  if (!(tree.contains("A") || tree.contains("D") || tree.contains("J")))
  {
    std::cout << "TRUE\n";
  }
  else
  {
    std::cout << "FALSE\n";
  }

  try
  {
    std::cout << tree.search("B") << " " << tree.search("C") << " " << tree.search("E") << "\n";
    tree.search("G");
  }
  catch (std::exception& ex)
  {
    std::cout << "YEEEEES!!!!\n";
  }

  tree.display();
  std::cout << "tree: ";
  tree.clear();
  tree.display();
  tree.insert("END.");
  tree.display();

  return 0;
}