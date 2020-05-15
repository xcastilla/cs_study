#include <string.h>
#include "malloc.h"
#include <unistd.h>
#include <stdio.h>
#include <sys/mman.h>

static block_t *FREE_LIST_HEAD_ = NULL;
block_t* find_fl_block_(block_t *fl_head, size_t size);
block_t* allocate_block_(size_t size);
void remove_fl_block_(block_t *block);
void add_fl_block_(block_t *block);

void* malloc(size_t size) {
    block_t *block = NULL;
    if(size <= 0) {
        return NULL;
    }
    // First allocation
    if(!FREE_LIST_HEAD_) {
        block = allocate_block_(size);
        if(!block) {
            return NULL;
        }
    }
    else {
        // First, we try to find a free block that is big enough
        block = find_fl_block_(FREE_LIST_HEAD_, size);
        // If we fail to find it, we need to allocate a new block
        if(!block) {
            block = allocate_block_(size);
        }
        // Otherwise we remove the block from the free list
        else {
            fputs("Found existing available block in the free list.\n", stderr);
            remove_fl_block_(block);
        }
    }

    return block;
}


void* calloc(size_t nelem, size_t elsize) {
    size_t size = nelem * elsize;
    void *addr = malloc(size);
    if(addr) {
        memset(addr, 0, size);
    }
    return addr;
}


void* realloc(void *ptr, size_t size) {
    if(!ptr) {
        return malloc(size);
    }
    block_t *block = ((void*)ptr - sizeof(block_t));
    // If we have enough space in the block, return as it is for now
    if(block->block_size >= size) {
        return ((void*)ptr + sizeof(block_t));
    }
    // We allocate a new block, copy the memory from the old one and free it
    void *new_block = malloc(size);
    if(!new_block) {
        return NULL;
    }
    else {
        memcpy(new_block, ptr, block->block_size);
        free(ptr);
    }
    return new_block;
}


void free(void *ptr) {
    if(!ptr) {
        return;
    }
    // First, we subtract the size of a block from the address to get the meta
    // information for the block
    block_t *addr = ((void*)ptr - sizeof(block_t));
    // Then, we add the block to the free list
    add_fl_block_(addr);
}

block_t* find_fl_block_(block_t *fl_head, size_t size) {
    block_t *cur = fl_head;
    fputs("Trying to find free block\n", stderr);
    while(cur != NULL && cur->block_size < size) {
        cur = cur->next_block;
    }
    if(!cur) return NULL;
    return (void*)cur + sizeof(block_t);
}

block_t* allocate_block_(size_t size) {
    block_t *alloc_block_ = NULL;
    size = size + sizeof(block_t);
    fputs("Allocating new memory from malloc.\n", stderr);
    alloc_block_ = mmap(NULL, size, PROT_READ | PROT_WRITE, MAP_PRIVATE | MAP_ANONYMOUS, -1, 0);

    // Check for errors in sbrk call
    if(alloc_block_ == (void*)-1) {
        return NULL;
    }

    // Otherwise, alloc_block_ will contain the address of the
    // of the newly allocated block, and the heap will have been
    // incremented by size + _BLOCK_SIZE_ bytes
    alloc_block_->next_block = NULL;
    alloc_block_->prev_block = NULL;
    alloc_block_->block_size = size - sizeof(block_t);

    // We return the address of the memory region of the allocated block
    // excluding the header
    return ((void*)alloc_block_ + sizeof(block_t));
}


void remove_fl_block_(block_t *block) {
    fputs("Removing block from the free list\n", stderr);
    block = (void*)block - sizeof(block_t);
    if(!block) return;

    // Check if the block is the last on in the list and update the list head pointer
    // accordingly
    if(block == FREE_LIST_HEAD_) {
        FREE_LIST_HEAD_ = NULL;
        return;
    }
    // Point adjacent blocks to each other skipping the current block
    if(block->prev_block) {
        block->prev_block->next_block = block->next_block;
    }
    if(block->next_block) {
        block->next_block->prev_block = block->prev_block;
    }
    block->prev_block = NULL;
    block->next_block = NULL;
}


void add_fl_block_(block_t *block) {
    fputs("Adding block to the free list\n", stderr);
    if(FREE_LIST_HEAD_) {
        FREE_LIST_HEAD_->prev_block = block;
    }
    block->next_block = FREE_LIST_HEAD_;
    FREE_LIST_HEAD_ = block;
}
