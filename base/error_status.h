#ifndef LLAMA_ERROR_STATUS_H
#define LLAMA_ERROR_STATUS_H

#include <string>

#include "base/error_code.h"

namespace llama {

class ErrorStatus {
 public:
  // Create a status object, which will default to success.
  ErrorStatus();

  // Create a status object from an error code and message.
  ErrorStatus(ErrorCode code, std::string message);

  // Default copy and move constructors.
  ErrorStatus(const ErrorStatus& status) = default;
  ErrorStatus(ErrorStatus&& status) = default;

  // Returns true if status indicates that there was an error
  bool IsError() const { return m_code != kSuccess; }

  // Returns the error code of this status object.
  ErrorCode GetCode() const { return m_code; }

  // Returns the error message of this status object.
  std::string GetMessage() const { return m_message; }

  // Default copy and move assignment operators.
  ErrorStatus& operator= (const ErrorStatus& status) = default;
  ErrorStatus& operator= (ErrorStatus&& status) = default;

 private:
  ErrorCode   m_code;
  std::string m_message;
};

ErrorStatus Success();
ErrorStatus UnknownError(const std::string& message);
ErrorStatus FailedPrecondtionError(const std::string& message);

}  // namespace llama

#endif // LLAMA_ERROR_STATUS_H
