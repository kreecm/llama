#ifndef LLAMA_VALUE_BASE_H
#define LLAMA_VALUE_BASE_H

#include <type_traits>

#include "base/error.h"
#include "base/type.h"

namespace llama {

class ValueBase {
 public:
  ValueBase() {}

  ValueBase(Type type) : m_type(type) {}

  virtual ~ValueBase() {}

  Type GetType() const { return m_type; }

  virtual const void* GetDataPtr() const = 0;

  template <class T>
  const T& Get() const {
    Assert(TypeOf<T>() == m_type,
           "Attempting to access value data as " + TypeName<T>() +
           ", but value holds data of type " + m_type.GetName());
    return *reinterpret_cast<const T*>(this->GetDataPtr());
  }

 protected:
  Type m_type;
};

class MutableValueBase : public ValueBase {
 public:
  MutableValueBase() {}

  MutableValueBase(Type type) : ValueBase(type) {}

  virtual void* GetMutableDataPtr() = 0;

  template <class T>
  T* GetMutable() {
    Assert(TypeOf<T>() == m_type,
           "Attempting to access value data as " + TypeName<T>() +
               ", but value holds data of type " + m_type.GetName());
    return reinterpret_cast<T*>(this->GetMutableDataPtr());
  }
};

}  // namespace llama

#endif // LLAMA_VALUE_BASE_H
