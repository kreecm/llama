#include "base/error_handler.h"

#include <cstdlib>
#include <iostream>
#include <mutex>

namespace llama {
namespace {

void DefaultErrorHandler(ErrorStatus status) {
  if (status.IsError()) {
    std::cerr << status.GetCode() << ": " << status.GetMessage() << "\n";
    std::exit(static_cast<int>(status.GetCode()));
  }
}

class ErrorHandlerProvider {
 public:
  static const ErrorHandler& GetHandler() {
    std::lock_guard<std::mutex> lock(s_mutex);
    if (!s_handler) {
      s_handler = DefaultErrorHandler;
    }
    return s_handler;
  }

  static void SetHandler(ErrorHandler handler) {
    std::lock_guard<std::mutex> lock(s_mutex);
    s_handler = std::move(handler);
  }

 private:
  static ErrorHandler s_handler;
  static std::mutex   s_mutex;
};

ErrorHandler ErrorHandlerProvider::s_handler;
std::mutex   ErrorHandlerProvider::s_mutex;

}  // namespace

void SetErrorHandler(ErrorHandler handler) {
  ErrorHandlerProvider::SetHandler(handler);
}

void HandleError(ErrorStatus status) {
  const auto& handler = ErrorHandlerProvider::GetHandler();
  handler(status);
}

void Assert(bool condition, const std::string& message) {
  if (!condition) {
    ErrorStatus status(kErrorFailedPrecondition, message);
    HandleError(status);
  }
}

}  // namespace llama
