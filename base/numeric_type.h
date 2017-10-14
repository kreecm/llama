#ifndef LLAMA_NUMERIC_TYPE_H
#define LLAMA_NUMERIC_TYPE_H

#include <cassert>
#include <cstdint>
#include <initializer_list>
#include <iostream>

namespace llama {

  // Numeric types parameters:
  //   byte 4-5:   scalar (0 = int, 1 = uint, 2 = float)
  //   byte 6-7:   rank (0 = scalar, 1 = vector, 2 = matrix, 3 = ignored)
  //   byte 8-11:  bit-depth (0 = 8-bit, 1 = 16-bit, 2 = 32-bit, 3 = 64-bit)
  //   byte 12-27: dims (each 8 bytes specify a dim, only rank #'s read) 
  class numeric_type {
  public:

    enum scalar_type {
      kScalarInt   = 0,
      kScalarUInt  = 1,
      kScalarFloat = 2
    };

    // Encodes a numeric type with the given parameters.
    static std::uint32_t encode(scalar_type scalar,
				std::uint8_t bit_depth,
				std::initializer_list<std::uint8_t> dims);
    
    static scalar_type get_scalar_type(std::uint32_t code) {
      std::uint32_t scalar = (code & kMaskScalar) >> kShiftScalar;
      return static_cast<scalar_type>(scalar);
    }

    static std::uint8_t get_rank(std::uint32_t code) {
      return (code & kMaskRank) >> kShiftRank;
    }

    static std::uint8_t get_bit_depth(std::uint32_t code) {
      return decode_bit_depth((code & kMaskBitDepth) >> kShiftBitDepth);
    }

    static std::uint8_t get_row_Dim(std::uint32_t code) {
      return (code & kMaskRowDim) >> kShiftRowDim;
    }

    static std::uint8_t get_col_dim(std::uint32_t code) {
      return (code & kMaskColDim) >> kShiftColDim;
    }

  private:
    // Shifts and masks for numeric types:
    static constexpr std::uint32_t kShiftScalar   = 4;
    static constexpr std::uint32_t kShiftRank     = 6;
    static constexpr std::uint32_t kShiftBitDepth = 8;
    static constexpr std::uint32_t kShiftRowDim   = 12;
    static constexpr std::uint32_t kShiftColDim   = 20;

    static constexpr std::uint32_t kMaskScalar    = 0x30;
    static constexpr std::uint32_t kMaskRank      = 0xc0; 
    static constexpr std::uint32_t kMaskBitDepth  = 0xf00;
    static constexpr std::uint32_t kMaskRowDim    = 0xff000;
    static constexpr std::uint32_t kMaskColDim    = 0xff00000;

    static bool validate_bit_depth(scalar_type scalar, std::uint8_t bit_depth);
    static std::uint8_t encode_bit_depth(std::uint8_t bit_depth);
    static std::uint8_t decode_bit_depth(std::uint8_t code);
 
    numeric_type() {}
  };

}  // namespace llama

#endif  // LLAMA_NUMERIC_TYPE_H
