#ifndef PRINTF_CUSTOM_H
#define PRINTF_CUSTOM_H

#include <stdio.h>
#include <stdarg.h>
/**
 * _print - function for printf
 *@format: the thing
 */
void _print(const char *format, ...)
{
	va_list args;
va_start(args, format);
		while (*format != '\0')
	{
		if (*format == '%')
		{
			format++;
			if (*format == 'd')
			{
				int num = va_arg(args, int);
printf("%d", num);
			}
			else if (*format == 's')
			{
				char *str = va_arg(args, char *);
printf("%s", str);
			}
		}
		else
		{
			putchar(*format);
		}
		format++;
	}
	va_end(args);
}

#endif /*PRINTF_CUSTOM_H */
