#include "base/error_status.h"

namespace llama {

ErrorStatus::ErrorStatus() : m_code(kSuccess) {}

ErrorStatus::ErrorStatus(ErrorCode code, std::string message)
    : m_code(code),
      m_message(message)
{}

ErrorStatus Success() {
  return ErrorStatus();
}

ErrorStatus UnknownError(const std::string& message) {
  return ErrorStatus(kErrorUnknown, message);
}

ErrorStatus FailedPrecondtionError(const std::string& message) {
  return ErrorStatus(kErrorFailedPrecondition, message);
}


ErrorStatus UnimplementedError(const std::string& message) {
  return ErrorStatus(kErrorUnimplemented, message);
}

}  // namespace llama
