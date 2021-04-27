#ifndef LOVE_C_WRAP
#define LOVE_C_WRAP

#define DEFINE_C_WRAPPER_FUNCTIONS(ty, ref)     \
  ty *unwrap(ref P) {                            \
    return reinterpret_cast<ty*>(P);                    \
  }                                                     \
                                                        \
  ref wrap(const ty *P) {                        \
    return reinterpret_cast<ref>(const_cast<ty*>(P));   \
  }

#ifdef __clang__
#define LOVE_C_STRICT_PROTOTYPES_BEGIN                                         \
  _Pragma("clang diagnostic push")                                             \
      _Pragma("clang diagnostic error \"-Wstrict-prototypes\"")
#define LOVE_C_STRICT_PROTOTYPES_END _Pragma("clang diagnostic pop")
#else
#define LOVE_C_STRICT_PROTOTYPES_BEGIN
#define LOVE_C_STRICT_PROTOTYPES_END
#endif

#ifdef __cplusplus
#define LOVE_C_EXTERN_C_BEGIN                                                  \
  extern "C" {                                                                 \
  LOVE_C_STRICT_PROTOTYPES_BEGIN
#define LOVE_C_EXTERN_C_END                                                    \
  LOVE_C_STRICT_PROTOTYPES_END                                                 \
  }
#else
#define LOVE_C_EXTERN_C_BEGIN LOVE_C_STRICT_PROTOTYPES_BEGIN
#define LOVE_C_EXTERN_C_END LOVE_C_STRICT_PROTOTYPES_END
#endif

#endif // LOVE_C_WRAP
