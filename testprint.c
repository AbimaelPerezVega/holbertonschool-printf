int _printf(const char *format, ...)
{
    if (format == NULL)
        return -1; // Return error code for NULL format string

    va_list args;
    va_start(args, format);

    int count = 0; // Counter for characters printed

    while (*format != '\0')
    {
        if (*format == '%')
        {
            format++;
            switch (*format)
            {
                case 'd':
                    {
                        int num = va_arg(args, int);
                        count += printf("%d", num);
                        break;
                    }
                case 's':
                    {
                        char *str = va_arg(args, char *);
                        if (str == NULL)
                            str = "(null)"; // Handle NULL strings
                        count += printf("%s", str);
                        break;
                    }
                case '%':
                    count += putchar('%');
                    break;
                default:
                    count += putchar('%') + putchar(*format);
                    break;
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
