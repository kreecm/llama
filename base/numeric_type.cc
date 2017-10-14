#include <sstream>

#include "base/math.h"
#include "base/numeric_type.h"
#include "base/type.h"

namespace llama {
  namespace {

    constexpr char kUnknownName[] = "unknown";
      
    constexpr char kScalarIntName[]   = "int";
    constexpr char kScalarUIntName[]  = "uint";
    constexpr char kScalarFloatName[] = "float";
    
    constexpr char kRankZeroName[] = "scalar";
    constexpr char kRankOneName[]  = "vector";
    constexpr char kRankTwoName[]  = "matrix";

  }  // namespace
  
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

  std::string numeric_type::get_type_name(std::uint32_t code) {
    scalar_type scalar = get_scalar_type(code);
    std::uint8_t rank  = get_rank(code);
    std::uint8_t depth = get_bit_depth(code);

    std::ostringstream sout;
    sout << scalar_type_name(scalar) << static_cast<int>(depth);
    if (rank > 0) {
      std::uint8_t dim1 = get_row_dim(code);
      sout << "_" << rank_name(rank) << static_cast<int>(dim1);
      if (rank > 1) {
	std::uint8_t dim2 = get_col_dim(code);
	sout << "x" << static_cast<int>(dim2);
      }
    }
    return sout.str();
  }

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

  std::string numeric_type::scalar_type_name(scalar_type scalar) {
    switch (scalar) {
    case kScalarInt:   return kScalarIntName;
    case kScalarUInt:  return kScalarUIntName;
    case kScalarFloat: return kScalarFloatName;
    }
    return kUnknownName;
  }

  std::string numeric_type::rank_name(std::uint8_t rank) {
    switch (rank) {
    case 0: return kRankZeroName;
    case 1: return kRankOneName;
    case 2: return kRankTwoName;
    }
    return kUnknownName;
  }

}  // namespace llama
