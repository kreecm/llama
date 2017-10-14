#include <cassert>

#include "type.h"

namespace llama {

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
  
}  // namespace llama

