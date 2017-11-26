#ifndef LLAMA_VALUE_H
#define LLAMA_VALUE_H

#include <functional>
#include <memory>
#include <string>

#include "base/value_base.h"

namespace llama {

class Value : public MutablValueBase {
 public:
  static constexpr size_t kInPlaceValueSize;

  // Construct an invalid value.
  Value() {}

  // Construct a value of type t.
  Value(Type t) : MutableValueBase(t) { Initialize(); }

  template <class T>
  Value() : Value(TypeOf<T>()) {}

  // Move constructor.
  Value(Value&& value) : Value(value.GetType()) { Move(value); }


  // Copy constructor.
  Value(const Value& value) : Value(value.GetType()) { Copy(value); }

  ~Value() { Delete(); }

  const void* GetDataPtr() const final;

  void* GetMutableDataPtr() final;

  Value& operator= (Value&& value) {
    Move(value);
    return *this;
  }

  Value& operator= (const Value& value) {
    Copy(value);
    return *this;
  }

 private:
  bool IsInPlace() const;

  void Initialize();

  void Move(Value&& value);

  void Copy(const Value& value);

  void Delete();

  union {
    uint8_t in_place[kInPlaceValueSize];
    void*   ptr;
  } m_data;
};

}  // namespace llama

#endif  // LLAMA_VALUE_H
