#ifndef LOVE_C_RUNTIME_C_H
#define LOVE_C_RUNTIME_C_H

#include "types.h"

#include "common/runtime.h"

namespace love
{
namespace love_c
{

LoveC_Bool register_module(const WrappedModule& m, char** error);

}
}

#endif // LOVE_C_RUNTIME_C_H
