#include "base/type.h"
#include "gtest/gtest.h"

namespace llama {

  TEST(NumericTypeTest, TestIntTypeParams) {
    static const std::uint8_t int_bit_depths[] = {8, 16, 32, 64};
    static const std::uint8_t bad_bit_depths[] = {2, 4, 5, 31, 127, 128};

    for (std::uint8_t bit_depth : int_bit_depths) {
      type int_type = type::make_int(bit_depth);
      EXPECT_TRUE(int_type.is_defined());
      EXPECT_TRUE(int_type.is_numeric());
      EXPECT_TRUE(int_type.is_scalar());
      EXPECT_EQ(numeric_type::kScalarInt, int_type.get_scalar_type());
      EXPECT_EQ(bit_depth, int_type.get_bit_depth());
    }

    for (std::uint8_t bit_depth : bad_bit_depths) {
      // TODO(kree): Test behavior of bad bit depths.
    }
  }

  TEST(NumericTypeTest, TestTypeName) {
    EXPECT_EQ("int8",  type_name<std::int8_t>());
    EXPECT_EQ("int16", type_name<std::int16_t>());
    EXPECT_EQ("int32", type_name<std::int32_t>());
    EXPECT_EQ("int64", type_name<std::int64_t>());

    EXPECT_EQ("uint8",  type_name<std::uint8_t>());
    EXPECT_EQ("uint16", type_name<std::uint16_t>());
    EXPECT_EQ("uint32", type_name<std::uint32_t>());
    EXPECT_EQ("uint64", type_name<std::uint64_t>());

    EXPECT_EQ("float32", type_name<float>());
    EXPECT_EQ("float64", type_name<double>());
  }
}
