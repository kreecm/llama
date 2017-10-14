#include "base/type.h"
#include "gtest/gtest.h"

namespace llama {

  TEST(NumericTypeTest, TestIntTypeParams) {
    static const std::uint8_t int_bit_depths[] = {8, 16, 32, 64};

    for (std::uint8_t bit_depth : int_bit_depths) {
      type int_type = type::make_int(bit_depth);
      EXPECT_TRUE(int_type.is_defined());
      EXPECT_TRUE(int_type.is_numeric());
      EXPECT_TRUE(int_type.is_scalar());
      EXPECT_EQ(numeric_type::kScalarInt, int_type.get_scalar_type());
      EXPECT_EQ(bit_depth, int_type.get_bit_depth());
    }
  }

}
