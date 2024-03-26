#include "custom_formatter.h"

unsigned int handle_width(buffer_t *buffer, unsigned int current_len, int width);
unsigned int handle_string_width(buffer_t *buffer, int width, int precision, int str_len);
unsigned int handle_trailing_spaces(buffer_t *buffer, unsigned int current_len, int width);

/**
 * handle_width - Adds spaces to buffer for numeric values based on width modifier.
 * @buffer: Pointer to the buffer structure where characters are stored.
 * @current_len: Current length of the formatted string to be printed.
 * @width: The specified width.
 *
 * Return: The number of spaces added to the buffer.
 */
unsigned int handle_width(buffer_t *buffer, unsigned int current_len, int width)
{
    unsigned int added_spaces = 0;
    char space = ' ';

    while (current_len < (unsigned int)width) {
        _memcpy(buffer, &space, 1);
        added_spaces++;
        current_len++;
    }

    return added_spaces;
}

/**
 * handle_string_width - Adds spaces to buffer for string values based on width and precision modifiers.
 * @buffer: Pointer to the buffer structure.
 * @width: The specified width.
 * @precision: The specified precision. -1 if not specified.
 * @str_len: Length of the string.
 *
 * Return: The number of spaces added to the buffer.
 */
unsigned int handle_string_width(buffer_t *buffer, int width, int precision, int str_len)
{
    unsigned int added_spaces = 0;
    char space = ' ';
    int effective_length = (precision != -1 && precision < str_len) ? precision : str_len;

    while (effective_length < width) {
        _memcpy(buffer, &space, 1);
        added_spaces++;
        effective_length++;
    }

    return added_spaces;
}

/**
 * handle_trailing_spaces - Adds trailing spaces to buffer when '-' flag is used.
 * @buffer: Pointer to the buffer structure.
 * @current_len: Current length of the formatted string or number.
 * @width: The specified width.
 *
 * Return: The number of spaces added to the buffer.
 */
unsigned int handle_trailing_spaces(buffer_t *buffer, unsigned int current_len, int width)
{
    unsigned int added_spaces = 0;
    char space = ' ';

    if (current_len < (unsigned int)width) {
        unsigned int spaces_to_add = width - current_len;
        for (unsigned int i = 0; i < spaces_to_add; i++) {
            _memcpy(buffer, &space, 1);
            added_spaces++;
        }
    }

    return added_spaces;
}

