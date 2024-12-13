#ifndef CTS_MEM_H
#define CTS_MEM_H

#include "cts_types_def.h"

CTS_C_BEGIN

#define CTS_MEM_ALLOC(size) cts_mem_alloc(size, __FILE__, __LINE__)

void* cts_mem_alloc(uint32_t size, const char* filename, const char* line);

typedef struct _cts_mem_hook_t {
  void* (*cts_mem_alloc_hook_t)(uint32_t size);
  void (*cts_mem_free_hook_t)(void* ptr);
} cts_mem_hook_t;

ret_t cts_mem_set_hook(cts_mem_hook_t)

CTS_C_END

#endif /*!CTS_MEM_H*/