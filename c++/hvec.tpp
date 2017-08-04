#include <iostream>
#include <vector>
#include "hvec.h"
using namespace std;

template <typename T>
HVector<T>::HVector() {
  _store = unique_ptr<T[]>(new T[16]);
  _count = 0;
  _capacity = 16;
}

template <typename T>
unsigned long HVector<T>::count() {
  return _count;
}

template <typename T>
void HVector<T>::push_back(const T& val) {
  if (_capacity == _count) {
    doubleCapacity();
  }

  _store[_count] = val;
  _count++;
}

template <typename T>
void HVector<T>::push_back(T&& val) {
  if (_capacity == _count) {
    doubleCapacity();
  }

  _store[_count] = val;
  _count++;
}

template <typename T>
void HVector<T>::doubleCapacity() {
  unique_ptr<T[]> newStore = unique_ptr<T[]>(new T[_capacity * 2]);
  for (unsigned long i = 0; i < _capacity; i++) {
    newStore[i] = move(_store[i]);
  }
  _store = move(newStore);
}

template <typename T>
T& HVector<T>::operator[](unsigned long i) {
  return _store[i];
}

template <typename T>
T* HVector<T>::begin() {
  return &_store[0];
}

template <typename T>
T* HVector<T>::end() {
  return _store.get() + _count;
}

template <typename T>
HVector<T>::HVector(const HVector<T>& hvec2) {
  _count = hvec2._count;
  _capacity = hvec2._capacity;
  unique_ptr<T[]> newStore = unique_ptr<T[]>(new T[hvec2._capacity]);
  for (unsigned long i = 0; i < hvec2._capacity; i++) {
    newStore[i] = hvec2._store[i];
  }
  _store = move(newStore);
}

template <typename T>
HVector<T>& HVector<T>::operator=(const HVector<T>& hvec2) {
  _count = hvec2._count;
  _capacity = hvec2._capacity;
  unique_ptr<T[]> newStore = unique_ptr<T[]>(new T[hvec2._capacity]);
  for (unsigned long i = 0; i < hvec2._capacity; i++) {
    newStore[i] = hvec2._store[i];
  }
  _store = move(newStore);
  return *this;
}

template <typename T>
template <typename Fn>
void HVector<T>::each(Fn& f) {
  for (auto el : *this) {
    f(el);
  }
}

template <typename T>
template <typename Fn>
void HVector<T>::each(Fn&& f) {
  for (auto el : *this) {
    f(el);
  }
}

template <typename T>
template <typename Fn>
auto HVector<T>::map(Fn& f) -> HVector<decltype(std::declval<Fn>()(std::declval<T>()))> {
  HVector <decltype(declval<Fn>()(declval<T>()))> res;
  for (auto el : *this) {
    res.push_back(f(el));
  }
  return res;
}

template <typename T>
template <typename Fn>
auto HVector<T>::map(Fn&& f) -> HVector<decltype(std::declval<Fn>()(std::declval<T>()))> {
  HVector <decltype(declval<Fn>()(declval<T>()))> res;
  for (auto el : *this) {
    res.push_back(f(el));
  }
  return res;
}
