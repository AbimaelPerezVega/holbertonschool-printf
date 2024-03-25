#include <stdio.h>
#include <stdarg.h>

/**
 * _printf - function for printf
 * @format: the format string
 * Return: number of characters printed
 */
int _printf(const char *format, ...)
{
    if (format == NULL)
        return -1;

    va_list args;
    va_start(args, format);

    int count = 0;

    while (*format != '\0')
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
                if (str == NULL)
                    str = "(null)";
                count += printf("%s", str);
            }
            else if (*format == '%')
            {
                count += putchar('%');
            }
            else
            {
                count += putchar('%') + putchar(*format);
            }
        }
        else
        {
            count += putchar(*format);
        }
        format++;
    }

    va_end(args);
    return count;
}
