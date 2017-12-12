#ifndef LLAMA_NUMERIC_TYPE_H
#define LLAMA_NUMERIC_TYPE_H

#include <cassert>
#include <cstdint>
#include <initializer_list>
#include <string>

namespace llama {

// Numeric types parameters:
//   bits 8-9:   scalar (0 = int, 1 = uint, 2 = float)
//   bits 10-11: rank (0 = scalar, 1 = vector, 2 = matrix, 3 = ignored)
//   bits 12-15: bit-depth (0 = 8-bit, 1 = 16-bit, 2 = 32-bit, 3 = 64-bit)
//   bits 16-31: dims (each 8 bytes specify a dim, only rank #'s read)
class NumericType {
 public:
  enum ScalarType { kScalarInt = 0, kScalarUInt = 1, kScalarFloat = 2 };

  // Encodes a numeric type with the given parameters.
  static std::uint32_t Encode(ScalarType scalar, std::uint8_t bit_depth,
                              std::initializer_list<std::uint8_t> dims);

  static ScalarType GetScalarType(std::uint32_t code) {
    std::uint32_t scalar = (code & kMaskScalar) >> kShiftScalar;
    return static_cast<ScalarType>(scalar);
  }

  static std::uint8_t GetRank(std::uint32_t code) {
    return (code & kMaskRank) >> kShiftRank;
  }

  static std::uint8_t GetBitDepth(std::uint32_t code) {
    return DecodeBitDepth((code & kMaskBitDepth) >> kShiftBitDepth);
  }

  static std::uint8_t GetRowDim(std::uint32_t code) {
    return (code & kMaskRowDim) >> kShiftRowDim;
  }

  static std::uint8_t GetColDim(std::uint32_t code) {
    return (code & kMaskColDim) >> kShiftColDim;
  }

  static size_t GetSize(std::uint32_t code);

  static std::string GetName(std::uint32_t code);

 private:
  // Bit shifts for the numeric type parameters:
  static constexpr std::uint32_t kShiftScalar = 8;
  static constexpr std::uint32_t kShiftRank = 10;
  static constexpr std::uint32_t kShiftBitDepth = 12;
  static constexpr std::uint32_t kShiftRowDim = 16;
  static constexpr std::uint32_t kShiftColDim = 24;

  // Bit masks for the numeric type parameters:
  static constexpr std::uint32_t kMaskScalar = 0x00000300;
  static constexpr std::uint32_t kMaskRank = 0x00000c00;
  static constexpr std::uint32_t kMaskBitDepth = 0x0000f000;
  static constexpr std::uint32_t kMaskRowDim = 0x00ff0000;
  static constexpr std::uint32_t kMaskColDim = 0xff000000;

  // Returns true if the given bit depth is valid for the specified scalar
  // type.
  static bool ValidateBitDepth(ScalarType scalar, std::uint8_t bit_depth);

  // Returns an encoded bit depth, which is suitable for storing in 2
  // bits. Mathematically, if b is the bit depth, this function will return c
  // such that:
  //
  //   b = 2^(c + 3);
  //
  static std::uint8_t EncodeBitDepth(std::uint8_t bit_depth);

  // Returns the bit depth, given a 2-bit code returned by the above function.
  static std::uint8_t DecodeBitDepth(std::uint8_t code);

  // Returns a string that identifies the specified scalar type.
  static std::string ScalarTypeName(ScalarType scalar);

  // Returns a string that identifies the rank of the numeric type.
  static std::string RankName(std::uint8_t rank);

  NumericType() {}
};

}  // namespace llama

#endif  // LLAMA_NUMERIC_TYPE_H
