#include <sstream>

#include "base/math.h"
#include "base/numeric_type.h"
#include "base/type.h"

namespace llama {
namespace {

constexpr char kUnknownName[] = "unknown";

constexpr char kScalarIntName[] = "int";
constexpr char kScalarUIntName[] = "uint";
constexpr char kScalarFloatName[] = "float";

constexpr char kRankZeroName[] = "scalar";
constexpr char kRankOneName[] = "vector";
constexpr char kRankTwoName[] = "matrix";

}  // namespace

constexpr std::uint32_t NumericType::kShiftScalar;
constexpr std::uint32_t NumericType::kShiftRank;
constexpr std::uint32_t NumericType::kShiftBitDepth;
constexpr std::uint32_t NumericType::kShiftRowDim;
constexpr std::uint32_t NumericType::kShiftColDim;

constexpr std::uint32_t NumericType::kMaskScalar;
constexpr std::uint32_t NumericType::kMaskRank;
constexpr std::uint32_t NumericType::kMaskBitDepth;
constexpr std::uint32_t NumericType::kMaskRowDim;
constexpr std::uint32_t NumericType::kMaskColDim;

std::uint32_t NumericType::Encode(ScalarType scalar, std::uint8_t bit_depth,
                                  std::initializer_list<std::uint8_t> dims) {
  // TODO(kree): Make these compile-time checks.
  assert(ValidateBitDepth(scalar, bit_depth));
  assert(dims.size() < 3);

  std::uint8_t rank = dims.size();
  std::uint8_t bits = EncodeBitDepth(bit_depth);
  std::int32_t code = Type::kTypeNumeric;
  code |= scalar << kShiftScalar;
  code |= rank << kShiftRank;
  code |= bits << kShiftBitDepth;
  int shift = kShiftRowDim;
  for (std::uint8_t dim : dims) {
    code |= dim << shift;
    shift += 8;
  }

  return code;
};

size_t NumericType::GetSize(std::uint32_t code) {
  std::uint8_t rank = GetRank(code);
  std::size_t scalar_size = GetBitDepth(code) / 8;

  if (rank == 0) {
    return scalar_size;
  } else if (rank == 1) {
    std::uint8_t dim = GetRowDim(code);
    return scalar_size * dim;
  } else if (rank == 2) {
    std::uint8_t row_dim = GetRowDim(code);
    std::uint8_t col_dim = GetColDim(code);
    return scalar_size * row_dim * col_dim;
  }
  return 0;
}

std::string NumericType::GetName(std::uint32_t code) {
  ScalarType scalar = GetScalarType(code);
  std::uint8_t rank = GetRank(code);
  std::uint8_t depth = GetBitDepth(code);

  std::ostringstream sout;
  sout << ScalarTypeName(scalar) << static_cast<int>(depth);
  if (rank > 0) {
    std::uint8_t dim1 = GetRowDim(code);
    sout << "_" << RankName(rank) << static_cast<int>(dim1);
    if (rank > 1) {
      std::uint8_t dim2 = GetColDim(code);
      sout << "x" << static_cast<int>(dim2);
    }
  }
  return sout.str();
}

bool NumericType::ValidateBitDepth(ScalarType scalar, std::uint8_t bit_depth) {
  if (!IsPowerOfTwo(bit_depth)) {
    return false;
  } else if (scalar == kScalarFloat) {
    return 32 <= bit_depth && bit_depth <= 64;
  } else {
    return 8 <= bit_depth && bit_depth <= 64;
  }
}

std::uint8_t NumericType::EncodeBitDepth(std::uint8_t bit_depth) {
  std::uint8_t code;
  for (code = 0; bit_depth > 0; ++code) {
    bit_depth = bit_depth >> 1;
  }
  return code - 4;
}

std::uint8_t NumericType::DecodeBitDepth(std::uint8_t code) {
  return 1 << (code + 3);
}

std::string NumericType::ScalarTypeName(ScalarType scalar) {
  switch (scalar) {
    case kScalarInt:
      return kScalarIntName;
    case kScalarUInt:
      return kScalarUIntName;
    case kScalarFloat:
      return kScalarFloatName;
  }
  return kUnknownName;
}

std::string NumericType::RankName(std::uint8_t rank) {
  switch (rank) {
    case 0:
      return kRankZeroName;
    case 1:
      return kRankOneName;
    case 2:
      return kRankTwoName;
  }
  return kUnknownName;
}

}  // namespace llama
