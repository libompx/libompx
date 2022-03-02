///===--------------------------------------------------------------------===///
///= Part of the libompx project. Consult the LICENCE.txt file if required. =///
///===--------------------------------------------------------------------===///
///==                                                                      ==///
///=                                                                        =///
///==                                                                      ==///
///===--------------------------------------------------------------------===///

#ifndef LIBOMPX_UTILS_H
#define LIBOMPX_UTILS_H

#include <assert.h>
#include <stdint.h>

// Adapted from
// https://stackoverflow.com/questions/824639/variadic-recursive-preprocessor-macros-is-it-possible/5048661#5048661
#define _LIBOMPX_CONC_IMPL(X, Y) X##Y
#define _LIBOMPX_CONC(X, Y) _LIBOMPX_CONC_IMPL(X, Y)

#define _LIBOMPX_NAME_OF_1(a) (a)
#define _LIBOMPX_NAME_OF_2(a, b) _LIBOMPX_CONC(a, b)

#define _LIBOMPX_NAME_OF_3(a, ...)                                             \
  _LIBOMPX_NAME_OF_2(a, _LIBOMPX_NAME_OF_2(__VA_ARGS__))
#define _LIBOMPX_NAME_OF_4(a, ...)                                             \
  _LIBOMPX_NAME_OF_2(a, _LIBOMPX_NAME_OF_3(__VA_ARGS__))
#define _LIBOMPX_NAME_OF_5(a, ...)                                             \
  _LIBOMPX_NAME_OF_2(a, _LIBOMPX_NAME_OF_4(__VA_ARGS__))
#define _LIBOMPX_NAME_OF_6(a, ...)                                             \
  _LIBOMPX_NAME_OF_2(a, _LIBOMPX_NAME_OF_5(__VA_ARGS__))
#define _LIBOMPX_NAME_OF_7(a, ...)                                             \
  _LIBOMPX_NAME_OF_2(a, _LIBOMPX_NAME_OF_6(__VA_ARGS__))
#define _LIBOMPX_NAME_OF_8(a, ...)                                             \
  _LIBOMPX_NAME_OF_2(a, _LIBOMPX_NAME_OF_7(__VA_ARGS__))

// NUM_ARGS(...) evaluates to the literal number of the passed-in arguments.
#define _NUM_ARGS2(X, X64, X63, X62, X61, X60, X59, X58, X57, X56, X55, X54,   \
                   X53, X52, X51, X50, X49, X48, X47, X46, X45, X44, X43, X42, \
                   X41, X40, X39, X38, X37, X36, X35, X34, X33, X32, X31, X30, \
                   X29, X28, X27, X26, X25, X24, X23, X22, X21, X20, X19, X18, \
                   X17, X16, X15, X14, X13, X12, X11, X10, X9, X8, X7, X6, X5, \
                   X4, X3, X2, X1, N, ...)                                     \
  N
#define NUM_ARGS(...)                                                          \
  _NUM_ARGS2(0, __VA_ARGS__, 64, 63, 62, 61, 60, 59, 58, 57, 56, 55, 54, 53,   \
             52, 51, 50, 49, 48, 47, 46, 45, 44, 43, 42, 41, 40, 39, 38, 37,   \
             36, 35, 34, 33, 32, 31, 30, 29, 28, 27, 26, 25, 24, 23, 22, 21,   \
             20, 19, 18, 17, 16, 15, 14, 13, 12, 11, 10, 9, 8, 7, 6, 5, 4, 3,  \
             2, 1, 0)

#define __LIBOMPX_NAME_OF_N3(N, ...) _LIBOMPX_NAME_OF_##N(__VA_ARGS__)
#define __LIBOMPX_NAME_OF_N2(N, ...) __LIBOMPX_NAME_OF_N3(N, __VA_ARGS__)
#define _LIBOMPX_NAME_OF_N(...)                                                \
  __LIBOMPX_NAME_OF_N2(NUM_ARGS(__VA_ARGS__), __VA_ARGS__)

#define LIBOMPX_NAME(...) _LIBOMPX_NAME_OF_N(__VA_ARGS__)

#define _LIBOMPX_NAME ompx
#define _LIBOMPX_NAME_PREFIX _LIBOMPX_CONC(_LIBOMPX_NAME, _)

#ifdef _LIBOMPX_BACKEND_NAME
#define _LIBOMPX_C_FN(_NAME, ...)                                              \
  _LIBOMPX_NAME_OF_N(_LIBOMPX_NAME_PREFIX, _LIBOMPX_BACKEND_NAME,_, _NAME, __VA_ARGS__)
#else
#define _LIBOMPX_C_FN(_NAME, ...)                                              \
  _LIBOMPX_NAME_OF_N(_LIBOMPX_NAME_PREFIX, _NAME, __VA_ARGS__)
#endif


#define _LIBOMPX_CXX_FN(_NAME, ...) _NAME

#ifdef __cplusplus

#define _LIBOMPX_NAMESPACE_NAME _LIBOMPX_NAME
#define _LIBOMPX_NAMESPACE_BEGIN namespace _LIBOMPX_NAMESPACE_NAME {
#define _LIBOMPX_NAMESPACE_END }

#ifdef _LIBOMPX_BACKEND_NAME
#define _LIBOMPX_BACKEND_NAMESPACE_BEGIN namespace _LIBOMPX_BACKEND_NAME {
#define _LIBOMPX_BACKEND_NAMESPACE_END }
#endif

#define _LIBOMPX_FN(_NAME, ...) _LIBOMPX_CXX_FN(_NAME)

#else

#define _LIBOMPX_NAMESPACE_NAME
#define _LIBOMPX_NAMESPACE_BEGIN
#define _LIBOMPX_NAMESPACE_END

#define _LIBOMPX_BACKEND_NAMESPACE_BEGIN
#define _LIBOMPX_BACKEND_NAMESPACE_END

#define _LIBOMPX_FN(_NAME, ...) _LIBOMPX_C_FN(_NAME, __VA_ARGS__)

#endif

#endif

///===--- vim: set ft=cpp sw=2 ts=2 sts=2 et: ----------------------------===///
