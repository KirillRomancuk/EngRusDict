#ifndef MYVECTOR_H
#define MYVECTOR_H

#include <iostream>
#include <stdexcept>

template <class T>
class MyVector {
 private:
  T* array_;
  size_t size_;
  size_t capacity_;
  const int CAPACITY_CHANGE_FACTOR_ = 2;

 public:
  MyVector() : array_(nullptr), size_(0), capacity_(0) {}

  ~MyVector() { delete[] array_; }

  void push_back(const T& value) {
    if (size_ >= capacity_) {
      capacity_ = (capacity_ == 0) ? 1 : capacity_ * CAPACITY_CHANGE_FACTOR_;
      T* new_array = new T[capacity_];
      for (size_t i = 0; i < size_; ++i) {
        new_array[i] = array_[i];
      }
      delete[] array_;
      array_ = new_array;
    }
    array_[size_++] = value;
  }

  void erase(size_t index) {
    if (index >= size_) {
      throw std::out_of_range("Index out of range");
    }

    for (size_t i = index; i < size_ - 1; ++i) {
      array_[i] = array_[i + 1];
    }

    size_--;
  }

  size_t getSize() const { return size_; }

  T& operator[](size_t index) {
    if (index >= size_) {
      throw std::out_of_range("Index out of range");
    }
    return array_[index];
  }

  void clear() { size_ = 0; }

  T* begin() { return array_; }

  T* end() { return array_ + size_; }
};

#endif  // !MYVECTOR_H
