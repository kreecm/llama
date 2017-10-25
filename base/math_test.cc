#include <limits>
#include <random>

#include "base/math.h"
#include "gtest/gtest.h"

namespace llama {

  class MathTest : public ::testing::Test {
  protected:

    template <typename IntType>
    IntType RandomInt() {
      static std::random_device device;
      static std::mt19937 rand(device());
      static std::uniform_int_distribution<IntType>
          dist(std::numeric_limits<IntType>::min(),
               std::numeric_limits<IntType>::max());
      return dist(rand);
    }

    template <typename IntType>
    void TestPowersOfTwo(const std::vector<IntType>& powers_of_two) {
      constexpr int kNumberOfRandomIntsToTest = 1000000;
      for (IntType num : powers_of_two) {
        EXPECT_TRUE(IsPowerOfTwo(num));
      }
      int count = 0;
      while (count < kNumberOfRandomIntsToTest) {
        IntType num = RandomInt<IntType>();
        bool is_pow_two = false;
        for (IntType pow_two : powers_of_two) {
          if (num == pow_two) {
            is_pow_two = true;
            break;
          }
        }
        if (is_pow_two) {
          continue;
        }
        EXPECT_FALSE(IsPowerOfTwo(num));
        count++;
      }
    }
  };

  TEST_F(MathTest, TestIsPowerOfTwoLong) {
    std::vector<long> kLongPowersOfTwo(126);
    for (long n = 0; n < 62; ++n) {
      kLongPowersOfTwo.push_back(1 << n);
      kLongPowersOfTwo.push_back(-(1 << n));
    }
    TestPowersOfTwo(kLongPowersOfTwo);
  }

  TEST_F(MathTest, TestIsPowerOfTwoUnsigned) {
    std::vector<unsigned> kUnsignedPowersOfTwo(64);
    for (long n = 0; n < 63; ++n) {
      kUnsignedPowersOfTwo.push_back(1 << n);
    }
    TestPowersOfTwo(kUnsignedPowersOfTwo);
  }

}
