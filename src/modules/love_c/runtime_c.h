#ifndef LOVE_C_RUNTIME_C_H
#define LOVE_C_RUNTIME_C_H

#include "types.h"

#include "common/runtime.h"

template<typename T, typename R>
inline T* unwrap(R ref) {
  return reinterpret_cast<T*>(ref);
}

template<typename R, typename T>
inline R wrap(const T* ptr) {
  return reinterpret_cast<R>(const_cast<T*>(ptr));
}

namespace love
{
namespace love_c
{

LoveC_Result register_module(const WrappedModule& m, char** outError);

}
}

#endif // LOVE_C_RUNTIME_C_H
