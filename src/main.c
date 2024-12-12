#include "adklib.h"

int main()
{
    printf("test string!\nchar: %c\nstr: %s\nnum: %d\nfloat: %f\n", 'A', "this is const char", 123, 3.1415);
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

char buff[count];
*format -= (count+1);
count = 0;
while (52<=format<62)        // заполнение buff
{
    buff[count++] = format;
    *format++;
}


*/
