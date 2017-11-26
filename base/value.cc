#include "base/value.h"

namespace llama {

constexpr size_t Value::kInPlaceValueSize = sizeof(std::string);

const void* Value::GetDataPtr() const final {
  if (IsInPlace()) {
    return reinterpret_cast<const void*>(m_data.in_place);
  } else {
    return m_data.ptr;
  }
}

void* Value::GetMutableDataPtr() final {
  if (IsInPlace()) {
    return reinterpret_cast<void*>(m_data.in_place);
  } else {
    return m_data.ptr;
  }
}

bool Value::IsInPlace() const {
  return GetType().GetSize() <= kInPlaceValueSize;
}

void Value::Initialize() {
  if (!IsInPlace()) {
    m_data.ptr = malloc(GetType().GetSize());
  }

  auto init = GetType().GetInitializer();
  init(GetMutableDataPtr());
}

void Value::Move(Value&& value) {
  auto move = GetType().GetMover();
  move(value.GetMutableDataPtr(), GetMutableDataPtr());
}

void Value::Copy(const Value& value) {
  auto copy = GetType().GetCopier();
  copy(value.GetDataPtr(), GetMutableDataPtr());
}

void Value::Delete() {
  auto finish = GetType().GetFinalizer();
  finish(GetMutableDataPtr());

  if (!IsInPlace()) {
    free(m_data.ptr);
  }
}

}  // namespace llama
