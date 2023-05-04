
#include "ompx/memory.h"
#include "omp.h"

_LIBOMPX_NAMESPACE_BEGIN

extern "C" void *_LIBOMPX_C_FN(malloc)(size_t size) {
  if (size <= 0)
    return nullptr;
  return omp_target_alloc(size, omp_get_default_device());
}

_LIBOMPX_NAMESPACE_END
