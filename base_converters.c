#include "custom_formatter.h"

unsigned int convert_signed_base(buffer_t *buffer, long num, const char *base, unsigned char flags, int width, int precision);
unsigned int convert_unsigned_base(buffer_t *buffer, unsigned long num, const char *base, unsigned char flags, int width, int precision);

/**
 * convert_signed_base - Converts a signed number to a specified base and stores
 *                       the result in a buffer.
 * @buffer: The buffer structure to store result.
 * @num: The number to convert.
 * @base: The base for conversion.
 * @flags: Modifier flags.
 * @width: Width modifier.
 * @precision: Precision modifier.
 *
 * Return: Number of characters added to the buffer.
 */
unsigned int convert_signed_base(buffer_t *buffer, long num, const char *base,
                                  unsigned char flags, int width, int precision)
{
    int base_len = 0;
    char digit;
    unsigned int count = 0;
    long value = num;

    // Calculate base length
    while (base[base_len] != '\0') base_len++;

    // Recursive conversion for numbers larger than the base
    if (value >= base_len || value <= -base_len) {
        count += convert_signed_base(buffer, value / base_len, base, flags, width - 1, precision - 1);
    } else {
        // Handle precision and width for positive values
        while (precision > 1 || (width > 1 && !(flags & NEG_FLAG))) {
            _memcpy(buffer, "0", 1);
            count++;
            precision--;
            width--;
        }
    }

    // Convert single digit and add to buffer
    digit = base[(value < 0 ? -value : value) % base_len];
    _memcpy(buffer, &digit, 1);
    count++;

    // Handle negative width (left justify)
    while (count < (unsigned)width) {
        _memcpy(buffer, " ", 1);
        count++;
    }

    return count;
}

/**
 * convert_unsigned_base - Converts an unsigned number to a specified base and
 *                         stores the result in a buffer.
 * @buffer: The buffer structure to store result.
 * @num: The number to convert.
 * @base: The base for conversion.
 * @flags: Modifier flags.
 * @width: Width modifier.
 * @precision: Precision modifier.
 *
 * Return: Number of characters added to the buffer.
 */
unsigned int convert_unsigned_base(buffer_t *buffer, unsigned long num, const char *base,
                                   unsigned char flags, int width, int precision)
{
    unsigned int base_len = 0, count = 0;
    char digit;
    unsigned long value = num;

    // Calculate base length
    while (base[base_len] != '\0') base_len++;

    // Recursive conversion for numbers larger than the base
    if (value >= base_len) {
        count += convert_unsigned_base(buffer, value / base_len, base, flags, width - 1, precision - 1);
    } else {
        // Handle precision and width for positive values
        while (precision > 1 || (width > 1 && !(flags & NEG_FLAG))) {
            _memcpy(buffer, "0", 1);
            count++;
            precision--;
            width--;
        }
    }

    // Convert single digit and add to buffer
    digit = base[value % base_len];
    _memcpy(buffer, &digit, 1);
    count++;

    // Handle negative width (left justify)
    while (count < (unsigned)width) {
        _memcpy(buffer, " ", 1);
        count++;
    }

    return count;
}

