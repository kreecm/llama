#ifndef LLAMA_ERROR_H
#define LLAMA_ERROR_H

#include "base/error_code.h"
#include "base/error_status.h"
#include "base/error_handler.h"

#define RETURN_IF_ERROR(status)                 \
  if (status.IsError()) {                       \
    return status;                              \
  }                                             \

#define CHECK_SUCCESS(status) llama::HandleError(status)

#endif // LLAMA_ERROR_H
