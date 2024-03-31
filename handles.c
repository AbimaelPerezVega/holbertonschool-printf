#include "main.h"

unsigned char handle_flags(const char *flag, char *i);
unsigned char handle_length(const char *modifier, char *i);
int handle_width(va_list args, const char *modifier, char *i);
int handle_precision(va_list args, const char *modifier, char *i);
unsigned int (*handle_specifiers(const char *specifier))(va_list, buffer_t *, unsigned char, int, int, unsigned char);
/**
 * handle_flags - Matches flags with corresponding values.
 * @flag: Pointer to a potential string of flags.
 * @i: Index counter for the original format string.
 *
 * Return: Flag character.
 */
unsigned char handle_flags(const char *flag, char *i)
{
	int x, j;
	unsigned char ret = 0;
	flag_t flags[] = {
		{'+', PLUS},
		{' ', SPACE},
		{'#', HASH},
		{'0', ZERO},
		{'-', NEG},
		{0, 0}
	};

	for (x = 0; flag[x]; x++)
	{
		for (j = 0; flags[j].flag != 0; j++)
		{
			if (flag[x] == flags[j].flag)
			{
				(*i)++;
				if (ret == 0)
					ret = flags[j].value;
				else
					ret |= flags[j].value;
				break;
			}
		}
		if (flags[j].value == 0)
			break;
	}

	return (ret);
}
/**
 * handle_length - Matches length modifiers with their corresponding value.
 * @modifier: Pointer to a potential length modifier.
 * @i: Index counter for the original format string.
 *
 * Return: Length modifier if matched; otherwise, 0.
 */
unsigned char handle_length(const char *modifier, char *i)
{
	if (*modifier == 'h')
	{
		(*i)++;
		return (SHORT);
	}

	else if (*modifier == 'l')
	{
		(*i)++;
		return (LONG);
	}

	return (0);
}

/**
 * handle_width - Matches a width modifier with its corresponding value.
 * @args: Va_list of arguments.
 * @modifier: Pointer to a potential width modifier.
 * @i: Index counter for the original format string.
 *
 * Return: Width modifier if matched; otherwise, 0.
 */
int handle_width(va_list args, const char *modifier, char *i)
{
	int value = 0;

	while ((*modifier >= '0' && *modifier <= '9') || (*modifier == '*'))
	{
		(*i)++;

		if (*modifier == '*')
		{
			value = va_arg(args, int);
			if (value <= 0)
				return (0);
			return (value);
		}

		value *= 10;
		value += (*modifier - '0');
		modifier++;
	}

	return (value);
}
/**
 * handle_precision - Matches a precision modifier with its
 * corresponding value.
 * @args: Va_list of arguments.
 * @modifier: Pointer to a potential precision modifier.
 * @i: Index counter for the original format string.
 *
 * Return: Precision modifier if matched; otherwise, 0.
 *
 */
int handle_precision(va_list args, const char *modifier, char *i)
{
	int value = 0;

	if (*modifier != '.')
		return (-1);

	modifier++;
	(*i)++;

	if ((*modifier <= '0' || *modifier > '9') &&
	     *modifier != '*')
	{
		if (*modifier == '0')
			(*i)++;
		return (0);
	}

	while ((*modifier >= '0' && *modifier <= '9') ||
	       (*modifier == '*'))
	{
		(*i)++;

		if (*modifier == '*')
		{
			value = va_arg(args, int);
			if (value <= 0)
				return (0);
			return (value);
		}

		value *= 10;
		value += (*modifier - '0');
		modifier++;
	}

	return (value);
}
/**
 * handle_specifiers - matches conversion spec. with corresponding conversion
 * @specifier: Pointer to a potential conversion specifier
 *
 * Return: Pointer to the conversion function if matched; otherwise, NULL
 */
unsigned int (*handle_specifiers(const char *specifier))(va_list, buffer_t *, unsigned char, int, int, unsigned char)
{
	int i;
	converter_t converters[] = {
		{'c', convert_c},
		{'s', convert_s},
		{'d', convert_di},
		{'i', convert_di},
		{'%', convert_percent},
		{'b', convert_b},
		{'u', convert_u},
		{'o', convert_o},
		{'x', convert_x},
		{'X', convert_X},
		{'S', convert_S},
		{'p', convert_p},
		{'r', NULL},
		{'R', convert_R},
		{0, NULL}
	};

	for (i = 0; converters[i].func; i++)
	{
		if (converters[i].specifier == *specifier)
			return (converters[i].func);
	}

	return (NULL);
}
