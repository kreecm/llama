#ifndef LLAMA_ERROR_HANDLER_H
#define LLAMA_ERROR_HANDLER_H

#include <functional>

#include "base/error_status.h"

namespace llama {

using ErrorHandler = std::function<void (ErrorStatus)>;

void SetErrorHandler(ErrorHandler handler);

void HandleError(ErrorStatus status);

void Assert(bool condition, const std::string& message);

}  // namespace llama

#endif // LLAMA_ERROR_HANDLER_H

