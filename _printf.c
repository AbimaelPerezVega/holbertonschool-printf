#include "custom_formatter.h"

void finalize(va_list args, buffer_t *buffer);
int execute_printf(const char *format, va_list args, buffer_t *buffer);
int custom_printf(const char *format, ...);

/**
 * finalize - Performs cleanup operations for custom_printf.
 * @args: A va_list of arguments provided to custom_printf.
 * @buffer: A buffer_t struct.
 */
void finalize(va_list args, buffer_t *buffer)
{
    va_end(args);
    write(1, buffer->start, buffer->len);
    free_buffer(buffer);
}

/**
 * execute_printf - Processes the format string for custom_printf.
 * @format: Character string to print, may contain directives.
 * @buffer: A buffer_t struct containing a buffer.
 * @args: A va_list of arguments.
 *
 * Return: The number of characters stored in the output.
 */
int execute_printf(const char *format, va_list args, buffer_t *buffer)
{
    int i, width, precision, result = 0;
    char tmp;
    unsigned char flags, length;
    unsigned int (*func)(va_list, buffer_t *, unsigned char, int, int, unsigned char);

    for (i = 0; format[i]; i++)
    {
        length = 0;
        if (format[i] == '%')
        {
            tmp = 0;
            flags = fetch_flags(format + i + 1, &tmp);
            width = fetch_width(args, format + i + tmp + 1, &tmp);
            precision = fetch_precision(args, format + i + tmp + 1, &tmp);
            length = fetch_length(format + i + tmp + 1, &tmp);

            func = fetch_specifiers(format + i + tmp + 1);
            if (func != NULL)
            {
                i += tmp + 1;
                result += func(args, buffer, flags, width, precision, length);
                continue;
            }
            else if (format[i + tmp + 1] == '\0')
            {
                result = -1;
                break;
            }
        }
        result += _memcpy(buffer, (format + i), 1);
        i += (length != 0) ? 1 : 0;
    }
    finalize(args, buffer);
    return (result);
}

/**
 * custom_printf - Outputs a formatted string, akin to the standard printf.
 * @format: Character string to print, may contain directives.
 *
 * Return: The number of characters printed.
 */
int custom_printf(const char *format, ...)
{
    buffer_t *buffer;
    va_list args;
    int result;

    if (format == NULL)
        return (-1);
    buffer = init_buffer();
    if (buffer == NULL)
        return (-1);

    va_start(args, format);

    result = execute_printf(format, args, buffer);

    return (result);
}

