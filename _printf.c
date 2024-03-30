#include "main.h"
#include <stdarg.h>
#include <unistd.h>
#include <stdio.h>

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
                if (s == NULL) {
                    s = "(null)";
                }
                while (*s)
                {
                    count += write(1, s++, 1);
                }
            }
            else
            {
                count += write(1, "%", 1);
                count += write(1, format, 1);
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

