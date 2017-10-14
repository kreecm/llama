#include "math.h"
#include "numeric_type.h"
#include "type.h"

namespace llama {
  
  constexpr std::uint32_t numeric_type::kShiftScalar;
  constexpr std::uint32_t numeric_type::kShiftRank;
  constexpr std::uint32_t numeric_type::kShiftBitDepth;
  constexpr std::uint32_t numeric_type::kShiftRowDim;
  constexpr std::uint32_t numeric_type::kShiftColDim;
  
  constexpr std::uint32_t numeric_type::kMaskScalar;
  constexpr std::uint32_t numeric_type::kMaskRank;
  constexpr std::uint32_t numeric_type::kMaskBitDepth;
  constexpr std::uint32_t numeric_type::kMaskRowDim;
  constexpr std::uint32_t numeric_type::kMaskColDim;

  std::uint32_t numeric_type::encode(scalar_type scalar,
				     std::uint8_t bit_depth,
				     std::initializer_list<std::uint8_t> dims) {
    // TODO(kree): Make these compile-time checks.
    assert(validate_bit_depth(scalar, bit_depth));
    assert(dims.size() < 3);

    std::uint8_t rank = dims.size();
    std::uint8_t bits = encode_bit_depth(bit_depth);
    std::int32_t code = type::kTypeNumeric;
    code |= scalar << kShiftScalar;
    code |= rank   << kShiftRank;
    code |= bits   << kShiftBitDepth;
    int shift = kShiftRowDim;
    for (std::uint8_t dim : dims) {
      code |= dim << shift;
      shift += 8;
    }
      
    return code;
  };

  bool numeric_type::validate_bit_depth(scalar_type scalar,
					std::uint8_t bit_depth) {
    if (!is_power_of_two(bit_depth)) {
      return false;
    } else if (scalar == kScalarFloat) {
      return 32 <= bit_depth && bit_depth <= 64;
    } else {
      return 8 <= bit_depth && bit_depth <= 64;
    }
  }

  std::uint8_t numeric_type::encode_bit_depth(std::uint8_t bit_depth) {
    std::uint8_t code;
    for (code = 0; bit_depth > 0; ++code) {
      bit_depth = bit_depth >> 1;
    }
    return code - 4;
  }
  
  std::uint8_t numeric_type::decode_bit_depth(std::uint8_t code) {
    return 1 << (code + 3);
  } 

}  // namespace llama
