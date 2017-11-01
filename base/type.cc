#include <cassert>

#include "base/type.h"

namespace llama {
namespace {

constexpr char kUnknownTypeName[] = "unknown";

}  // namespace

constexpr std::uint32_t Type::kMaskCategory;

Type Type::Vector(Type scalar, std::uint8_t dim) {
  assert(scalar.IsScalar());
  return Type(
      NumericType::Encode(scalar.GetScalarType(), scalar.GetBitDepth(), {dim}));
}

Type Type::Matrix(Type scalar, std::uint8_t row_dim, std::uint8_t col_dim) {
  assert(scalar.IsScalar());
  return Type(NumericType::Encode(scalar.GetScalarType(), scalar.GetBitDepth(),
                                  {row_dim, col_dim}));
}

std::string Type::GetName() const {
  switch (GetCategory()) {
    case kTypeUndefined:
      return kUnknownTypeName;
    case kTypeNumeric:
      return NumericType::GetName(m_code);
    case kTypeString:
      break;
    case kTypeEnum:
      break;
    case kTypeTuple:
      break;
    case kTypeArray:
      break;
    case kTypeDictionary:
      break;
    case kTypeBuffer:
      break;
    case kTypeCustom:
      break;
  }
  return kUnknownTypeName;
}

}  // namespace llama
