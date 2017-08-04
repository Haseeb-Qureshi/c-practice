#ifndef HVEC_H
#define HVEC_H
#include <memory>

template <typename T>
class HVector {
private:
  void doubleCapacity();
  std::unique_ptr<T[]> _store; // effectively a int* pointer
  unsigned long _count;
  unsigned long _capacity;
public:
  HVector();
  HVector(const HVector<T>& hvec2);
  unsigned long count();
  void push_back(const T& val);
  void push_back(T&& val);
  T& operator[](unsigned long);
  T* begin();
  T* end();
  HVector<T>& operator=(const HVector<T>& hvec2);
  template <typename Fn>
  void each(Fn&);
  template <typename Fn>
  void each(Fn&&);
  template <typename Fn>
  auto map(Fn&) -> HVector<decltype(std::declval<Fn>()(std::declval<T>()))>;
  template <typename Fn>
  auto map(Fn&&) -> HVector<decltype(std::declval<Fn>()(std::declval<T>()))>;
};

#include "hvec.tpp"

#endif
