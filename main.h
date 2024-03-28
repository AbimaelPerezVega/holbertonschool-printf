#ifndef MAIN_H
#define MAIN_H
#include <stdarg.h>
#include <stdio.h>
#include <unistd.h>

#define UNUSed(x) (void)(x)
#define BUFF_SIZE 1024

/* FLAGS */
#define F_MINUS 1
#define F_PLUS 2
#define F_ZERO 4
#define F_HASH 8
#define F_SPACE 16
/* SIZE */
#define S_LONG 2
#define S_SHORT 1
/**
 *struct fmt - struct up
 *L0MAX
 *@fmt: the format
 *@fn: the function associated
 *
*/
struct fmt
{
char fmt;
int (*fn)(va_list, char[], int, int, int, int);
};
/**
 *typedef struct fmt fmt_t - struct op
 *
 *@fmt: the format
 *@fm_t: the function associated
 *
*/
typedef struct fmt fmt_t;

int _printf(const char *format, ...);
int handle_print(const char *fmt, int *i,
va_list list, char buffer[], int flags, int width, int precision, int size);

/***FUNCTIONS***/
/*Functions to print chars and strings*/
int print_char(va_list types, char buffer[],
		int flags, int width, int precision, int size);
int print_string(va_list types, char buffer[],
		int flags, int width, int precision, int size);
int print_percent(va_list types, char buffer[],
		int flags, int width, int precision, int size);
/*Functions to print numbers*/
int print_int(va_list types, char buffer[],
int flags, int width, int precision, int size);
int print_binary(va_list types, char buffer[],
int flags, int width, int precision, int size);
int print_unsigned(va_list types, char buffer[],
int flags, int width, int precision, int size);
int print_octal(va_list types, char buffer[],
int flags, int width, int precision, int size);
int print_hexadecimal(va_list types, char buffer[],
int flags, int width, int precision, int size);
int print_hexa_upper(va_list types, char buffer[],
int flags, int width, int precision, int size);
int print_hexa(va_list types, char buffer[],
int flags, int width, int precision, int size);

/*Function to print non printable characters */
int print_non_printable(va_list types, char buffer[],
int flags, int width, int precision, int size);
#endif /* MAIN_H */
