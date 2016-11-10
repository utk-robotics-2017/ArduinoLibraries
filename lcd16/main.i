# 1 "main.c"
# 1 "Z:\\mixed\\electronics\\avrcode\\others\\lcd16//"
# 1 "<built-in>"
# 1 "<command line>"
# 1 "main.c"
# 12 "main.c"
# 1 "C:/WinAVR/bin/../lib/gcc/avr/3.4.3/../../../../avr/include/stdlib.h" 1 3
# 47 "C:/WinAVR/bin/../lib/gcc/avr/3.4.3/../../../../avr/include/stdlib.h" 3
# 1 "C:/WinAVR/bin/../lib/gcc/avr/3.4.3/include/stddef.h" 1 3 4
# 213 "C:/WinAVR/bin/../lib/gcc/avr/3.4.3/include/stddef.h" 3 4
typedef unsigned int size_t;
# 325 "C:/WinAVR/bin/../lib/gcc/avr/3.4.3/include/stddef.h" 3 4
typedef int wchar_t;
# 48 "C:/WinAVR/bin/../lib/gcc/avr/3.4.3/../../../../avr/include/stdlib.h" 2 3
# 66 "C:/WinAVR/bin/../lib/gcc/avr/3.4.3/../../../../avr/include/stdlib.h" 3
typedef struct {
 int quot;
 int rem;
} div_t;


typedef struct {
 long quot;
 long rem;
} ldiv_t;


typedef int (*__compar_fn_t)(const void *, const void *);
# 100 "C:/WinAVR/bin/../lib/gcc/avr/3.4.3/../../../../avr/include/stdlib.h" 3
extern __inline__ void abort(void) __attribute__((__noreturn__));




extern __inline__ void
abort(void)
{
 for (;;);
}




extern int abs(int __i) __attribute__((__const__));
# 123 "C:/WinAVR/bin/../lib/gcc/avr/3.4.3/../../../../avr/include/stdlib.h" 3
extern long labs(long __i) __attribute__((__const__));
# 146 "C:/WinAVR/bin/../lib/gcc/avr/3.4.3/../../../../avr/include/stdlib.h" 3
extern void *bsearch(const void *__key, const void *__base, size_t __nmemb,
       size_t __size, int (*__compar)(const void *, const void *));







extern div_t div(int __num, int __denom) __asm__("__divmodhi4") __attribute__((__const__));





extern ldiv_t ldiv(long __num, long __denom) __asm__("__divmodsi4") __attribute__((__const__));
# 178 "C:/WinAVR/bin/../lib/gcc/avr/3.4.3/../../../../avr/include/stdlib.h" 3
extern void qsort(void *__base, size_t __nmemb, size_t __size,
    __compar_fn_t __compar);
# 211 "C:/WinAVR/bin/../lib/gcc/avr/3.4.3/../../../../avr/include/stdlib.h" 3
extern long strtol(const char *__nptr, char **__endptr, int __base);
# 245 "C:/WinAVR/bin/../lib/gcc/avr/3.4.3/../../../../avr/include/stdlib.h" 3
extern unsigned long strtoul(const char *__nptr, char **__endptr, int __base);
# 255 "C:/WinAVR/bin/../lib/gcc/avr/3.4.3/../../../../avr/include/stdlib.h" 3
extern __inline__ long atol(const char *__nptr) __attribute__((__pure__));
extern __inline__ long
atol(const char *__nptr)
{
 return strtol(__nptr, (char **) 0, 10);
}
# 279 "C:/WinAVR/bin/../lib/gcc/avr/3.4.3/../../../../avr/include/stdlib.h" 3
extern int atoi(const char *) __attribute__((__pure__));
# 291 "C:/WinAVR/bin/../lib/gcc/avr/3.4.3/../../../../avr/include/stdlib.h" 3
extern void exit(int __status) __attribute__((__noreturn__));
# 303 "C:/WinAVR/bin/../lib/gcc/avr/3.4.3/../../../../avr/include/stdlib.h" 3
extern void *malloc(size_t __size) __attribute__((__malloc__));






extern void free(void *__ptr);




extern size_t __malloc_margin;




extern char *__malloc_heap_start;




extern char *__malloc_heap_end;






