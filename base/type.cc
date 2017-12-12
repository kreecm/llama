#include <cassert>
#include <cstring>

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

size_t Type::GetSize() const {
  switch (GetCategory()) {
    case kTypeUndefined:
      return 0;
    case kTypeNumeric:
      return NumericType::GetSize(m_code);
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
  return 0;
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

Type::Initializer Type::GetInitializer() const {
  switch (GetCategory()) {
    case kTypeUndefined:
    case kTypeNumeric:
      return [](void* mem) { return Success(); };
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
  return [this](void* mem) {
    return UnimplementedError("GetInitializer is not implemented for type " +
                              GetName());
  };
}

Type::Copier Type::GetCopier() const {
  switch (GetCategory()) {
    case kTypeUndefined:
    case kTypeNumeric:
      return [](const void* src, void* dst) {
        std::memcpy(dst, src, GetSize());
        return Success();
      };
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
  return [this](void* mem) {
    return UnimplementedError("GetInitializer is not implemented for type " +
                              GetName());
  };
}

Type::Mover Type::GetMover() const {
  switch (GetCategory()) {
    case kTypeUndefined:
    case kTypeNumeric:
      return [](void* src, void* dst) {
        return Success();
      };
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
  return [this](void* mem) {
    return UnimplementedError("GetInitializer is not implemented for type " +
                              GetName());
  };
}

Type::Finalizer Type::GetFinalizer() const {
  switch (GetCategory()) {
    case kTypeUndefined:
    case kTypeNumeric:
      return [](void* mem) { return Success(); };
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
  return [this](void* mem) {
    return UnimplementedError("GetFinalizer is not implemented for type " +
                              GetName());
  };
}

}  // namespace llama
