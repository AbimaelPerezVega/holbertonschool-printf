#include <stdarg.h>
#include <unistd.h> // for write
#include <stdlib.h> // for malloc, free
#include <string.h> // for strlen

int _printf(const char *format, ...)
{
	va_list args;
	int printed_chars = 0;	
	va_start(args, format);
	
	while (*format)
	{
	if (*format == '%')
	{
	format++;
	switch (*format)
	{
	case 'c':
	{
	char c = (char) va_arg(args, int);
	printed_chars += write(1, &c, 1);
	break;
	}
	case 's':
	{
	char *str = va_arg(args, char *);
	size_t len = strlen(str);
	printed_chars += write(1, str, len);
	break;
	}
	case '%':
	printed_chars += write(1, "%", 1);
	break;
	default:
	printed_chars += write(1, "%", 1);
	printed_chars += write(1, format, 1);
	}
	}
	else
	{
	printed_chars += write(1, format, 1);
	}
	format++;
	}
	va_end(args);
	return printed_chars;
}
