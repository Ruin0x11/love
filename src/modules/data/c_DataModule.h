#ifndef LOVE_DATA_C_DATA_MODULE_H
#define LOVE_DATA_C_DATA_MODULE_H

#include "common/config.h"
#include "common/c_wrap.h"
#include "modules/love_c/types.h"

#include "love_c/c_Data.h"
#include "c_ByteData.h"
#include "c_CompressedData.h"
#include "c_DataView.h"

LOVE_C_EXTERN_C_BEGIN

typedef enum LoveC_Data_EncodeFormat {
  ENCODE_BASE64,
  ENCODE_HEX,
  ENCODE_MAX_ENUM
} LoveC_Data_EncodeFormat;

typedef enum LoveC_Data_ContainerType {
  CONTAINER_DATA,
  CONTAINER_STRING,
  CONTAINER_MAX_ENUM
} LoveC_Data_ContainerType;

typedef enum LoveC_Data_Compressor_Format {
  FORMAT_LZ4,
  FORMAT_ZLIB,
  FORMAT_GZIP,
  FORMAT_DEFLATE,
  FORMAT_MAX_ENUM
} LoveC_Data_Compressor_Format;

typedef enum LoveC_Data_HashFunction_Function {
  FUNCTION_MD5,
  FUNCTION_SHA1,
  FUNCTION_SHA224,
  FUNCTION_SHA256,
  FUNCTION_SHA384,
  FUNCTION_SHA512,
  FUNCTION_MAX_ENUM
} LoveC_Data_HashFunction_Function;

typedef struct LoveC_Data_HashFunction_Value {
  char data[64]; // Maximum possible size (SHA512).
  LoveC_SizeT size;
} LoveC_Data_HashFunction_Value;

LOVE_EXPORT LoveC_Result love_data_newDataView(LoveC_DataRef dataRef, LoveC_SizeT offset, LoveC_SizeT size, LoveC_Data_DataViewRef* outDataView, char** outError);
LOVE_EXPORT LoveC_Result love_data_newByteData(LoveC_SizeT size, LoveC_Data_ByteDataRef* outByteData, char** outError);
LOVE_EXPORT LoveC_Result love_data_newByteData__data(const char* data, LoveC_SizeT size, LoveC_Data_ByteDataRef* outByteData, char** outError);
LOVE_EXPORT LoveC_Result love_data_compress(LoveC_Data_Compressor_Format format, const char *rawbytes, LoveC_SizeT rawsize, LoveC_Data_CompressedDataRef* outCdata, LoveC_SizeT* outCompressedsize, char **outError);
LOVE_EXPORT LoveC_Result love_data_decompress(LoveC_Data_Compressor_Format format, const char *compressedbytes, LoveC_SizeT compressedsize, char** outRawbytes, LoveC_SizeT* outRawsize, char **outError);
LOVE_EXPORT LoveC_Result love_data_decompress__CompressedData(LoveC_Data_Compressor_Format format, LoveC_Data_CompressedDataRef dataRef, char** outRawbytes, LoveC_SizeT* outRawsize, char **outError);
LOVE_EXPORT LoveC_Result love_data_encode(LoveC_Data_EncodeFormat format, const char *src, LoveC_SizeT srclen, char** outDst, LoveC_SizeT* outSize, char **outError);
LOVE_EXPORT LoveC_Result love_data_encode__Data(LoveC_Data_EncodeFormat format, LoveC_DataRef dataRef, char** outDst, LoveC_SizeT* outSize, char **outError);
LOVE_EXPORT LoveC_Result love_data_decode(LoveC_Data_EncodeFormat format, const char *src, LoveC_SizeT srclen, char** outDst, LoveC_SizeT* outSize, char **outError);
LOVE_EXPORT LoveC_Result love_data_decode__Data(LoveC_Data_EncodeFormat format, LoveC_DataRef dataRef, char** outDst, LoveC_SizeT* outSize, char **outError);
LOVE_EXPORT LoveC_Result love_data_hash(LoveC_Data_HashFunction_Function function, const char *rawbytes, LoveC_SizeT rawsize, LoveC_Data_HashFunction_Value *outValue, char **outError);
LOVE_EXPORT LoveC_Result love_data_hash__Data(LoveC_Data_HashFunction_Function function, LoveC_DataRef rawdataRef, LoveC_Data_HashFunction_Value* outValue, char** outError);

LOVE_EXPORT LoveC_Result love_data_registerModule(char **outError);

LOVE_C_EXTERN_C_END

#endif // LOVE_DATA_C_DATA_MODULE_H
