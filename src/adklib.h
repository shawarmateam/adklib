#ifndef __ADK_LIB_STANDART
#define __ADK_LIB_STANDART
#include <adklib_settings.h>
#define size_t unsigned int
#define NULL 0

#ifdef ADKLIB_ENABLE_PUTCHAR
#define ADKLIB_ENABLE_PRINT
#define ADKLIB_MEMORY_ENABLE
void print(const char * msg);
void *malloc(size_t size);
void free(void *ptr);
void putchar(char c)
{
    char * addr_c = malloc(2);
    addr_c[0]=c;
    print(addr_c);
    free(addr_c);
}
#endif


#ifdef ADKLIB_MEMORY_ENABLE
#ifndef ADKLIB_MEMORY_POOL_SIZE
#define ADKLIB_MEMORY_POOL_SIZE 1024
#endif

static char memory_pool[ADKLIB_MEMORY_POOL_SIZE];
static size_t used_memory = 0;

typedef struct Block {
    size_t size;
    struct Block* next;
} Block;

static Block* free_list = NULL;




void* malloc(size_t size) {
    size = (size + sizeof(size_t) - 1) & ~(sizeof(size_t) - 1);
    size += sizeof(Block);

    if (used_memory + size > ADKLIB_MEMORY_POOL_SIZE) {
        return NULL;
    }

    Block* block = (Block*)(memory_pool + used_memory);
    block->size = size;
    block->next = free_list;
    free_list = block;

    used_memory += size;
    return (void*)(block + 1);
}

void free(void* ptr) {
    if (ptr == NULL) return;
    Block* block = (Block*)ptr - 1;
    block->next = free_list;
    free_list = block;
}
#endif // ADKLIB_MEMORY_ENABLE



#ifdef ADKLIB_ENABLE_PRINT
void print(const char * msg)
{
    long msg_len = 0;
    while (msg[msg_len]!=0) ++msg_len;

    asm (
        "movq $1, %%rax;"      // syscall: sys_write
        "movq $1, %%rdi;"      // file descriptor: stdout
        "movq %0, %%rsi;"      // pointer to message
        "movq %1, %%rdx;"     // message length
        "syscall;"             // call kernel
        : 
        : "r"(msg), "r"(msg_len)
        : "%rax", "%rdi", "%rsi", "%rdx"
    );
}
#endif

#ifdef ADKLIB_ENABLE_BOOL
#define bool char
#define true 0xff
#define false 0x00
#endif

#endif // __ADK_LIB_STANDART
