#include "main.h"

int handle_write_char(char c, char buffer[], int flags, int width, int precision, int size);

/***PRINT CHAR***/

/**
 *print_char - prints the char
 *@types: list of arguments
 *@buffer: buffer array
 *@flags: calculates the active flags
 *@width: width of the array
 *@precision: precision specification
 *@size:size specifier
 *Return: number of chars being printed
*/
int print_char(va_list types, char buffer[],
		int flags, int width, int precision, int size)
{
	char c = va_arg(types, int);

	return (handle_write_char(c, buffer, flags, width, precision, size));
}

/***PRINT A STRING***/
/**
 *print_string - prints a stirng
 *@types: list arguments
 *@buffer: buffer array to handle print
 *@flags: calculates the active flags
 *@width: width
 *@precision: precision specification
 *@size: size specifier
 *Return: number of chars printed
*/
int print_string(va_list types, char buffer[],
		int flags, int width, int precision, int size)
{
	int length = 0, i;
	char *str = va_arg(types, char *);

	UNUSED(buffer);
	UNUSED(flags);
	UNUSED(width);
	UNUSED(precision);
	UNUSED(size);

if (str == NULL)
{
	str = "(null)";
	if (precision >= 6)
		str = "   ";
}

while (str[length] != '\0')
length++;

if (precision >= 0 && precision < length)
	length = precision;

if (width > length)
{
if (!(flags & F_MINUS))
{
for (i = width - length; i > 0; i--)
	buffer[i] = ' ';
return (handle_print("%s", 0, types, buffer, flags, width, precision, size));
}
}
return (handle_print("%s", 0, types, buffer, flags, width, precision, size));
}

/***PRINT PERCENT SIGN***/
/**
 *print_percent - prints a percent sign
 *@types: lists of arguments
 *@buffer: buffer array to handle print
 *@flags: calculates
 *@width: width
 *@precision: precision specification
 *@size: size specifier
 *Return: number of chars printed
*/
int print_percent(va_list types, char buffer[],
		int flags, int width, int precision, int size)
{
UNUSED(types);
UNUSED(buffer);
UNUSED(flags);
UNUSED(width);
UNUSED(precision);
UNUSED(size);
return (handle_print("%%", 0, types, buffer, flags, width, precision, size));
}

/***PRINT INT***/
/**
 *print_int - print int
 *@types: lists of arguments
 *@buffer: buffer arrays
 *@flags: calculates active flags
 *@width: width
 *@precision: precision specification
 *@size: size specifier
 *Return: number of chars printed
*/
int print_int(va_list types, char buffer[],
	int flags, int width, int precision, int size)
{
	UNUSED(flags);
	UNUSED(width);
	UNUSED(precision);
	UNUSED(size);

return (handle_print("%ld", 0, types, buffer, flags, width, precision, size));
}

/***PRINT BINARY***/
/**
 *print_binary - prints an unsigned number
 *@types: lists of arguments
 *@buffer: buffer the array to handle print
 *@flags: calculates active flags
 *@width: width
 *@precision: precision specification
 *@size: size specifier
 *Return: numbers of char
*/
int print_binary(va_list types, char buffer[],
		int flags, int width, int precision, int size)
{
	UNUSED(flags);
	UNUSED(width);
	UNUSED(precision);
	UNUSED(size);

return (handle_print("%u", 0, types, buffer, flags, width, precision, size));
}
