#include "base/value_ptr.h"
#include "gtest/gtest.h"

namespace llama {

constexpr int kTestIntValue = 13331;
constexpr float kTestFloatValue = 1.570796;

TEST(ValuePtrTest, TestValuePtr) {
  Value int_value(TypeOf<int>());
  *int_value.GetMutable<int>() = kTestIntValue;
  EXPECT_EQ(TypeOf<int>(), int_value.GetType());
  EXPECT_EQ(kTestIntValue, int_value.Get<int>());
  ValuePtr int_ptr(&int_value);
  EXPECT_EQ(TypeOf<int>(), int_ptr.GetType());
  EXPECT_EQ(kTestIntValue, int_ptr.Get<int>());
  EXPECT_EQ(int_value.GetDataPtr(), int_ptr.GetDataPtr());

  Value float_value(TypeOf<float>());
  *float_value.GetMutable<float>() = kTestFloatValue;
  EXPECT_EQ(TypeOf<float>(), float_value.GetType());
  EXPECT_EQ(kTestFloatValue, float_value.Get<float>());
  ValuePtr float_ptr(&float_value);
  EXPECT_EQ(TypeOf<float>(), float_ptr.GetType());
  EXPECT_EQ(kTestFloatValue, float_ptr.Get<float>());
  EXPECT_EQ(float_value.GetDataPtr(), float_ptr.GetDataPtr());
}

TEST(ValuePtrTest, TestExternalValuePtr) {
  int int_value = kTestIntValue;
  ValuePtr int_ptr(&int_value);
  EXPECT_EQ(TypeOf<int>(), int_ptr.GetType());
  EXPECT_EQ(kTestIntValue, int_ptr.Get<int>());
  EXPECT_EQ(&int_value, int_ptr.GetDataPtr());

  float float_value = kTestFloatValue;
  ValuePtr float_ptr(&float_value);
  EXPECT_EQ(TypeOf<float>(), float_ptr.GetType());
  EXPECT_FLOAT_EQ(kTestFloatValue, float_ptr.Get<float>());
  EXPECT_EQ(&float_value, float_ptr.GetDataPtr());
}

TEST(ValuePtrTest, TestMutableValuePtr) {
  Value int_value(TypeOf<int>());
  *int_value.GetMutable<int>() = kTestIntValue;
  EXPECT_EQ(TypeOf<int>(), int_value.GetType());
  EXPECT_EQ(kTestIntValue, int_value.Get<int>());
  MutableValuePtr int_ptr(&int_value);
  EXPECT_EQ(TypeOf<int>(), int_ptr.GetType());
  EXPECT_EQ(kTestIntValue, int_ptr.Get<int>());
  EXPECT_EQ(int_value.GetDataPtr(), int_ptr.GetDataPtr());
  *int_ptr.GetMutable<int>() = 33;
  EXPECT_EQ(33, int_ptr.Get<int>());
  EXPECT_EQ(33, int_value.Get<int>());

  Value float_value(TypeOf<float>());
  *float_value.GetMutable<float>() = kTestFloatValue;
  EXPECT_EQ(TypeOf<float>(), float_value.GetType());
  EXPECT_FLOAT_EQ(kTestFloatValue, float_value.Get<float>());
  MutableValuePtr float_ptr(&float_value);
  EXPECT_EQ(TypeOf<float>(), float_ptr.GetType());
  EXPECT_FLOAT_EQ(kTestFloatValue, float_ptr.Get<float>());
  EXPECT_EQ(float_value.GetDataPtr(), float_ptr.GetDataPtr());
  *float_ptr.GetMutable<float>() = 2.71828;
  EXPECT_FLOAT_EQ(2.71828, float_ptr.Get<float>());
  EXPECT_FLOAT_EQ(2.71828, float_value.Get<float>());
}

TEST(ValuePtrTest, TestExternalMutableValuePtr) {
  int int_value = kTestIntValue;
  MutableValuePtr int_ptr(&int_value);
  EXPECT_EQ(TypeOf<int>(), int_ptr.GetType());
  EXPECT_EQ(kTestIntValue, int_ptr.Get<int>());
  EXPECT_EQ(&int_value, int_ptr.GetDataPtr());
  *int_ptr.GetMutable<int>() = 33;
  EXPECT_EQ(33, int_ptr.Get<int>());
  EXPECT_EQ(33, int_value);

  float float_value = kTestFloatValue;
  MutableValuePtr float_ptr(&float_value);
  EXPECT_EQ(TypeOf<float>(), float_ptr.GetType());
  EXPECT_FLOAT_EQ(kTestFloatValue, float_ptr.Get<float>());
  EXPECT_EQ(&float_value, float_ptr.GetDataPtr());
  *float_ptr.GetMutable<float>() = 2.71828;
  EXPECT_FLOAT_EQ(2.71828, float_ptr.Get<float>());
  EXPECT_FLOAT_EQ(2.71828, float_value);
}

}  // namespace llama
