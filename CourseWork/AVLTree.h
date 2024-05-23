#ifndef AVLTREE_H
#define AVLTREE_H

#include <algorithm>
#include <iostream>

#include "MyVector.h"

template < class S, class T >
class AVLTree
{
public:
  AVLTree():
    root_(nullptr){};

  AVLTree(const AVLTree< S, T >& other):
    root_(deepCopy(other.root_)){};

  AVLTree(AVLTree< S, T >&& other) noexcept:
    root_(other.root_)
  {
    other.root_ = nullptr;
  }

  ~AVLTree()
  {
    clear();
  }

  void clear()
  {
    removeSubTree(root_);
    root_ = nullptr;
  }

  void insert(const S& key, const T& value)
  {
    root_ = insertRecursive(root_, key, value);
  }

  void remove(const S& key)
  {
    root_ = removeRecursive(root_, key);
  }

  void addElements(const AVLTree< S, T >& other)
  {
    addElementsRecursive(other.root_);
  }
  void removeElements(const AVLTree< S, T >& other)
  {
    removeElementsRecursive(other.root_);
  }
  bool contains(const S& key) const
  {
    return containsRecursive(root_, key);
  }
  T& at(const S& key) const
  {
    return at(root_, key)->data_;
  }
  size_t size() const
  {
    return sizeRecursive(root_);
  }
  size_t height() const
  {
    return heightRecursive(root_);
  }
  friend AVLTree< S, T > getIntersectionTree(const AVLTree< S, T >& tree1, const AVLTree< S, T >& tree2)
  {
    AVLTree< S, T > intersectionTree;
    getIntersectionTreeRecursive(tree1.root_, tree2, intersectionTree);
    getIntersectionTreeRecursive(tree2.root_, tree1, intersectionTree);
    return intersectionTree;
  }
  friend AVLTree< S, T > getDifferenceTree(const AVLTree< S, T >& tree1, const AVLTree< S, T >& tree2)
  {
    AVLTree< S, T > differenceTree;
    getDifferenceTreeRecursive(tree1.root_, tree2, differenceTree);
    getDifferenceTreeRecursive(tree2.root_, tree1, differenceTree);
    return differenceTree;
  }
  AVLTree< S, T >& operator=(const AVLTree< S, T >& other)
  {
    if (this != &other)
    {
      removeSubTree(root_);
      root_ = deepCopy(other.root_);
    }
    return *this;
  }
  friend std::ostream& operator<<(std::ostream& os, const AVLTree< S, T >& tree)
  {
    os << tree.root_;
    return os;
  }
  void display(std::ostream& out, std::string separator = ", ") const
  {
    displayHelper(root_, out, separator);
  }

  MyVector< S > getAllKeys() const
  {
    MyVector< S > keys;
    getAllRecursive(root_, keys);
    return keys;
  }

private:
  struct Node
  {
    T data_;
    S key_;
    Node* left_;
    Node* right_;
    size_t height_;

    Node():
      left_(nullptr),
      right_(nullptr),
      height_(1)
    {}
    Node(const S& key, const T& data):
      data_(data),
      key_(key),
      left_(nullptr),
      right_(nullptr),
      height_(1)
    {}
  };

  Node* root_;

  Node* deepCopy(Node* node)
  {
    if (node == nullptr)
    {
      return nullptr;
    }
    else
    {
      Node* newNode = new Node;
      newNode->data_ = node->data_;
      newNode->key_ = node->key_;
      newNode->left_ = deepCopy(node->left_);
      newNode->right_ = deepCopy(node->right_);
      newNode->height_ = node->height_;
      return newNode;
    }
  }

  Node* insertRecursive(Node* node, const S& key, const T& data)
  {
    if (node == nullptr)
    {
      return new Node(key, data);
    }

    if (key < node->key_)
    {
      if (node->left_ == nullptr)
      {
        node->left_ = new Node(key, data);
      }
      else
      {
        node->left_ = insertRecursive(node->left_, key, data);
      }
    }
    else if (key > node->key_)
    {
      if (node->right_ == nullptr)
      {
        node->right_ = new Node(key, data);
      }
      else
      {
        node->right_ = insertRecursive(node->right_, key, data);
      }
    }
    node->height_ = 1 + std::max(heightRecursive(node->left_), heightRecursive(node->right_));

    size_t balance = getBalance(node);

    if (balance > 1 && node->left_ && key < node->left_->key_)
    {
      return rightRotate(node);
    }
    if (balance < -1 && node->right_ && key > node->right_->key_)
    {
      return leftRotate(node);
    }
    if (balance > 1 && node->left_ && key > node->left_->key_)
    {
      if (node->left_ && node->left_->left_ && key > node->left_->left_->key_)
      {
        node->left_ = leftRotate(node->left_);
      }
      return rightRotate(node);
    }
    if (balance < -1 && node->right_ && key < node->right_->key_)
    {
      if (node->right_ && node->right_->right_ && key < node->right_->right_->key_)
      {
        node->right_ = rightRotate(node->right_);
      }
      return leftRotate(node);
    }
    return node;
  }

