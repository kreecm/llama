#include "base/type.h"
#include "gtest/gtest.h"

namespace llama {

  TEST(NumericTypeTest, TestIntTypeParams) {
    constexpr std::uint8_t int_bit_depths[] = {8, 16, 32, 64};
    for (std::uint8_t bit_depth : int_bit_depths) {
      Type int_type = Type::Int(bit_depth);
      EXPECT_TRUE(int_type.IsDefined());
      EXPECT_TRUE(int_type.IsNumeric());
      EXPECT_TRUE(int_type.IsScalar());
      EXPECT_EQ(NumericType::kScalarInt, int_type.GetScalarType());
      EXPECT_EQ(bit_depth, int_type.GetBitDepth());
    }

    // TODO(kree): Test behavior of bad bit depths.
    // constexpr std::uint8_t bad_bit_depths[] = {2, 4, 5, 31, 127, 128};
    // for (std::uint8_t bit_depth : bad_bit_depths) {
    // }
  }

  TEST(NumericTypeTest, TestTypeName) {
    EXPECT_EQ("int8",  TypeName<std::int8_t>());
    EXPECT_EQ("int16", TypeName<std::int16_t>());
    EXPECT_EQ("int32", TypeName<std::int32_t>());
    EXPECT_EQ("int64", TypeName<std::int64_t>());

    EXPECT_EQ("uint8",  TypeName<std::uint8_t>());
    EXPECT_EQ("uint16", TypeName<std::uint16_t>());
    EXPECT_EQ("uint32", TypeName<std::uint32_t>());
    EXPECT_EQ("uint64", TypeName<std::uint64_t>());

    EXPECT_EQ("float32", TypeName<float>());
    EXPECT_EQ("float64", TypeName<double>());
  }
}
