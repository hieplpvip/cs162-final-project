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

  T* begin();
  T* end();

private:
  size_t _size;
  size_t _capacity;
  T* _elements;
};

template<class T>
Vector<T>::Vector() {
  _size = 0;
  _capacity = 0;
  _elements = nullptr;
}

template<class T>
Vector<T>::Vector(size_t size) {
  _size = size;
  _capacity = size;
  _elements = new T[size];
}

template<class T>
Vector<T>::Vector(size_t size, const T& initial) {
  _size = size;
  _capacity = size;
  _elements = new T[size];
  for (size_t i = 0; i < size; ++i) {
    _elements[i] = initial;
  }
}

template<class T>
Vector<T>::Vector(const Vector<T>& v) {
  _size = v._size;
  _capacity = v._capacity;
  _elements = new T[_capacity];
  for (size_t i = 0; i < _size; ++i) {
    _elements[i] = v._elements[i];
  }
}

template<class T>
Vector<T>::~Vector() {
  if (_elements) {
    delete[] _elements;
  }
}

template<class T>
size_t Vector<T>::size() const {
  return _size;
}

template<class T>
size_t Vector<T>::capacity() const {
  return _capacity;
}

template<class T>
bool Vector<T>::empty() const {
  return _size == 0;
}

template<class T>
T& Vector<T>::front() {
  return _elements[0];
}

template<class T>
T& Vector<T>::back() {
  return _elements[_size - 1];
}

template<class T>
void Vector<T>::push_back(const T& v) {
  if (_capacity == 0) {
    reserve(8);
  } else if (_size = _capacity) {
    reserve(_capacity * 2);
  }
  _elements[_size++] = v;
}

template<class T>
void Vector<T>::pop_back() {
  //_elements[_size]->~T();
  _size--;
}

template<class T>
void Vector<T>::reserve(size_t new_capacity) {
	if (new_capacity <= _capacity) return;

	T* p = new T[new_capacity];
	for (size_t i = 0; i < _size; ++i) {
		p[i] = _elements[i];
  }
	delete[] _elements;
	_elements = p;
	_capacity = new_capacity;
}

template<class T>
void Vector<T>::resize(size_t new_size, T val) {
	reserve(new_size);

	for (int i = _size; i < new_size; ++i) {
		_elements[i] = val;
  }

	_size = new_size;
}

template<class T>
T& Vector<T>::operator [](size_t index) {
  return _elements[index];
}

template<class T>
void Vector<T>::clear() {
  _size = 0;
}

template<class T>
T* Vector<T>::begin() {
  return _elements;
}

template<class T>
T* Vector<T>::end() {
  return _elements + _size;
}

#endif
