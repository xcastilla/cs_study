#ifndef __MALLOC_H__
#define __MALLOC_H__

#include "block.h"

void* malloc(size_t size);
void* calloc(size_t nelem, size_t elsize);
void* realloc(void *ptr, size_t size);
void free(void *ptr);

#endif /* __MALLOC_H__ */
