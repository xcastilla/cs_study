#ifndef __BLOCK_H__
#define __BLOCK_H__

#include <sys/types.h>

typedef struct block {
    size_t block_size;
    struct block *next_block;
    struct block *prev_block;
} block_t;

#endif /* __BLOCK_H__ */
