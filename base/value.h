#ifndef LLAMA_VALUE_H
#define LLAMA_VALUE_H

#include <functional>
#include <memory>
#include <string>

#include "base/error.h"
#include "base/type.h"

namespace llama {

class Value {
 public:
  using Deleter = std::function<void (Value*)>;
  using Ptr = std::unique_ptr<Value, Deleter>;

  static ErrorStatus Allocate(Type type, Ptr* value);
  static ErrorStatus Free(Value* value);

  template <class T>
  static ErrorStatus Allocate(Ptr* value) {
    return Allocate(TypeOf<T>(), value);
  }

  Type GetType() const { return m_type; }

  template <class T>
  const T& GetData() const {
    Assert(TypeOf<T>() == m_type,
           "Attempting to access value data as " + TypeName<T>() +
               ", but value holds data of type " + m_type.GetName());
    return *reinterpret_cast<const T*>(GetConstDataPtr());
  }

  template <class T>
  T* GetMutableData() {
    Assert(TypeOf<T>() == m_type,
           "Attempting to access value data as " + TypeName<T>() +
               ", but value holds data of type " + m_type.GetName());
    return reinterpret_cast<T*>(GetDataPtr());
  }

 private:
  Value(Type t) : m_type(t) {}

  ErrorStatus Initialize();

  void* GetDataPtr();
  const void* GetConstDataPtr() const;

  Type m_type;
};

}  // namespace llama

#endif  // LLAMA_VALUE_H
