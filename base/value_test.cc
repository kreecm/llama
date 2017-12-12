#include "base/value.h"
#include "gtest/gtest.h"

namespace llama {

TEST(ValueTest, TestConstructAndDelete) {
  Value* value = new Value(TypeOf<int>());
  EXPECT_EQ(TypeOf<int>(), value->GetType());
  delete value;
}

TEST(ValueTest, TestGetData) {
  Value int_value(TypeOf<int>());
  *int_value.GetMutable<int>() = 13331;
  EXPECT_EQ(13331, int_value.Get<int>());

  Value float_value(TypeOf<float>());
  *float_value.GetMutable<float>() = 1.570796;
  EXPECT_FLOAT_EQ(1.570796, float_value.Get<float>());
}

}  // namespace llama
