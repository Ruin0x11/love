// LOVE
#include "common/version.h"

#include "love_c.h"

const char *love_version()
{
	// Do not refer to love::VERSION here, the linker
	// will patch it back up to the executable's one..
	return LOVE_VERSION_STRING;
}
