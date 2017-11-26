#ifndef LLAMA_TYPE_H
#define LLAMA_TYPE_H

#include <cstdint>
#include <functional>
#include <string>

#include "base/error.h"
#include "base/numeric_type.h"

namespace llama {

// Core identifier of data types in the llama type system.
//
// Types are encoded into a 32-bit integer code as follows:
//
//   bits 0-7:  category
//   bits 8-31: category params
//
// Each category defines its required params, which must fit into 28 bits and
// specify the format of the data represented by the type.
class Type {
 public:
  enum Category {
    kTypeUndefined = 0,
    kTypeNumeric = 1,
    kTypeString = 2,
    kTypeEnum = 3,
    kTypeTuple = 4,
    kTypeArray = 5,
    kTypeDictionary = 6,
    kTypeBuffer = 7,
    kTypeCustom = 8
  };

  using Initializer = std::function<ErrorStatus (void*)>;
  using Copier = std::function<ErrorStatus (const void*, void*)>;
  using Mover = std::function<ErrorStatus (void*, void*)>;
  using Finalizer = std::function<ErrorStatus (void*)>;
  using ScalarType = NumericType::ScalarType;

  // Static contructors for numeric types.
  // =====================================================================
  static Type MakeNumericType(ScalarType scalar, std::uint8_t bit_depth,
                              std::initializer_list<std::uint8_t> dims) {
    return Type(NumericType::Encode(scalar, bit_depth, dims));
  }

  static Type Int(std::int8_t bit_depth) {
    return MakeNumericType(NumericType::kScalarInt, bit_depth, {});
  }

  static Type UInt(std::int8_t bit_depth) {
    return MakeNumericType(NumericType::kScalarUInt, bit_depth, {});
  }

  static Type Float(std::int8_t bit_depth) {
    return MakeNumericType(NumericType::kScalarFloat, bit_depth, {});
  }

  static Type Vector(Type scalar, std::uint8_t dim);

  static Type Matrix(Type scalar, std::uint8_t row_dim, std::uint8_t col_dim);

  // Accessors for all types.
  // =====================================================================
  bool IsDefined() const { return GetCategory() != kTypeUndefined; }

  Category GetCategory() const {
    return static_cast<Category>(m_code & kMaskCategory);
  }

  size_t GetSize() const;

  std::string GetName() const;

  Initializer GetInitializer() const;

  Copier GetCopier() const;

  Mover GetMover() const;

  Finalizer GetFinalizer() const;

  // Accessors for numeric types.
  // =====================================================================
  bool IsNumeric() const { return GetCategory() == kTypeNumeric; }

  bool IsScalar() const {
    return IsNumeric() && NumericType::GetRank(m_code) == 0;
  }

  ScalarType GetScalarType() const {
    Assert(IsNumeric(), "GetScalarType() is only defined for numeric types.");
    return NumericType::GetScalarType(m_code);
  }

  std::uint8_t GetBitDepth() const {
    Assert(IsNumeric(), "GetBitDepth() is only defined for numeric types.");
    return NumericType::GetBitDepth(m_code);
  }

  bool operator== (const Type& other) const { return m_code == other.m_code; }

 private:
  static constexpr std::uint32_t kMaskCategory = 0xf;

  Type(std::uint32_t code) : m_code(code) {}

  std::uint32_t m_code;
};


template <typename T>
Type TypeOf();
template <typename T>
std::string TypeName() {
  return TypeOf<T>().GetName();
}

template <>
inline Type TypeOf<std::int8_t>() {
  return Type::Int(8);
}
template <>
inline Type TypeOf<std::int16_t>() {
  return Type::Int(16);
}
template <>
inline Type TypeOf<std::int32_t>() {
  return Type::Int(32);
}
template <>
inline Type TypeOf<std::int64_t>() {
  return Type::Int(64);
}

template <>
inline Type TypeOf<std::uint8_t>() {
  return Type::UInt(8);
}
template <>
inline Type TypeOf<std::uint16_t>() {
  return Type::UInt(16);
}
template <>
inline Type TypeOf<std::uint32_t>() {
  return Type::UInt(32);
}
template <>
inline Type TypeOf<std::uint64_t>() {
  return Type::UInt(64);
}

template <>
inline Type TypeOf<float>() {
  return Type::Float(32);
}
template <>
inline Type TypeOf<double>() {
  return Type::Float(64);
}

}  // namespace llama

#endif  // LLAMA_TYPE_H
