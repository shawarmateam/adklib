#ifndef __ADK_LIB_STANDART
#define __ADK_LIB_STANDART
#include <adklib_settings.h>
#define size_t unsigned int
#define NULL 0




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

#ifdef ADKLIB_ENABLE_PRINTF
#define ADKLIB_ENABLE_PUTNUM
#define ADKLIB_ENABLE_PRINT
#define ADKLIB_ENABLE_PUTFLT
#define ADKLIB_ENABLE_STR2INT
#define ADKLIB_ENABLE_STR2FLT
void putchar(char c);
void putnum0(int num);
void putflt0(float flt);
void putnum(int cut, int num, int *count);
void putflt(int cuti, float flt, int cutf);
int  str2int(const char * str);
float str2flt(const char * str);
void print(const char * str);
void printf(const char * format, ...)
{
    __builtin_va_list args;
    __builtin_va_start(args, format);

    while (*format)
    {
        if (*format == '%')
        {
            format++;
            putnum0(*format);
            putchar(' ');
            if (!(*format > 47 && *format < 58))
            {
                switch (*format)
                {
                    case 'd':
                        int d = __builtin_va_arg(args, int);
                        putnum0(d);
                        break;
                    case 'c':
                        int c = __builtin_va_arg(args, int);
                        putchar((char)c);
                        break;
                    case 's':
                        const char * str = __builtin_va_arg(args, const char *);
                        print(str);
                        break;
                    case 'f':
                        double f = __builtin_va_arg(args, double);
                        putflt0((float)f);
                        break;
                    case '%':
                    default:
                        putchar('%');
                }
            }
            else
            {
                print("in else\n");
                int count = 0;
                while (*format > 47 && *format < 58)        // размер под buff
                {
                    count++;
                    format++;
                }

                char buff[count];
                format -= count;
                count = 0;
                while (*format > 47 && *format < 58)        // заполнение buff
                {
                    buff[count++] = *format;
                    format++;
                }

                putchar(buff[0]);
                putchar(*format);
                switch (*format)
                {
                    case 'd':
                        int d = __builtin_va_arg(args, int);
                        int c = 0;
                        const char * addr_buff = buff;
                        putchar('\n');
                        print(addr_buff);
                        int cut = str2int(addr_buff);
                        putnum0(cut);
                        putnum(cut, d, &c);
                        break;
                    case 's': // TODO: сделать обрез для строки
                        const char * str = __builtin_va_arg(args, const char *);
                        print(str);
                        break;
                    case 'f':
                        double f = __builtin_va_arg(args, double);
                        //float cut = str2flt(buff);
                        //int cuti = (int)cut;
                        //float frac = cut-cuti;
                        //while ((frac-(int)frac)) frac*=10;
                        //int cutf = (int)frac;

                        //putflt(cuti, (float)f, cutf);
                        break;
                    case '%':
                    default:
                        putchar('%');
                }
            }
        } else putchar(*format);
        format++;
    }

    __builtin_va_end(args);
}
#endif

#ifdef ADKLIB_ENABLE_MULTIARG
#define va_list          __builtin_va_list
#define va_start(v, ...) __builtin_va_start(v, 0)
#define va_start(v,l)    __builtin_va_arg(v,l)
#define va_arg(v,l)      __builtin_va_arg(v,l)
#define va_end(v)        __builtin_va_end(v)
#endif

#ifdef ADKLIB_ENABLE_FMOD
#define fmod(x, y) ( \
    (y) == .0f \
        ? .0f \
        : ((x) - ((int)((x) / (y))) * (y)))
#endif

#ifdef ADKLIB_ENABLE_PUTFLT
#define ADKLIB_ENABLE_PUTNUM
void putchar(char c);
void putnum0(int num);
void putnum(int cut, int num, int *count);

void putflt0(float flt)
{
    if (flt < 0)
    {
        putchar('-');
        flt = -flt;
    }

    int num = (int)flt;
    putnum0(num);
    putchar('.');
    flt = flt-num;

    while ( flt-(int)flt ) flt *= 10;
    num = (int)flt;
    putnum0(num);
}

void putflt(int cuti, float flt, int cutf)
{
    if (flt < 0)
    {
        putchar('-');
        flt = -flt;
    }

    int num = (int)flt;
    int c = 0;
    putnum(cuti, num, &c);
    putchar('.');
    flt = flt-num;

    while ( flt-(int)flt ) flt *= 10;
    num = (int)flt;
    cutf+=2;putnum(cutf, num, &c);
}

#endif


#ifdef ADKLIB_ENABLE_STR2INT
int str2int(const char * str)
{
    int ret = 0;
    for (int i=0; str[i]!=0; ++i)
    {
        if (i!=0)                    ret*=10;
        if (str[i]>=48&&str[i]<58)   ret+=(str[i]-48);  // ASCII 48 equals '0'
        else                         return 0;
    }
    return ret;
}
#endif

#ifdef ADKLIB_ENABLE_PRINT
#define ADKLIB_ENABLE_WRITE
long write(int fd, const char *buf, long count);
void print(const char * str)                        // fn: print; deps: write
{
    int i=0;
    while (str[i]!=0) ++i;
    write(1, str, i);
}
#endif



#ifdef ADKLIB_ENABLE_PUTNUM
#define ADKLIB_ENABLE_PUTCHAR
void putchar(char c);

void putnum0(int num)
{
    if (num == 0)
    {
        putchar('0');
        return;
    }

    if (num < 0)
    {
        putchar('-');
        num = -num;
    }

    if (num / 10)
    {
        putnum0(num / 10);
    }

    putchar((num % 10) + '0');
}

void putnum(int cut, int num, int *count)
{
    if (*count >= cut)
        return;

    if (num == 0 && *count == 0)
    {
        putchar('0');
        (*count)++;
        return;
    }

    if (num < 0)
    {
        putchar('-');
        (*count)++;
        num = -num;
    }

    if (num / 10)
    {
        putnum(cut, num / 10, count);
    }

    if (*count < cut)
    {
        putchar((num % 10) + '0');
        (*count)++;
    }
}
#endif



#ifdef ADKLIB_ENABLE_PUTCHAR
#define ADKLIB_ENABLE_WRITE
long write(int fd, const char *buf, long count);

void putchar(char c)                  // fn: putchar; deps: write
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
