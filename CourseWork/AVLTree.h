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
    root_(nullptr)
  {}

  AVLTree(const AVLTree< Key, Value >& other):
    root_(deepCopyNode(other.root_))
  {}

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

  AVLTree< Key, Value >& operator=(const AVLTree< Key, Value >& other)
  {
    if (this != &other)
    {
      clear();
      root_ = deepCopyNode(other.root_);
    }
    return *this;
  }

  void display(std::ostream& out, const std::string separator = ", ") const
  {
    displayRecursive(root_, out, separator);
  }

  MyVector< Key > getAllKeys() const
  {
    MyVector< Key > keys;
    getAllKeysRecursive(root_, keys);
    return keys;
  }

private:
  struct Node
  {
    Value value_;
    Key key_;
    Node* left_;
    Node* right_;
    int balance_;

    Node():
      left_(nullptr),
      right_(nullptr),
      balance_(0)
    {}

    Node(const Key& key, const Value& value):
      value_(value),
      key_(key),
      left_(nullptr),
      right_(nullptr),
      balance_(0)
    {}
  };

  Node* root_;

  Node* deepCopyNode(Node* node)
  {
    if (node == nullptr)
      return nullptr;
    Node* newNode = new Node(node->key_, node->value_);
    newNode->left_ = deepCopyNode(node->left_);
    newNode->right_ = deepCopyNode(node->right_);
    newNode->balance_ = node->balance_;
    return newNode;
  }

  Node* insertRecursive(Node* node, const Key& key, const Value& value)
  {
    if (node == nullptr)
      return new Node(key, value);
    if (key < node->key_)
    {
      node->left_ = insertRecursive(node->left_, key, value);
    }
    else if (key > node->key_)
    {
      node->right_ = insertRecursive(node->right_, key, value);
    }
    else
    {
      return node;
    }
    updateBalance(node);
    return balanceNode(node, key);
  }

  Node* removeRecursive(Node* node, const Key& key)
  {
    if (node == nullptr)
      return node;
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
      if (node->left_ == nullptr || node->right_ == nullptr)
      {
        Node* temp = node->left_ ? node->left_ : node->right_;
        if (temp == nullptr)
        {
          temp = node;
          node = nullptr;
        }
        else
        {
          *node = *temp; // Copy the contents of the non-empty child
        }
        delete temp;
      }
      else
      {
        Node* temp = getMinValueNode(node->right_);
        node->key_ = temp->key_;
        node->value_ = temp->value_;
        node->right_ = removeRecursive(node->right_, temp->key_);
      }
    }
    if (node == nullptr)
      return node;
    updateBalance(node);
    return balanceNode(node, key);
  }

  void updateBalance(Node* node)
  {
    if (node == nullptr)
      return;
    int leftHeight = (node->left_ ? node->left_->balance_ : 0);
    int rightHeight = (node->right_ ? node->right_->balance_ : 0);
    node->balance_ = 1 + std::max(leftHeight, rightHeight);
  }

  Node* balanceNode(Node* node, const Key& key)
  {
    int balance = getBalance(node);
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

  Node* rightRotate(Node* y)
  {
    Node* x = y->left_;
    Node* T2 = x->right_;

    x->right_ = y;
    y->left_ = T2;

    updateBalance(y);
    updateBalance(x);

    return x;
  }

  Node* leftRotate(Node* x)
  {
    Node* y = x->right_;
    Node* T2 = y->left_;

    y->left_ = x;
    x->right_ = T2;

    updateBalance(x);
    updateBalance(y);

    return y;
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
      throw std::invalid_argument("No element found with the given key");
    }
    if (key < node->key_)
    {
      return at(node->left_, key);
    }
    else if (key > node->key_)
    {
      return at(node->right_, key);
    }
    return node;
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
    return true;
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

  void getAllKeysRecursive(const Node* node, MyVector< Key >& keys) const
  {
    if (node != nullptr)
    {
      getAllKeysRecursive(node->left_, keys);
      keys.push_back(node->key_);
      getAllKeysRecursive(node->right_, keys);
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

  int getBalance(Node* node) const
  {
    if (node == nullptr)
      return 0;
    int leftHeight = (node->left_ ? node->left_->balance_ : 0);
    int rightHeight = (node->right_ ? node->right_->balance_ : 0);
    return leftHeight - rightHeight;
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
};

#endif // AVLTREE_H
