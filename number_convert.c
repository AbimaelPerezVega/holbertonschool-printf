#include "main.h"

unsigned int convert_di(va_list args, buffer_t *output,
		unsigned char flags, int w, int pre, unsigned char len);
unsigned int convert_b(va_list args, buffer_t *output,
		unsigned char flags, int w, int pre, unsigned char len);
unsigned int convert_u(va_list args, buffer_t *output,
		unsigned char flags, int w, int pre, unsigned char len);
unsigned int convert_o(va_list args, buffer_t *output,
		unsigned char flags, int w, int pre, unsigned char len);
/**
 * convert_di - converts an argument to a signed int and
 *              stores it to a buffer contained in a struct.
 * @args: va_list pointing to the argument to be converted.
 * @flags: flag modifiers.
 * @w: width modifier.
 * @pre: precision modifier.
 * @len: length modifier.
 * @output: buffer_t struct containing a character array.
 *
 * Return: number of bytes stored to the buffer.
 */
unsigned int convert_di(va_list args, buffer_t *output,
		unsigned char flags, int w, int pre, unsigned char len)
{
	long int d = (len == LONG) ? va_arg(args, long int) : va_arg(args, int);
	char pad, space = ' ', neg = '-', plus = '+';
	unsigned int ret = 0, count = 0;
	long int copy;
	/* Handle space flag */
	if (SPACE_FLAG == 1 && d >= 0)
		ret += _memcpy(output, &space, 1);
	/* Calculate width */
	if (pre <= 0 && NEG_FLAG == 0)
	{
		count = (d == LONG_MIN) ? 19 : (d == 0) ? 1 : 0;

		for (copy = (d < 0) ? -d : d; copy > 0; copy /= 10)
			count++;
		count += (d < 0 || PLUS_FLAG == 1) ? 1 : 0;
		count += (SPACE_FLAG == 1 && d >= 0) ? 1 : 0;
		/* Handle plus flag when zero flag is active */
		if (ZERO_FLAG == 1 && (PLUS_FLAG == 1 && d >= 0))
			ret += _memcpy(output, &plus, 1);
		/* Print negative sign when zero flag is active */
		if (ZERO_FLAG == 1 && d < 0)
			ret += _memcpy(output, &neg, 1);
		pad = (ZERO_FLAG == 1) ? '0' : ' ';

		for (w -= count; w > 0; w--)
			ret += _memcpy(output, &pad, 1);
	}
	/* Print negative sign when zero flag is not active */
	if (ZERO_FLAG == 0 && d < 0)
		ret += _memcpy(output, &neg, 1);
	/* Handle plus flag when zero flag is not active */
	if (ZERO_FLAG == 0 && (PLUS_FLAG == 1 && d >= 0))
		ret += _memcpy(output, &plus, 1);

	if (!(d == 0 && pre == 0))
	ret += convert_sbase(output, d, "0123456789", flags, 0, pre);

	ret += print_neg_width(output, ret, flags, w);

	return (ret);
}
/**
 * convert_b - converts an unsigned int argument to binary
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
unsigned int convert_b(va_list args, buffer_t *output,
		unsigned char flags, int w, int pre, unsigned char len)
{
	unsigned int num = va_arg(args, unsigned int);
	(void)len;

	return (convert_ubase(output, num, "01", flags, w, pre));
}
/**
 * convert_o - converts an unsigned int to octal and
 *             stores it to a buffer contained in a struct.
 * @args: va_list poinitng to the argument to be converted.
 * @flags: flag modifiers.
 * @w: width modifier.
 * @pre: precision modifier.
 * @len: length modifier.
 * @output: buffer_t struct containing a character array.
 *
 * Return: number of bytes stored to the buffer.
 */
unsigned int convert_o(va_list args, buffer_t *output,
		unsigned char flags, int w, int pre, unsigned char len)
{
	unsigned long int num;
	unsigned int ret = 0;
	char zero = '0';

	if (len == SHORT)
		num = (unsigned short)va_arg(args, unsigned int);
	else if (len == LONG)
		num = va_arg(args, unsigned long int);
	else
		num = va_arg(args, unsigned int);
	if (HASH_FLAG == 1 && num != 0)
		ret += _memcpy(output, &zero, 1);
	if (!(num == 0 && pre == 0))
		ret += convert_ubase(output, num, "01234567", flags, w, pre);

	ret += print_neg_width(output, ret, flags, w);

	return (ret);
}
/**
 * convert_u - converts an unsigned int argument to decimal and
 *               stores it to a buffer contained in a struct.
 * @args: va_list pointing to the argument to be converted.
 * @flags: Flag modifiers.
 * @w: width modifier.
 * @pre: precision modifier.
 * @len: length modifier.
 * @output: buffer_t struct containing a character array.
 *
 * Return: number of bytes stored to the buffer.
 */
unsigned int convert_u(va_list args, buffer_t *output,
		unsigned char flags, int w, int pre, unsigned char len)
{
	unsigned long int num;
	unsigned int ret = 0;

	if (len == SHORT)
		num = (unsigned short)va_arg(args, unsigned int);
	else if (len == LONG)
		num = va_arg(args, unsigned long int);
	else
		num = va_arg(args, unsigned int);
	if (!(num == 0 && pre == 0))
		ret += convert_ubase(output, num, "0123456789", flags, w, pre);

	ret += print_neg_width(output, ret, flags, w);

	return (ret);
}
