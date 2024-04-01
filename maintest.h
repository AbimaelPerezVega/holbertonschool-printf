#ifndef MAIN_H
#define MAIN_H

<<<<<<< HEAD
int _printf(const char *format, ...);
int _putchar(char c);
=======
#include <limits.h>
#include <stdarg.h>
#include <stdlib.h>
#include <unistd.h>

/* Flag Modifier Macros */
#define PLUS 1
#define SPACE 2
#define HASH 4
#define ZERO 8
#define NEG 16
#define PLUS_FLAG (flags & 1)
#define SPACE_FLAG ((flags >> 1) & 1)
#define HASH_FLAG ((flags >> 2) & 1)
#define ZERO_FLAG ((flags >> 3) & 1)
#define NEG_FLAG ((flags >> 4) & 1)

/* Length Modifier Macros */
#define SHORT 1
#define LONG 2

/**
 * struct buffer_s - new type defining a buffer struct
 * @buffer: pointer to a character array
 * @start: pointer to the start of buffer
 * @len: length of the string stored in buffer
 */
typedef struct buffer_s
{
	char *buffer;
	char *start;
	unsigned int len;
} buffer_t;

/**
 * struct converter_s - new type defining a converter struct
 * @specifier: character representing a conversion specifier
 * @func: pointer to a conversion function corresponding to specifier
 */
typedef struct converter_s
{
	unsigned char specifier;
	unsigned int (*func)(va_list, buffer_t *,
			unsigned char, int, int, unsigned char);
} converter_t;

/**
 * struct flag_s - new type defining a flags struct
 * @flag: character representing a flag
 * @value: integer value of the flag
 */
typedef struct flag_s
{
	unsigned char flag;
	unsigned char value;
} flag_t;

int _printf(const char *format, ...);

/* Conversion Specifier Functions */
unsigned int convert_c(va_list args, buffer_t *output,
		unsigned char flags, int w, int pre, unsigned char len);
unsigned int convert_s(va_list args, buffer_t *output,
		unsigned char flags, int w, int pre, unsigned char len);
unsigned int convert_di(va_list args, buffer_t *output,
		unsigned char flags, int w, int pre, unsigned char len);
unsigned int convert_percent(va_list args, buffer_t *output,
		unsigned char flags, int w, int pre, unsigned char len);
unsigned int convert_b(va_list args, buffer_t *output,
		unsigned char flags, int w, int pre, unsigned char len);
unsigned int convert_u(va_list args, buffer_t *output,
		unsigned char flags, int w, int pre, unsigned char len);
unsigned int convert_o(va_list args, buffer_t *output,
		unsigned char flags, int w, int pre, unsigned char len);
unsigned int convert_x(va_list args, buffer_t *output,
		unsigned char flags, int w, int pre, unsigned char len);
unsigned int convert_X(va_list args, buffer_t *output,
		unsigned char flags, int w, int pre, unsigned char len);
unsigned int convert_S(va_list args, buffer_t *output,
		unsigned char flags, int w, int pre, unsigned char len);
unsigned int convert_p(va_list args, buffer_t *output,
		unsigned char flags, int w, int pre, unsigned char len);
unsigned int convert_r(va_list args, buffer_t *output,
		unsigned char flags, int w, int pre, unsigned char len);
unsigned int convert_R(va_list args, buffer_t *output,
		unsigned char flags, int w, int pre, unsigned char len);

/* Handlers */
unsigned char handle_flags(const char *flags, char *i);
unsigned char handle_length(const char *modifier, char *i);
int handle_width(va_list args, const char *modifier, char *i);
int handle_precision(va_list args, const char *modifier, char *i);
unsigned int (*h_s(const char *s))(va_list, buffer_t *,
		unsigned char, int, int, unsigned char);

/* Modifiers */
unsigned int print_width(buffer_t *output, unsigned int printed,
		unsigned char flags, int w);
unsigned int print_string_width(buffer_t *output,
		unsigned char flags, int w, int pre, int size);
unsigned int print_neg_width(buffer_t *output, unsigned int printed,
		unsigned char flags, int w);

/* Helper Functions */
buffer_t *init_buffer(void);
void free_buffer(buffer_t *output);
unsigned int _memcpy(buffer_t *output, const char *src, unsigned int n);
unsigned int convert_sbase(buffer_t *output, long int num, char *base,
		unsigned char flags, int w, int pre);
unsigned int convert_ubase(buffer_t *output, unsigned long int num, char *base,
		unsigned char flags, int w, int pre);
>>>>>>> b85c1904f70491640441548355032c5d04714f81

#endif /* MAIN_H */
