#include "main.h"

unsigned int convert_c(va_list args, buffer_t *output,
		unsigned char flags, int w, int pre, unsigned char len);
unsigned int convert_percent(va_list args, buffer_t *output,
		unsigned char flags, int w, int pre, unsigned char len);
unsigned int convert_p(va_list args, buffer_t *output,
		unsigned char flags, int w, int pre, unsigned char len);

/**
 * convert_c - converts an argument to an unsigned char and
 *             stores it to a buffer contained in a struct.
 * @args: va_list pointing to the argument to be converted.
 * @flags: flag modifiers.
 * @w: width modifier.
 * @pre: precision modifier.
 * @len: length modifier.
 * @output: buffer_t struct containing a character array.
 *
 * Return: number of bytes stored to the buffer.
 */
unsigned int convert_c(va_list args, buffer_t *output,
                       unsigned char flags, int w, int pre, unsigned char len)
{
    char c = va_arg(args, int);
    unsigned int ret = 0;

    (void)pre;
    (void)len;

    ret += print_width(output, ret, flags, w);
    ret += _memcpy(output, &c, 1);
    ret += print_neg_width(output, ret, flags, w);

    return (ret);
}
/**
 * convert_percent - stores a percent sign to a
 *                   buffer contained in a struct.
 * @args: va_list pointing to the argument to be converted.
 * @flags: flag modifiers.
 * @w: width modifier.
 * @pre: precision modifier.
 * @len: length modifier.
 * @output: buffer_t struct containing a character array.
 *
 * Return: number of bytes stored to the buffer (always 1).
 */
unsigned int convert_percent(va_list args, buffer_t *output,
                             unsigned char flags, int w, int pre, unsigned char len)
{
    char percent = '%';
    unsigned int ret = 0;
    
    (void)args;
    (void)pre;
    (void)len;
    
    ret += print_width(output, ret, flags, w);
    ret += _memcpy(output, &percent, 1);
    ret += print_neg_width(output, ret, flags, w);

    return (ret);
}
/**
 * convert_p - converts the address of an argument to hex and
 *             stores it to a buffer contained in a struct.
 * @args: va_list pointing to the argument to be converted.
 * @flags: flag modifiers.
 * @w: width modifier.
 * @pre: A precision modifier.
 * @len: length modifier.
 * @output: buffer_t struct containing a character array.
 *
 * Return: number of bytes stored to the buffer.
 */
unsigned int convert_p(va_list args, buffer_t *output,
                       unsigned char flags, int w, int pre, unsigned char len)
{
    char *null = "(nil)";
    unsigned long int address = va_arg(args, unsigned long int);
    unsigned int ret = 0;

    (void)len;

    if (address == '\0')
        return _memcpy(output, null, 5);

    flags |= 32;
    ret += convert_ubase(output, address, "0123456789abcdef", flags, w, pre);
    ret += print_neg_width(output, ret, flags, w);

    return (ret);
}
