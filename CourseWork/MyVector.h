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
  class Iterator
  {
  private:
    T* ptr_;

  public:
    Iterator(T* ptr):
      ptr_(ptr)
    {}
    T& operator*()
    {
      return *ptr_;
    }
    Iterator& operator++()
    {
      ++ptr_;
      return *this;
    }
    bool operator!=(const Iterator& other) const
    {
      return ptr_ != other.ptr_;
    }
  };

  Iterator find(const T& value)
  {
    for (T* ptr = array_; ptr != array_ + size_; ++ptr)
    {
      if (*ptr == value)
      {
        return Iterator(ptr);
      }
    }
    return Iterator(array_ + size_);
  }

  Iterator begin()
  {
    return Iterator(array_);
  }

  Iterator end()
  {
    return Iterator(array_ + size_);
  }

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

  void erase(const Iterator& it)
  {
    if (it == end())
    {
      throw std::out_of_range("Предпринята попытка удалить итератор end()");
    }
    T* ptr = &(*it);
    for (T* i = ptr; i != array_ + size_ - 1; ++i)
    {
      *i = *(i + 1);
    }
    --size_;
  }
  size_t getSize() const { return size_; }

  T& operator[](size_t index) {
    if (index >= size_) {
      throw std::out_of_range("Индекс вне диапазона");
    }
    return array_[index];
  }

  void clear() { size_ = 0; }
};

#endif  // !MYVECTOR_H
