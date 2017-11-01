#ifndef LLAMA_VALUE_H
#define LLAMA_VALUE_H

#include <string>

#include "base/type.h"

namespace llama {

class Value {
 public:
  Value(Type t);

 private:
  static constexpr int kInPlaceSize = sizeof(std::string);

  Type m_type;
  bool m_in_place_data;

  union m_data {
    uint8_t in_place[kInPlaceSize];
    void* ptr;
  };
};

}  // namespace llama

#endif  // LLAMA_VALUE_H
