#include "base/value.h"
#include "gtest/gtest.h"

namespace llama {

TEST(ValueTest, TestAllocateFreeValue) {
  Value::Ptr value;
  ErrorStatus status = Value::Allocate<int>(&value);
  ASSERT_FALSE(status.IsError());
  status = Value::Free(value.get());
  ASSERT_FALSE(status.IsError());
  value.release();
}

TEST(ValueTest, TestGetData) {
  ErrorStatus status;
  Value::Ptr int_value;
  status = Value::Allocate<int>(&int_value);
  ASSERT_FALSE(status.IsError());
  *int_value->GetMutableData<int>()  = 13331;
  EXPECT_EQ(13331, int_value->GetData<int>());

  Value::Ptr float_value;
  status = Value::Allocate<float>(&float_value);
  ASSERT_FALSE(status.IsError());
  *float_value->GetMutableData<float>()  = 1.570796;
  EXPECT_FLOAT_EQ(1.570796, float_value->GetData<float>());
}

}  // namespace llama
