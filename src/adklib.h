#ifndef __ADK_LIB_STANDART
#define __ADK_LIB_STANDART
#include <adklib_settings.h>
#define size_t unsigned int
#define NULL 0

#ifdef ADKLIB_ENABLE_PRINT
#define ADKLIB_ENABLE_PUTCHAR
void putchar(char c); // fn: print; deps: putchar
void print(const char * str)
{
    while (*str) {
        putchar(*str);
        str++;
    }
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



#ifdef ADKLIB_ENABLE_PUTCHAR
#define ADKLIB_ENABLE_WRITE
long write(int fd, const char *buf, long count);

void putchar(char c)
{
    write(1, &c, 1);
}
#endif

#ifdef ADKLIB_ENABLE_WRITE
long write(int fd, const char *buf, long count) {
    long ret;
    asm volatile (
        "syscall"
        : "=a" (ret)
        : "a" (1),
          "D" (fd),
          "S" (buf),
          "d" (count)
        : "rcx", "r11", "memory"
    );
    return ret;
}
#endif

#ifdef ADKLIB_ENABLE_BOOL
#define bool char
#define true 0xff
#define false 0x00
#endif

#endif // __ADK_LIB_STANDART
