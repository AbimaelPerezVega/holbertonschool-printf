#include "main.h"
<<<<<<< HEAD
#include <stdarg.h>
#include <unistd.h>
#include <stdio.h> // for NULL definition

int _printf(const char *format, ...)
{
    va_list args;
    int count = 0;

    va_start(args, format);

    while (*format)
    {
        if (*format == '%')
        {
            format++;
            if (*format == '\0') {
                count += write(1, "%", 1);
                break;
            }
            else if (*format == 'c')
            {
                char c = (char)va_arg(args, int);
                count += write(1, &c, 1);
            }
            else if (*format == 's')
            {
                char *s = va_arg(args, char *);
                if (s == NULL) {
                    s = "(NULL)";
                }
                while (*s)
                {
                    count += write(1, s++, 1);
                }
            }
            else
            {
                // Print the unknown specifier along with the '%'
                count += write(1, "%", 1);
                count += write(1, format - 1, 1);
            }
        }
        else
        {
            count += write(1, format, 1);
        }
        format++;
    }

    va_end(args);

    return count;
=======

void cleanup(va_list args, buffer_t *output);
int run_printf(const char *format, va_list args, buffer_t *output);
int _printf(const char *format, ...);

/**
 * cleanup - Peforms cleanup operations for _printf.
 * @args: A va_list of arguments provided to _printf.
 * @output: A buffer_t struct.
 */
void cleanup(va_list args, buffer_t *output)
{
	va_end(args);
	write(1, output->start, output->len);
	free_buffer(output);
}

/**
 * run_printf - Reads through the format stringig
 * _printf - custom printf function
 *
 * @format: Character string to print - may contain directives.
 * @output: A buffer_t struct containing a buffer.
 * @args: A va_list of arguments.
 *
 * Return: The number of characters stored to output.
 */
int run_printf(const char *format, va_list args, buffer_t *output)
{
	int i, w, pre, ret = 0;
	char tmp;
	unsigned char flags, len;
unsigned int (*f)(va_list, buffer_t *, unsigned char, int, int, unsigned char);

	for (i = 0; *(format + i); i++)
	{
		len = 0;
		if (*(format + i) == '%')
		{
			tmp = 0;
			flags = handle_flags(format + i + 1, &tmp);
			w = handle_width(args, format + i + tmp + 1, &tmp);
			pre = handle_precision(args, format + i + tmp + 1,
					&tmp);
			len = handle_length(format + i + tmp + 1, &tmp);

			f = handle_specifiers(format + i + tmp + 1);
			if (f != NULL)
			{
				i += tmp + 1;
				ret += f(args, output, flags, w, pre, len);
				continue;
			}
			else if (*(format + i + tmp + 1) == '\0')
			{
				ret = -1;
				break;
			}
		}
		ret += _memcpy(output, (format + i), 1);
		i += (len != 0) ? 1 : 0;
	}
	cleanup(args, output);
	return (ret);
}

/**
 * _printf - Outputs a formatted string
 *
 * @format: Character string to print - may contain directives.
 *
 * Return: The number of characters printed.
 */
int _printf(const char *format, ...)
{
	buffer_t *output;
	va_list args;
	int ret;

	if (format == NULL)
		return (-1);
	output = init_buffer();
	if (output == NULL)
		return (-1);

	va_start(args, format);

	ret = run_printf(format, args, output);

	return (ret);
>>>>>>> b85c1904f70491640441548355032c5d04714f81
}
