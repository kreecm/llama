#ifndef LLAMA_VALUE_PTR_H
#define LLAMA_VALUE_PTR_H

#include "base/value_base.h"

namespace llama {

class MutableValuePtr;

class ValuePtr : public ValueBase {
 public:
  ValuePtr() : m_ptr(nullptr) {}

  ValuePtr(const ValueBase* value)
      : ValueBase(value->GetType()),
        m_ptr(value->GeDataPtr()) {}

  template <class T>
  ValuePtr(const T* value)
      : ValueBase(TypeOf<T>())
        m_ptr(reinterpret_cast<const void*>(value)) {}

  ValuePtr(const MutableValuePtr& mutable_ptr);

  const void* GetDataPtr() const final { return m_ptr; }

 private:
  const void* m_ptr;
};

class MutableValuePtr : public MutableValueBase {
 public:
  MutableValuePtr() : m_ptr(nullptr) {}

  MutableValuePtr(Value* value)
      : MutableValueBase(value->GetType()),
        m_ptr(value->GeDataPtr()) {}

  template <class T>
  MutableValuePtr(T* value)
      : MutableValueBase(TypeOf<T>())
        m_ptr(reinterpret_cast<void*>(value)) {}

  const void* GetDataPtr() const final { return m_ptr; }

  void* GetMutableDataPtr() final { return m_ptr; }

 private:
  void* m_ptr;
};

ValuePtr::ValuePtr(const MutableValuePtr& mutable_ptr)
    : ValuePtr(&mutable_ptr) {}

}  // namespace llama

#endif  // LLAMA_VALUE_PTR_H
