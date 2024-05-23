#ifndef AVLTREE_H
#define AVLTREE_H

#include <algorithm>
#include <iostream>

#include "MyVector.h"

template < class Key, class Value >
class AVLTree
{
public:
  AVLTree():
    root_(nullptr){};

  AVLTree(const AVLTree< Key, Value >& other):
    root_(deepCopyNode(other.root_)){};

  AVLTree(AVLTree< Key, Value >&& other) noexcept:
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

  void insert(const Key& key, const Value& value)
  {
    root_ = insertRecursive(root_, key, value);
  }

  void remove(const Key& key)
  {
    root_ = removeRecursive(root_, key);
  }

  void addElements(const AVLTree< Key, Value >& other)
  {
    addElementsRecursive(other.root_);
  }

  void removeElements(const AVLTree< Key, Value >& other)
  {
    removeElementsRecursive(other.root_);
  }

  bool contains(const Key& key) const
  {
    return containsRecursive(root_, key);
  }

  Value& at(const Key& key) const
  {
    return at(root_, key)->value_;
  }

  size_t size() const
  {
    return sizeRecursive(root_);
  }

  size_t height() const
  {
    return heightRecursive(root_);
  }

  AVLTree< Key, Value >& operator=(const AVLTree< Key, Value >& other)
  {
    if (this != &other)
    {
      removeSubTree(root_);
      root_ = deepCopyNode(other.root_);
    }
    return *this;
  }

  friend std::ostream& operator<<(std::ostream& os, const AVLTree< Key, Value >& tree)
  {
    os << tree.root_;
    return os;
  }

  void display(std::ostream& out, std::string separator = ", ") const
  {
    displayRecursive(root_, out, separator);
  }

  MyVector< Key > getAllKeys() const
  {
    MyVector< Key > keys;
    getAllRecursive(root_, keys);
    return keys;
  }

private:
  struct Node
  {
    Value value_;
    Key key_;
    Node* left_;
    Node* right_;
    size_t height_;

    Node():
      left_(nullptr),
      right_(nullptr),
      height_(1)
    {}

    Node(const Key& key, const Value& value):
      value_(value),
      key_(key),
      left_(nullptr),
      right_(nullptr),
      height_(1)
    {}
  };

  Node* root_;

  Node* deepCopyNode(Node* node)
  {
    if (node == nullptr)
    {
      return nullptr;
    }
    else
    {
      Node* newNode = new Node;
      newNode->value_ = node->value_;
      newNode->key_ = node->key_;
      newNode->left_ = deepCopyNode(node->left_);
      newNode->right_ = deepCopyNode(node->right_);
      newNode->height_ = node->height_;
      return newNode;
    }
  }

  Node* insertRecursive(Node* node, const Key& key, const Value& value)
  {
    if (node == nullptr)
    {
      return new Node(key, value);
    }

    if (key < node->key_)
    {
      if (node->left_ == nullptr)
      {
        node->left_ = new Node(key, value);
      }
      else
      {
        node->left_ = insertRecursive(node->left_, key, value);
      }
    }
    else if (key > node->key_)
    {
      if (node->right_ == nullptr)
      {
        node->right_ = new Node(key, value);
      }
      else
      {
        node->right_ = insertRecursive(node->right_, key, value);
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

  Node* removeRecursive(Node* node, const Key& key)
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
      insert(node->key_, node->value_);
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
    if (node == nullptr || node->left_ == nullptr)
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
    if (node == nullptr || node->right_ == nullptr)
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

  Node* at(Node* node, const Key& key) const
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

  bool containsRecursive(Node* node, const Key& key) const
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

  void displayRecursive(const Node* node, std::ostream& out, const std::string& separator) const
  {
    if (node != nullptr)
    {
      displayRecursive(node->left_, out, separator);
      if (node->left_ != nullptr)
      {
        out << separator;
      }
      out << node->key_ << ": " << node->value_;
      if (node->right_ != nullptr)
      {
        out << separator;
      }
      displayRecursive(node->right_, out, separator);
    }
  }

  void getAllRecursive(const Node* node, MyVector< Key >& keys) const
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