  Node* removeRecursive(Node* node, const S& key)
  {
    if (node == nullptr)
    {
      return node;
    }

    if (key < node->key_)
    {
      node->left_ = removeRecursive(node->left_, key);
    }
    else if (key > node->key_)
    {
      node->right_ = removeRecursive(node->right_, key);
    }
    else
    {
      if (node->left_ == nullptr)
      {
        Node* temp = node->right_;
        delete node;
        return temp;
      }
      else if (node->right_ == nullptr)
      {
        Node* temp = node->left_;
        delete node;
        return temp;
      }
      Node* temp = getMinValueNode(node->right_);
      node->key_ = temp->key_;
      node->right_ = removeRecursive(node->right_, temp->key_);
    }

    node->height_ = 1 + std::max(heightRecursive(node->left_), heightRecursive(node->right_));

    size_t balance = getBalance(node);

    if (balance > 1 && getBalance(node->left_) >= 0)
    {
      return rightRotate(node);
    }
    if (balance > 1 && getBalance(node->left_) < 0)
    {
      node->left_ = leftRotate(node->left_);
      return rightRotate(node);
    }
    if (balance < -1 && getBalance(node->right_) <= 0)
    {
      return leftRotate(node);
    }
    if (balance < -1 && getBalance(node->right_) > 0)
    {
      node->right_ = rightRotate(node->right_);
      return leftRotate(node);
    }

    return node;
  }

  void addElementsRecursive(Node* node)
  {
    if (node != nullptr)
    {
      insert(node->key_, node->data_);
      addElementsRecursive(node->left_);
      addElementsRecursive(node->right_);
    }
  }

  void removeElementsRecursive(Node* node)
  {
    if (node != nullptr)
    {
      remove(node->key_);
      removeElementsRecursive(node->left_);
      removeElementsRecursive(node->right_);
    }
  }

  size_t sizeRecursive(Node* node) const
  {
    if (node == nullptr)
    {
      return 0;
    }
    return 1 + sizeRecursive(node->left_) + sizeRecursive(node->right_);
  }

  size_t heightRecursive(Node* node) const
  {
    if (node == nullptr)
    {
      return 0;
    }
    return node->height_;
  }

  static void getIntersectionTreeRecursive(Node* node, const AVLTree< S, T >& tree, AVLTree< S, T >& intersectionTree)
  {
    if (node != nullptr)
    {
      if (tree.contains(node->key_))
      {
        intersectionTree.insert(node->key_, node->data_);
      }
      getIntersectionTreeRecursive(node->left_, tree, intersectionTree);
      getIntersectionTreeRecursive(node->right_, tree, intersectionTree);
    }
  }

  static void getDifferenceTreeRecursive(Node* node, const AVLTree< S, T >& tree, AVLTree< S, T >& differenceTree)
  {
    if (node != nullptr)
    {
      if (!tree.contains(node->key_))
      {
        differenceTree.insert(node->key_, node->data_);
      }
      getDifferenceTreeRecursive(node->left_, tree, differenceTree);
      getDifferenceTreeRecursive(node->right_, tree, differenceTree);
    }
  }

  size_t getBalance(Node* node) const
  {
    if (node == nullptr)
    {
      return 0;
    }
    return heightRecursive(node->left_) - heightRecursive(node->right_);
  }

  Node* rightRotate(Node* node)
  {
    if (node == nullptr || node->left_ == nullptr || node->left_->right_ == nullptr)
    {
      return node;
    }

    Node* nextLeftNode = node->left_;
    Node* newRightSubtree = nextLeftNode->right_;

    nextLeftNode->right_ = node;
    node->left_ = newRightSubtree;

    node->height_ = 1 + std::max(heightRecursive(node->left_), heightRecursive(node->right_));
    nextLeftNode->height_ = 1 + std::max(heightRecursive(nextLeftNode->left_), heightRecursive(nextLeftNode->right_));

    return nextLeftNode;
  }

  Node* leftRotate(Node* node)
  {
    if (node == nullptr || node->right_ == nullptr || node->right_->left_ == nullptr)
    {
      return node;
    }

    Node* nextRightNode = node->right_;
    Node* newLeftSubtree = nextRightNode->left_;

    nextRightNode->left_ = node;
    node->right_ = newLeftSubtree;

    node->height_ = 1 + std::max(heightRecursive(node->left_), heightRecursive(node->right_));
    nextRightNode->height_ =
      1 + std::max(heightRecursive(nextRightNode->left_), heightRecursive(nextRightNode->right_));

    return nextRightNode;
  }

  void removeSubTree(Node* node)
  {
    if (node != nullptr)
    {
      removeSubTree(node->left_);
      removeSubTree(node->right_);
      delete node;
    }
  }

  Node* at(Node* node, const S& key) const
  {
    if (node == nullptr)
    {
      throw std::invalid_argument("Нет никакого указанного элемента");
    }
    if (node->key_ == key)
    {
      return node;
    }
    if (key < node->key_)
    {
      return at(node->left_, key);
    }
    return at(node->right_, key);
  }

  Node* getMinValueNode(Node* node) const
  {
    Node* current = node;

    while (current && current->left_ != nullptr)
    {
      current = current->left_;
    }

    return current;
  }

  bool containsRecursive(Node* node, const S& key) const
  {
    if (node == nullptr)
    {
      return false;
    }

    if (key < node->key_)
    {
      return containsRecursive(node->left_, key);
    }
    else if (key > node->key_)
    {
      return containsRecursive(node->right_, key);
    }
    else
    {
      return true;
    }
  }

  void displayHelper(const Node* node, std::ostream& out, const std::string& separator) const
  {
    if (node != nullptr)
    {
      displayHelper(node->left_, out, separator);
      if (node->left_ != nullptr)
      {
        out << separator;
      }
      out << node->key_ << ": " << node->data_;
      if (node->right_ != nullptr)
      {
        out << separator;
      }
      displayHelper(node->right_, out, separator);
    }
  }

  void getAllRecursive(const Node* node, MyVector< S >& keys) const
  {
    if (node != nullptr)
    {
      getAllRecursive(node->left_, keys);
      keys.push_back(node->key_);
      getAllRecursive(node->right_, keys);
    }
  }
};

#endif // !AVLTREE_H
