#include "adklib.h"

int main()
{
    //printf("test string!\nchar: %c\nstr: %s\nnum: %d\nfloat: %f\n", 'A', "this is const char", 123, 3.1415);
    printf("%2d\n", 123); // TODO: исправить баг с printf
    //int c = 0;
    //putnum(5, 123456, &c);
    putflt(2, 123.1415, 1);
    return 0;
}
// "%99d", 123
// 52<=x<62 // тут <= чтобы была посхалочка 52
/*

int count = 0;
while (52<=format<62)        // размер под buff
{
    count++;
    *format++;
}

if (count == 0) <запуск формата без обреза>

char buff[count];
*format -= (count+1);
count = 0;
while (52<=format<62)        // заполнение buff
{
    buff[count++] = format;
    *format++;
}

switch (*format)
{
    case 'd':
        int d = __builtin_va_arg(args, int);
        int c = 0;
        int cut = str2int(buff);
        putnum(cut, d, &c);
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
        float cut = str2flt(buff);
        int cuti = (int)cut;
        float frac = cut-cuti;
        while ((frac-(int)frac)) frac*=10;
        int cutf = (int)frac;

        putflt(cuti, (float)f, cutf);
        break;
    case '%':
    default:
        putchar('%');
}
*/
