#include <cassert>

#include "base/type.h"

namespace llama {
  namespace {
    
    constexpr char kUnknownTypeName[] = "unknown";

  }  // namespace
  
  constexpr std::uint32_t type::kMaskCategory;
  
  type type::make_vector(type scalar, std::uint8_t dim) {
    assert(scalar.is_scalar());
    return type(numeric_type::encode(scalar.get_scalar_type(),
				     scalar.get_bit_depth(),
				     {dim}));
  }

  type type::make_matrix(type scalar, std::uint8_t row_dim,
			 std::uint8_t col_dim) {
    assert(scalar.is_scalar());
    return type(numeric_type::encode(scalar.get_scalar_type(),
				     scalar.get_bit_depth(),
				     {row_dim, col_dim}));
  }

  std::string type::get_type_name() const {
    switch (get_category()) {
    case kTypeUndefined:
      return kUnknownTypeName;
    case kTypeNumeric:
      return numeric_type::get_type_name(m_code);
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

