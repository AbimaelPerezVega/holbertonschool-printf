#include "main.h"
#include <stdarg.h>
#include <unistd.h>

int _printf(const char *format, ...)
{
    va_list args;
    int count = 0;
    char buffer[2] = {'\0', '\0'};

    va_start(args, format);

    while (*format)
    {
        if (*format == '%')
        {
            format++;
            if (*format == 'c')
            {
                buffer[0] = va_arg(args, int);
                write(1, buffer, 1);
                count++;
            }
            else if (*format == 's')
            {
                char *s = va_arg(args, char *);
                while (*s)
                {
                    buffer[0] = *s++;
                    write(1, buffer, 1);
                    count++;
                }
            }
            else if (*format == '%')
            {
                write(1, "%", 1);
                count++;
            }
        }
        else
        {
            buffer[0] = *format;
            write(1, buffer, 1);
            count++;
        }
        format++;
    }

    va_end(args);

    return count;
}

