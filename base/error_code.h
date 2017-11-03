#ifndef LLAMA_ERROR_CODE_H
#define LLAMA_ERROR_CODE_H

#include <iostream>
#include <string>
#include <vector>

namespace llama {

enum ErrorCode {
  kSuccess = 0,
  kErrorUnknown,
  kErrorFailedPrecondition,
};

const std::vector<ErrorCode>& GetErrorCodes();

std::string ErrorCodeToString(ErrorCode code);

std::ostream& operator<< (std::ostream& out, ErrorCode code);

}  // namespace llama

#endif // LLAMA_ERROR_CODE_H
