// LOVE
#include "common/version.h"

#include "modules/filesystem/c_Filesystem.h"

#include "love_c.h"

LoveC_Bool love_c_init(char** error) {
  if (!love_filesystem_registerModule(error)) {
    return false;
  }

  return true;
}

const char *love_c_version()
{
	// Do not refer to love::VERSION here, the linker
	// will patch it back up to the executable's one..
	return LOVE_VERSION_STRING;
}
