#include <sstream>

#include "base/error_code.h"
#include "gtest/gtest.h"

namespace llama {

void ExpectErrorCodeName(const std::string &code_name,
                         const std::string &error) {
  std::ostringstream sout;
  sout << "ERROR[" << code_name << "]";
  EXPECT_EQ(sout.str(), error);
}

TEST(ErrorCodeTest, TestErrorCodes) {
  const auto &codes = GetErrorCodes();
  EXPECT_EQ(4, codes.size());
  EXPECT_EQ(kSuccess, codes[0]);
  EXPECT_EQ(kErrorUnknown, codes[1]);
  EXPECT_EQ(kErrorFailedPrecondition, codes[2]);
}

TEST(ErrorCodeTest, TestErrorCodeString) {
  static const std::vector<std::string> code_names = {
    "", "Unknown", "Failed Precondition", "Unimplemented",
  };

  const auto &codes = GetErrorCodes();

  std::ostringstream sout;
  sout << codes[0];
  EXPECT_EQ("Success", sout.str());

  for (size_t i = 1; i < codes.size(); ++i) {
    sout.str("");
    sout << codes[i];
    ExpectErrorCodeName(code_names[i], sout.str());
  }
}

} // namespace llama
