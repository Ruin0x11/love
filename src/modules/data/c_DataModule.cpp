#include "c_DataModule.h"

#include "common/c_wrap.h"
#include "common/Module.h"
#include "common/runtime.h"

#include "modules/love_c/runtime_c.h"

#include "DataModule.h"

using namespace love;
using namespace love::data;

#define instance() (Module::getInstance<DataModule>(Module::M_DATA))

LOVE_EXPORT LoveC_Result love_data_newDataView(LoveC_DataRef dataRef, LoveC_SizeT offset, LoveC_SizeT size, LoveC_Data_DataViewRef* outDataView, char** outError) {
  auto data = unwrap<Data>(dataRef);

  DataView* d;

  try {
    d = instance()->newDataView(data, offset, size);
  } catch (const std::exception& e) {
    *outError = strdup(e.what());
    return false;
  }

  *outDataView = wrap<LoveC_Data_DataViewRef>(d);

  return true;
}

LOVE_EXPORT LoveC_Result love_data_newByteData(LoveC_SizeT size, LoveC_Data_ByteDataRef* outByteData, char** outError) {
  ByteData* d;

  try {
    d = instance()->newByteData(size);
  } catch (const std::exception& e) {
    *outError = strdup(e.what());
    return false;
  }

  *outByteData = wrap<LoveC_Data_ByteDataRef>(d);

  return true;
}

LOVE_EXPORT LoveC_Result love_data_newByteData__data(const char* data, LoveC_SizeT size, LoveC_Data_ByteDataRef* outByteData, char** outError) {
  ByteData* d;

  try {
    d = instance()->newByteData(data, size);
  } catch (const std::exception& e) {
    *outError = strdup(e.what());
    return false;
  }

  *outByteData = wrap<LoveC_Data_ByteDataRef>(d);

  return true;
}

LoveC_Result love_data_compress(LoveC_Data_Compressor_Format format, const char *rawbytes, LoveC_SizeT rawsize, LoveC_Data_CompressedDataRef* outCdata, LoveC_SizeT* outCompressedsize, char **outError) {
  auto format_ = static_cast<Compressor::Format>(format);
  CompressedData* cdata;
  size_t compressedsize;

  try {
    cdata = love::data::compress(format_, rawbytes, rawsize, compressedsize);
  } catch (const std::exception& e) {
    *outError = strdup(e.what());
    return false;
  }

  *outCdata = wrap<LoveC_Data_CompressedDataRef>(cdata);
  *outCompressedsize = compressedsize;

  return true;
}

LoveC_Result love_data_decompress(LoveC_Data_Compressor_Format format, const char *compressedbytes, LoveC_SizeT compressedsize, char** outRawbytes, LoveC_SizeT* outRawsize, char **outError) {
  auto format_ = static_cast<Compressor::Format>(format);
  char* rawbytes;
  size_t rawsize;

  try {
    rawbytes = love::data::decompress(format_, compressedbytes, compressedsize, rawsize);
  } catch (const std::exception& e) {
    *outError = strdup(e.what());
    return false;
  }

  *outRawbytes = rawbytes;
  *outRawsize = rawsize;

  return true;
}

LoveC_Result love_data_decompress__CompressedData(LoveC_Data_Compressor_Format format, LoveC_Data_CompressedDataRef dataRef, char** outRawbytes, LoveC_SizeT* outRawsize, char **outError) {
  auto format_ = static_cast<Compressor::Format>(format);
  auto data = unwrap<CompressedData>(dataRef);
  char* rawbytes;
  size_t rawsize;

  try {
    rawbytes = love::data::decompress(data, rawsize);
  } catch (const std::exception& e) {
    *outError = strdup(e.what());
    return false;
  }

  *outRawbytes = rawbytes;
  *outRawsize = rawsize;

  return true;
}

LoveC_Result love_data_decode(LoveC_Data_EncodeFormat format, const char *src, LoveC_SizeT srclen, char** outDst, LoveC_SizeT* outSize, char **outError) {
  auto format_ = static_cast<EncodeFormat>(format);
  char* dst;
  size_t dstlen;

  try {
    dst = love::data::decode(format_, src, srclen, dstlen);
  } catch (const std::exception& e) {
    *outError = strdup(e.what());
    return false;
  }

  *outDst = dst;
  *outSize = dstlen;

  return true;
}

LoveC_Result love_data_decode__Data(LoveC_Data_EncodeFormat format, LoveC_DataRef dataRef, char** outDst, LoveC_SizeT* outSize, char **outError) {
  auto format_ = static_cast<EncodeFormat>(format);
  auto data = unwrap<Data>(dataRef);
  char* dst;
  size_t dstlen;

  const char* src = (const char *) data->getData();
  size_t srclen = data->getSize();

  try {
    dst = love::data::decode(format_, src, srclen, dstlen);
  } catch (const std::exception& e) {
    *outError = strdup(e.what());
    return false;
  }

  *outDst = dst;
  *outSize = dstlen;

  return true;
}

LoveC_Result love_data_hash(LoveC_Data_HashFunction_Function function, const char* rawbytes, LoveC_SizeT rawsize, LoveC_Data_HashFunction_Value* outValue, char** outError) {
  auto function_ = static_cast<HashFunction::Function>(function);

  HashFunction::Value hashvalue;

  try {
    love::data::hash(function, rawbytes, rawsize, hashvalue);
  } catch (const std::exception& e) {
    *outError = strdup(e.what());
    return false;
  }

  memcpy(outValue->data, hashvalue.data, sizeof(outValue->data));
  outValue->size = hashvalue.size;

  return true;
}

LoveC_Result love_data_hash__Data(LoveC_Data_HashFunction_Function function, LoveC_DataRef rawdataRef, LoveC_Data_HashFunction_Value* outValue, char** outError) {
  auto function_ = static_cast<HashFunction::Function>(function);
  auto rawdata = unwrap<Data>(rawdataRef);

  HashFunction::Value hashvalue;

  try {
    love::data::hash(function, rawdata, hashvalue);
  } catch (const std::exception& e) {
    *outError = strdup(e.what());
    return false;
  }

  return true;
}

LoveC_Result love_data_registerModule(char** outError) {
  DataModule *instance = instance();
  if (instance == nullptr) {
    try {
      instance = new DataModule();
    } catch (const std::exception &e) {
      *outError = strdup(e.what());
      return false;
    }
  }

  WrappedModule w;
  w.module = instance;
  w.name = "data";
  w.type = &Module::type;
  w.functions = nullptr;
  w.types = nullptr;

  return love_c::register_module(w, outError);
}
