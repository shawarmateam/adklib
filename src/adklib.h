#ifndef __ADK_LIB_STANDART
#define __ADK_LIB_STANDART
#include <adklib_settings.h>

#define MEMORY_POOL_SIZE 1024
#define size_t unsigned int
#define NULL 0
static char memory_pool[MEMORY_POOL_SIZE];
static size_t used_memory = 0;

void* malloc(size_t size) {
    size = (size + sizeof(size_t) - 1) & ~(sizeof(size_t) - 1);

    if (used_memory + size > MEMORY_POOL_SIZE) {
        return NULL;
    }

    void* ptr = memory_pool + used_memory;
    used_memory += size;
    return ptr;
}

#ifdef ADKLIB_ENABLE_PUTCHAR
#define ADKLIB_ENABLE_PRINT
void print(const char * msg);
void putchar(char c)
{
    char * addr_c = malloc(2);
    addr_c[0]=c;
    print(addr_c);
}
#endif

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
