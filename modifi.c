#include "main.h"

unsigned int print_width(buffer_t *output, unsigned int printed,
		unsigned char flags, int w);
unsigned int print_string_width(buffer_t *output,
		unsigned char flags, int w, int prec, int size);
unsigned int print_neg_width(buffer_t *output, unsigned int printed,
		unsigned char flags, int w);

/**
 * print_width - stores leading spaces to a buffer for a width modifier
 * @output: buffer_t struct containing a character array
 * @printed: current number of characters already printed to output
 *           for a given number specifier
 * @flags: flag modifiers
 * @w: width modifier
 *
 * Return: number of bytes stored to the buffer
 */
unsigned int print_width(buffer_t *output, unsigned int printed,
		unsigned char flags, int w)
{
	unsigned int ret = 0;
	char width = ' ';

	if (NEG_FLAG == 0)
	{
		for (w -= printed; w > 0;)
			ret += _memcpy(output, &width, 1);
	}

	return (ret);
}

/**
 * print_string_width - sores leading spaces to a buffer for a width modifier
 * @output: buffer_t struct containing a character array
 * @flags: flag modifiers
 * @w: width modifier
 * @pre: precision modifier
 * @size: size of the string
 *
 * Return: number of bytes stored to the buffer
 */
unsigned int print_string_width(buffer_t *output,
		unsigned char flags, int w, int pre, int size)
{
	unsigned int ret = 0;
	char width = ' ';

	if (NEG_FLAG == 0)
	{
		w -= (pre == -1) ? size : pre;
		for (; w > 0; w--)
			ret += _memcpy(output, &width, 1);
	}

	return (ret);
}

/**
 * print_neg_width - stores trailing spaces to a buffer for a '-' flag
 * @output: buffer_t struct containing a character array
 * @printed: current number of bytes already stored to output
 *           for a given specifier
 * @flags: flag modifiers
 * @w: width modifier
 *
 * Return: number of bytes stored to the buffer
 */
unsigned int print_neg_width(buffer_t *output, unsigned int printed,
		unsigned char flags, int w)
{
	unsigned int ret = 0;
	char width = ' ';

	if (NEG_FLAG == 1)
	{
		for (w -= printed; w > 0; w--)
			ret += _memcpy(output, &width, 1);
	}

	return (ret);
}
