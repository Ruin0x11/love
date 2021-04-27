#include "c_FileData.h"

#include "common/c_wrap.h"
#include "common/Module.h"
#include "common/runtime.h"

#include "modules/love_c/runtime_c.h"

#include "FileData.h"

using namespace love;
using namespace love::filesystem;


void love_filesystem_FileData_getFilename(LoveC_FileDataRef ref, const char** outFilename) {
  auto real = unwrap<FileData>(ref);
  *outFilename = real->getFilename().c_str();
}

void love_filesystem_FileData_getExtension(LoveC_FileDataRef ref, const char** outExtension) {
  auto real = unwrap<FileData>(ref);
  *outExtension = real->getExtension().c_str();
}

void love_filesystem_FileData_getName(LoveC_FileDataRef ref, const char** outName) {
  auto real = unwrap<FileData>(ref);
  *outName = real->getName().c_str();
}