extern void *calloc(size_t __nele, size_t __size) __attribute__((__malloc__));
# 351 "C:/WinAVR/bin/../lib/gcc/avr/3.4.3/../../../../avr/include/stdlib.h" 3
extern void *realloc(void *__ptr, size_t __size) __attribute__((__malloc__));
# 383 "C:/WinAVR/bin/../lib/gcc/avr/3.4.3/../../../../avr/include/stdlib.h" 3
extern double strtod(const char *__nptr, char **__endptr);
# 394 "C:/WinAVR/bin/../lib/gcc/avr/3.4.3/../../../../avr/include/stdlib.h" 3
extern double atof(const char *__nptr);
# 416 "C:/WinAVR/bin/../lib/gcc/avr/3.4.3/../../../../avr/include/stdlib.h" 3
extern int rand(void);



extern void srand(unsigned int __seed);






extern int rand_r(unsigned long *ctx);
# 458 "C:/WinAVR/bin/../lib/gcc/avr/3.4.3/../../../../avr/include/stdlib.h" 3
extern char *itoa(int __val, char *__s, int __radix);
# 486 "C:/WinAVR/bin/../lib/gcc/avr/3.4.3/../../../../avr/include/stdlib.h" 3
extern char *ltoa(long int __val, char *__s, int __radix);
# 512 "C:/WinAVR/bin/../lib/gcc/avr/3.4.3/../../../../avr/include/stdlib.h" 3
extern char *utoa(unsigned int __val, char *__s, int __radix);
# 538 "C:/WinAVR/bin/../lib/gcc/avr/3.4.3/../../../../avr/include/stdlib.h" 3
extern char *ultoa(unsigned long int __val, char *__s, int __radix);
# 556 "C:/WinAVR/bin/../lib/gcc/avr/3.4.3/../../../../avr/include/stdlib.h" 3
extern long random(void);




extern void srandom(unsigned long __seed);







extern long random_r(unsigned long *ctx);
# 611 "C:/WinAVR/bin/../lib/gcc/avr/3.4.3/../../../../avr/include/stdlib.h" 3
extern char *dtostre(double __val, char *__s, unsigned char __prec,
       unsigned char __flags);
# 626 "C:/WinAVR/bin/../lib/gcc/avr/3.4.3/../../../../avr/include/stdlib.h" 3
extern char *dtostrf(double __val, char __width, char __prec, char *__s);
# 13 "main.c" 2


# 1 "C:/WinAVR/bin/../lib/gcc/avr/3.4.3/../../../../avr/include/string.h" 1 3
# 45 "C:/WinAVR/bin/../lib/gcc/avr/3.4.3/../../../../avr/include/string.h" 3
# 1 "C:/WinAVR/bin/../lib/gcc/avr/3.4.3/include/stddef.h" 1 3 4
# 46 "C:/WinAVR/bin/../lib/gcc/avr/3.4.3/../../../../avr/include/string.h" 2 3
# 64 "C:/WinAVR/bin/../lib/gcc/avr/3.4.3/../../../../avr/include/string.h" 3
extern void *memccpy(void *, const void *, int, size_t);
extern void *memchr(const void *, int, size_t) __attribute__((__pure__));
extern int memcmp(const void *, const void *, size_t) __attribute__((__pure__));
extern void *memcpy(void *, const void *, size_t);
extern void *memmove(void *, const void *, size_t);
extern void *memset(void *, int, size_t);
extern char *strcat(char *, const char *);
extern char *strchr(const char *, int) __attribute__((__pure__));
extern int strcmp(const char *, const char *) __attribute__((__pure__));
extern char *strcpy(char *, const char *);
extern int strcasecmp(const char *, const char *) __attribute__((__pure__));
extern size_t strlcat(char *, const char *, size_t);
extern size_t strlcpy(char *, const char *, size_t);
extern size_t strlen(const char *) __attribute__((__pure__));
extern char *strlwr(char *);
extern char *strncat(char *, const char *, size_t);
extern int strncmp(const char *, const char *, size_t) __attribute__((__pure__));
extern char *strncpy(char *, const char *, size_t);
extern int strncasecmp(const char *, const char *, size_t) __attribute__((__pure__));
extern size_t strnlen(const char *, size_t) __attribute__((__pure__));
extern char *strrchr(const char *, int) __attribute__((__pure__));
extern char *strrev(char *);
extern char *strsep(char **, const char *);
extern char *strstr(const char *, const char *) __attribute__((__pure__));
extern char *strtok_r(char *, const char *, char **);
extern char *strupr(char *);
# 16 "main.c" 2
# 1 "C:/WinAVR/bin/../lib/gcc/avr/3.4.3/../../../../avr/include/math.h" 1 3
# 93 "C:/WinAVR/bin/../lib/gcc/avr/3.4.3/../../../../avr/include/math.h" 3
extern double cos(double __x) __attribute__((__const__));







