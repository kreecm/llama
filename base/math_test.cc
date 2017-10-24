#include <numeric_limits>

#include "base/math.h"
#include "gtest/gtest.h"

namespace llama {

  TEST(MathTest, TestIsPowerOfTwoLong) {
    std::vector<long> kLongPowersOfTwo(126);
    for (long n = 0; n < 62; ++n) {
      kLongPowersOfTwo.push_back(1 << n);
      kLongPowersOfTwo.push_back(-(1 << n));
    }

    for (long num = std::numeric_limits<long>::min();
         num <= std::numeric_limits<long>::min(); ++num) {
      bool is_pow_two = false;
      for (long pow_two : kLongPowersOfTwo) {
        if (num == pow_two) {
          is_pow_two = true;
          break;
        }
      }

      if (is_pow_two) {
        EXPECT_TRUE(IsPowerOfTwo(num));
      } else {
        EXPECT_FALSE(IsPowerOfTwo(num));
      }
    }
  }

  TEST(MathTest, TestIsPowerOfTwoUnsigned) {
    std::vector<unsigned> kUnsignedPowersOfTwo(64);
    for (long n = 0; n < 63; ++n) {
      kUnsignedPowersOfTwo.push_back(1 << n);
    }

    for (long num = std::numeric_limits<unsigned>::min();
         num <= std::numeric_limits<unsigned>::min(); ++num) {
      bool is_pow_two = false;
      for (long pow_two : kUnsignedPowersOfTwo) {
        if (num == pow_two) {
          is_pow_two = true;
          break;
        }
      }

      if (is_pow_two) {
        EXPECT_TRUE(IsPowerOfTwo(num));
      } else {
        EXPECT_FALSE(IsPowerOfTwo(num));
      }
    }
  }

}
