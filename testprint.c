#include <stdio.h>
#include <stdarg.h>

/**
 * _printf - custom printf function
 * @format: format string
 * Return: number of characters printed
 */
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
            if (*format == 'd')
            {
                int num = va_arg(args, int);
                count += printf("%d", num);
            }
            else if (*format == 's')
            {
                char *str = va_arg(args, char *);
                count += printf("%s", str);
            }
            else
            {
                putchar(*format);
                count++;
            }
        }
        else
        {
            putchar(*format);
            count++;
        }
        format++;
    }

    va_end(args);
    return count;
}

