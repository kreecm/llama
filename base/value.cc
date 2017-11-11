#include "base/value.h"

namespace llama {
namespace {

void DeleteValue(Value* value) {
  ErrorStatus status = Value::Free(value);
  Assert(!status.IsError(), "Failed to free value: " + status.GetMessage());
}

}

ErrorStatus Value::Allocate(Type type, Ptr* value) {
  size_t mem_size = sizeof(Type) + type.GetSize();
  void* mem = malloc(mem_size);
  Value* new_value = new (mem) Value(type);
  ErrorStatus status = new_value->Initialize();
  if (status.IsError()) {
    free(mem);
    return status;
  }
  *value = Ptr(new_value, DeleteValue);
  return Success();
}

ErrorStatus Value::Free(Value* value) {
  auto finalize = value->GetType().GetFinalizer();
  RETURN_IF_ERROR(finalize(value->GetDataPtr()));
  void* mem = reinterpret_cast<void*>(value);
  free(mem);
  return Success();
}

ErrorStatus Value::Initialize() {
  auto initialize = m_type.GetInitializer();
  return initialize(GetDataPtr());
}

void* Value::GetDataPtr() {
  uint8_t* ptr = reinterpret_cast<uint8_t*>(this);
  ptr += sizeof(Type);
  return reinterpret_cast<void*>(ptr);
}

const void* Value::GetConstDataPtr() const {
  const uint8_t* ptr = reinterpret_cast<const uint8_t*>(this);
  ptr += sizeof(Type);
  return reinterpret_cast<const void*>(ptr);
}

}  // namespace llama
