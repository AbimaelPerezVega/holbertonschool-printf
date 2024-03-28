#include "main.h"

unsigned int convert_s(va_list args, buffer_t *output,
		unsigned char flags, int w, int pre, unsigned char len);
unsigned int convert_S(va_list args, buffer_t *output,
		unsigned char flags, int w, int pre, unsigned char len);
unsigned int convert_r(va_list args, buffer_t *output,
		unsigned char flags, int w, int pre, unsigned char len);
unsigned int convert_R(va_list args, buffer_t *output,
		unsigned char flags, int w, int pre, unsigned char len);

/**
 * convert_s - converts an argument to a string and
 *             stores it to a buffer contained in a struct
 * @args: va_list pointing to the argument to be converted
 * @flags: flag modifiers
 * @w: width modifier
 * @pre: precision modifier
 * @len: length modifier
 * @output: buffer_t struct containing a character array
 *
 * Return: number of bytes stored to the buffer
 */
unsigned int convert_s(va_list args, buffer_t *output,
                       unsigned char flags, int w, int pre, unsigned char len)
{
    char *str = va_arg(args, char *);
    char *null = "(null)";
    int size = 0;
    unsigned int ret = 0;

    (void)flags;
    (void)len;

    if (str == NULL)
        return (_memcpy(output, null, 6));

    while (str[size])
        size++;

    ret += print_string_width(output, flags, w, pre == -1 ? size : pre, size);

    while (*str && pre-- > 0)
    {
        ret += _memcpy(output, str++, 1);
    }

    ret += print_neg_width(output, ret, flags, w);

    return ret;
}
/**
 * convert_S - converts an argument to a string and
 *             stores it to a buffer contained in a struct.
 * @args: va_list pointing to the argument to be converted.
 * @flags: flag modifiers.
 * @w: A width modifier.
 * @pre: precision modifier.
 * @len: length modifier.
 * @output: buffer_t struct containing a character array.
 *
 * Return: number of bytes stored to the buffer.
 *
 * Description: Non-printable characteres (ASCII values < 32 or >= 127)
 *              are stored as \x followed by the ASCII code value in hex.
 */
unsigned int convert_S(va_list args, buffer_t *output,
                       unsigned char flags, int w, int pre, unsigned char len)
{
    char *str = va_arg(args, char *);
    char *null = "(null)", *hex = "\\x", zero = '0';
    int size = 0, i;
    unsigned int ret = 0;

    (void)len;

    if (str == NULL)
        return (_memcpy(output, null, 6));

    while (str[size])
        size++;

    ret += print_string_width(output, flags, w, pre == -1 ? size : pre, size);

    for (i = 0; str[i] && i < pre; i++)
    {
        if (str[i] < 32 || str[i] >= 127)
        {
            ret += _memcpy(output, hex, 2);
            if (str[i] < 16)
                ret += _memcpy(output, &zero, 1);
            ret += convert_ubase(output, str[i], "0123456789ABCDEF", flags, 0, 0);
            continue;
        }
        ret += _memcpy(output, (str + i), 1);
    }

    ret += print_neg_width(output, ret, flags, w);

    return ret;
}
/**
 * convert_r - reverses a string and stores it
 *             to a buffer contained in a struct.
 * @args: va_list pointing to the string to be reversed.
 * @flags: Flag modifiers.
 * @w: width modifier.
 * @pre: precision modifier.
 * @len: length modifier.
 * @output: buffer_t struct containing a character array.
 *
 * Return: number of bytes stored to the buffer.
 */
unsigned int convert_r(va_list args, buffer_t *output,
                       unsigned char flags, int w, int pre, unsigned char len)
{
    char *str = va_arg(args, char *);
    char *null = "(null)";
    int size = 0, end, i;
    unsigned int ret = 0;

    (void)flags;
    (void)len;

    if (str == NULL)
        return (_memcpy(output, null, 6));

    while (*(str + size))
        size++;

    ret += print_string_width(output, flags, w, pre == -1 ? size : pre, size);

    end = size - 1;
    for (i = 0; end >= 0 && i < pre; i++, end--)
    {
        ret += _memcpy(output, (str + end), 1);
    }

    ret += print_neg_width(output, ret, flags, w);

    return ret;
}
/**
 * convert_R - converts a string to ROT13 and stores
 *             it to a buffer contained in a struct.
 * @args: va_list pointing to the string to be converted.
 * @flags: flag modifiers.
 * @w: width modifier.
 * @pre: precision modifier.
 * @len: lenth modifier.
 * @output: buffer_t struct containing a character array.
 *
 * Return: number of bytes stored to the buffer
 */
unsigned int convert_R(va_list args, buffer_t *output,
                       unsigned char flags, int w, int pre, unsigned char len)
{
    char *alpha = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ";
    char *rot13 = "nopqrstuvwxyzabcdefghijklmNOPQRSTUVWXYZABCDEFGHIJKLM";
    char *str = va_arg(args, char *);
    char *null = "(null)";
    int i, j, size = 0;
    unsigned int ret = 0;

    (void)flags;
    (void)len;

    if (str == NULL)
        return (_memcpy(output, null, 6));

    while (*(str + size))
        size++;

    ret += print_string_width(output, flags, w, pre == -1 ? size : pre, size);

    for (i = 0; *(str + i) != '\0' && i < pre; i++)
    {
        for (j = 0; j < 52; j++)
        {
            if (*(str + i) == *(alpha + j))
            {
                ret += _memcpy(output, (rot13 + j), 1);
                break;
            }
        }
        if (j == 52)
            ret += _memcpy(output, (str + i), 1);
    }

    ret += print_neg_width(output, ret, flags, w);

    return ret;
}