extern double fabs(double __x) __attribute__((__const__));
# 118 "C:/WinAVR/bin/../lib/gcc/avr/3.4.3/../../../../avr/include/math.h" 3
extern double fmod(double __x, double __y) __attribute__((__const__));
# 130 "C:/WinAVR/bin/../lib/gcc/avr/3.4.3/../../../../avr/include/math.h" 3
extern double modf(double __value, double *__iptr);







extern double sin(double __x) __attribute__((__const__));






extern double sqrt(double __x) __attribute__((__const__));







extern double tan(double __x) __attribute__((__const__));







extern double floor(double __x) __attribute__((__const__));







extern double ceil(double __x) __attribute__((__const__));
# 183 "C:/WinAVR/bin/../lib/gcc/avr/3.4.3/../../../../avr/include/math.h" 3
extern double frexp(double __value, int *__exp);
# 197 "C:/WinAVR/bin/../lib/gcc/avr/3.4.3/../../../../avr/include/math.h" 3
extern double ldexp(double __x, int __exp) __attribute__((__const__));






extern double exp(double _x) __attribute__((__const__));






extern double cosh(double __x) __attribute__((__const__));






extern double sinh(double __x) __attribute__((__const__));






extern double tanh(double __x) __attribute__((__const__));
# 236 "C:/WinAVR/bin/../lib/gcc/avr/3.4.3/../../../../avr/include/math.h" 3
extern double acos(double __x) __attribute__((__const__));
# 247 "C:/WinAVR/bin/../lib/gcc/avr/3.4.3/../../../../avr/include/math.h" 3
extern double asin(double __x) __attribute__((__const__));
# 258 "C:/WinAVR/bin/../lib/gcc/avr/3.4.3/../../../../avr/include/math.h" 3
extern double atan(double __x) __attribute__((__const__));
# 269 "C:/WinAVR/bin/../lib/gcc/avr/3.4.3/../../../../avr/include/math.h" 3
extern double atan2(double __y, double __x) __attribute__((__const__));
# 278 "C:/WinAVR/bin/../lib/gcc/avr/3.4.3/../../../../avr/include/math.h" 3
extern double log(double __x) __attribute__((__const__));
# 287 "C:/WinAVR/bin/../lib/gcc/avr/3.4.3/../../../../avr/include/math.h" 3
extern double log10(double __x) __attribute__((__const__));






extern double pow(double __x, double __y) __attribute__((__const__));







extern int isnan(double __x) __attribute__((__const__));







extern int isinf(double __x) __attribute__((__const__));
# 320 "C:/WinAVR/bin/../lib/gcc/avr/3.4.3/../../../../avr/include/math.h" 3
extern double square(double __x) __attribute__((__const__));
# 329 "C:/WinAVR/bin/../lib/gcc/avr/3.4.3/../../../../avr/include/math.h" 3
extern double inverse(double) __attribute__((__const__));
# 17 "main.c" 2
# 1 "lcd.h" 1
# 9 "lcd.h"
extern void InitLCD(void);
extern void SendCommand(unsigned char value);
extern void SendString(char *pt, int line, int position);
extern void SendFloat(float value, int line, int position);
extern void SendLong(long number, int line, int position);
extern void SendInt(int number, int line, int position);
extern void sprintl(long number, char *pt);
# 18 "main.c" 2




int main(void);

int main(void)
{
    float fnum;
    long lnum;
    int inum;


    outp(0xff, PORTB);
    outp(0xff, DDRB);

    outp(0x00, PORTA);
    outp(0xff, DDRA);

    InitLCD();
    fnum = 0.0;
    lnum = 0L;
    inum = 0;

    while (1)
    {
        SendFloat(fnum, 1, 0);
        fnum = fnum + 1.0;

        SendString("value", 1, 11);

        SendLong(lnum, 2, 0);
        lnum++;

        SendString("      ", 2, 10);
        SendInt(inum, 2, 10);
        inum++;
    }

    return 0;
}
