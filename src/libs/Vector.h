#ifndef VECTOR_H
#define VECTOR_H

#include <stddef.h>

// TODO: unit test
template<class T>
class Vector {
public:
  Vector();
  Vector(size_t size);
  Vector(size_t size, const T& initial);
  Vector(const Vector<T>& v);
  ~Vector();

  size_t capacity() const;
  size_t size() const;
  bool empty() const;

  T& front();
  T& back();
  void push_back(const T& value);
  void pop_back();

  void reserve(size_t capacity);
  void resize(size_t size, T val = T());

  T& operator [](size_t index);
  void clear();

private:
  size_t _size;
  size_t _capacity;
  T* _elements;
};

#endif
