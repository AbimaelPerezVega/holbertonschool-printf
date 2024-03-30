#include "main.h"
#include <stdarg.h>
#include <unistd.h>

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
            if (*format == 'c')
            {
                char c = (char)va_arg(args, int);
                count += write(1, &c, 1);
            }
            else if (*format == 's')
            {
                char *s = va_arg(args, char *);
                while (*s)
                {
                    count += write(1, s++, 1);
                }
            }
            else if (*format == '%')
            {
                count += write(1, "%", 1);
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
}
