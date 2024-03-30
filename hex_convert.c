#include "main.h"

unsigned int convert_x(va_list args, buffer_t *output,
		unsigned char flags, int w, int pre, unsigned char len);
unsigned int convert_X(va_list args, buffer_t *output,
		unsigned char flags, int w, int pre, unsigned char len);

/**
 * convert_x - converts an unsigned int argument to hex using abcdef
 *             and stores it to a buffer contained in a struct.
 * @args: va_list pointing to the argument to be converted.
 * @flags: flag modifiers.
 * @w: width modifier.
 * @pre: precision modifier.
 * @len: length modifier.
 * @output: buffer_t struct containing a character array.
 *
 * Return: number of bytes stored to the buffer.
 */
unsigned int convert_x(va_list args, buffer_t *output,
		unsigned char flags, int w, int pre, unsigned char len)
{
	unsigned long int num = (len == LONG) ? va_arg(args, unsigned long int) :
		(len == SHORT) ? (unsigned short)va_arg(args, unsigned int) :
		va_arg(args, unsigned int);
	unsigned int ret = 0;

	if (!(num == 0 && pre == 0))

	ret += convert_ubase(output, num, "0123456789abcdef", flags, w, pre);

	ret += print_neg_width(output, ret, flags, w);

	if (HASH_FLAG == 1 && num != 0)

	ret += _memcpy(output, "0x", 2);

	return (ret);
}
/**
 * convert_X - converts an unsigned int argument to hex using ABCDEF
 *             and stores it to a buffer contained in a struct.
 * @args: va_list pointing to the argument to be converted.
 * @flags: Flag modifiers.
 * @w: width modifier.
 * @pre: precision modifier.
 * @len: length modifier.
 * @output: buffer_t struct containing a character array.
 *
 * Return: number of bytes stored to the buffer.
 */
unsigned int convert_X(va_list args, buffer_t *output,
		unsigned char flags, int w, int pre, unsigned char len)
{
	unsigned long int num = (len == LONG) ? va_arg(args, unsigned long) :
		(len == SHORT) ? (unsigned short)va_arg(args, unsigned int) :
		va_arg(args, unsigned int);
	char *lead = "0X";
	unsigned int ret = 0;

	if (HASH_FLAG == 1 && num != 0)

	ret += _memcpy(output, lead, 2);

	if (!(num == 0 && pre == 0))

		ret += convert_ubase(output, num, "0123456789ABCDEF", flags, w, pre);

	ret += print_neg_width(output, ret, flags, w);

	return (ret);
}
