#include "base/error_code.h"

namespace llama {

const std::vector<ErrorCode>& GetErrorCodes() {
  const static std::vector<ErrorCode> kErrorCodes = {
    kSuccess,
    kErrorUnknown,
    kErrorFailedPrecondition,
    kErrorUnimplemented,
  };
  return kErrorCodes;
}

std::string ErrorCodeToString(ErrorCode code) {
  switch (code) {
    case kSuccess:
      return "Success";
    case kErrorUnknown:
      return "ERROR[Unknown]";
    case kErrorFailedPrecondition:
      return "ERROR[Failed Precondition]";
    case kErrorUnimplemented:
      return "ERROR[Unimplemented]";
  }
  return "";
}

std::ostream& operator<< (std::ostream& out, ErrorCode code) {
  out << ErrorCodeToString(code);
  return out;
}

}  // namespace llama
