#include "base/value.h"
#include "gtest/gtest.h"

namespace llama {

constexpr int kTestIntValue = 13331;
constexpr float kTestFloatValue = 1.570796;

TEST(ValueTest, TestConstructAndDelete) {
  Value* value = new Value(TypeOf<int>());
  EXPECT_EQ(TypeOf<int>(), value->GetType());
  delete value;
}

TEST(ValueTest, TestGetData) {
  Value int_value(TypeOf<int>());
  *int_value.GetMutable<int>() = kTestIntValue;
  EXPECT_EQ(kTestIntValue, int_value.Get<int>());

  Value float_value(TypeOf<float>());
  *float_value.GetMutable<float>() = kTestFloatValue;
  EXPECT_FLOAT_EQ(kTestFloatValue, float_value.Get<float>());
}

TEST(ValueTest, TestCopy) {
  Value int_value(TypeOf<int>());
  *int_value.GetMutable<int>() = kTestIntValue;
  EXPECT_EQ(kTestIntValue, int_value.Get<int>());
  Value int_copy = int_value;
  EXPECT_EQ(TypeOf<int>(), int_copy.GetType());
  EXPECT_EQ(kTestIntValue, int_copy.Get<int>());

  Value float_value(TypeOf<float>());
  *float_value.GetMutable<float>() = kTestFloatValue;
  EXPECT_FLOAT_EQ(kTestFloatValue, float_value.Get<float>());
  Value float_copy = float_value;
  EXPECT_EQ(TypeOf<float>(), float_copy.GetType());
  EXPECT_EQ(kTestFloatValue, float_copy.Get<float>());
}

TEST(ValueTest, TestMove) {
  Value int_value(TypeOf<int>());
  *int_value.GetMutable<int>() = kTestIntValue;
  EXPECT_EQ(kTestIntValue, int_value.Get<int>());
  Value int_move = std::move(int_value);
  EXPECT_EQ(TypeOf<int>(), int_move.GetType());
  EXPECT_EQ(kTestIntValue, int_move.Get<int>());

  Value float_value(TypeOf<float>());
  *float_value.GetMutable<float>() = kTestFloatValue;
  EXPECT_FLOAT_EQ(kTestFloatValue, float_value.Get<float>());
  Value float_move = std::move(float_value);
  EXPECT_EQ(TypeOf<float>(), float_move.GetType());
  EXPECT_EQ(kTestFloatValue, float_move.Get<float>());
}

}  // namespace llama
