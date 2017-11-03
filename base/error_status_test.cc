#include "base/error_status.h"
#include "gtest/gtest.h"

namespace llama {

TEST(ErrorStatusTest, TestErrorStatusAccessors) {
  ErrorStatus status;
  status = ErrorStatus();
  EXPECT_FALSE(status.IsError());
  EXPECT_EQ(kSuccess, status.GetCode());

  status = ErrorStatus(kErrorUnknown, "unknown error message");
  EXPECT_TRUE(status.IsError());
  EXPECT_EQ(kErrorUnknown, status.GetCode());
  EXPECT_EQ("unknown error message", status.GetMessage());

  status = ErrorStatus(kErrorFailedPrecondition,
                       "failed precondition error message");
  EXPECT_TRUE(status.IsError());
  EXPECT_EQ(kErrorFailedPrecondition, status.GetCode());
  EXPECT_EQ("failed precondition error message", status.GetMessage());
}

} // namespace llama
