#include "custom_formatter.h"

// Definiciones para manejar los flags, manteniendo la estructura para
// facilidad de modificación y expansión.
typedef struct {
    char flag_char;
    unsigned char flag_value;
} FlagDefinition;

FlagDefinition availableFlags[] = {
    {'+', FLAG_PLUS},
    {'-', FLAG_MINUS},
    {'#', FLAG_HASH},
    {'0', FLAG_ZERO},
    {' ', FLAG_SPACE},
    {0, 0} // Terminal nulo para marcar el fin del array
};

// Prototipos simplificados para mejorar la claridad
unsigned char fetch_flags(const char *flagSequence, char *advance);
unsigned char fetch_length_modifier(const char *modifier, char *advance);
int fetch_width(va_list args, const char *input, char *advance);
int fetch_precision(va_list args, const char *input, char *advance);
unsigned int (*get_conversion_function(const char *specifier))(va_list args, buffer_t *buffer, unsigned char flags, int width, int precision, unsigned char length);

// Implementaciones
unsigned char fetch_flags(const char *flagSequence, char *advance) {
    unsigned char flagAccumulator = 0;
    int i, j;
    for (i = 0; flagSequence[i]; ++i) {
        for (j = 0; availableFlags[j].flag_char; ++j) {
            if (flagSequence[i] == availableFlags[j].flag_char) {
                (*advance)++;
                flagAccumulator |= availableFlags[j].flag_value;
                break;
            }
        }
        // Si no se encuentra el flag, se rompe el bucle
        if (!availableFlags[j].flag_char) break;
    }
    return flagAccumulator;
}

unsigned char fetch_length_modifier(const char *modifier, char *advance) {
    if (*modifier == 'h' || *modifier == 'l') {
        (*advance)++;
        return (*modifier == 'h') ? LENGTH_SHORT : LENGTH_LONG;
    }
    return LENGTH_NONE;
}

int fetch_width(va_list args, const char *input, char *advance) {
    int width = 0;
    if (*input == '*') {
        (*advance)++;
        return va_arg(args, int);
    }
    while (*input >= '0' && *input <= '9') {
        width = 10 * width + (*input - '0');
        input++;
        (*advance)++;
    }
    return width;
}

int fetch_precision(va_list args, const char *input, char *advance) {
    int precision = 0;
    if (*input != '.') return PRECISION_NOT_SPECIFIED;
    
    input++; // Salta el punto
    (*advance)++;
    
    if (*input == '*') {
        (*advance)++;
        return va_arg(args, int);
    }

    while (*input >= '0' && *input <= '9') {
        precision = 10 * precision + (*input - '0');
        input++;
        (*advance)++;
    }
    return (precision > 0) ? precision : PRECISION_ZERO;
}

unsigned int (*get_conversion_function(const char *specifier))(va_list args, buffer_t *buffer, unsigned char flags, int width, int precision, unsigned char length) {
    // Mapeo de especificadores a funciones
    static const FunctionMap functionMappings[] = {
        {'c', convert_char},
        {'s', convert_string},
        // Añade aquí más mapeos según sea necesario
        {0, NULL} // Fin del mapeo
    };

    for (int i = 0; functionMappings[i].func != NULL; ++i) {
        if (functionMappings[i].specifier == *specifier) {
            return functionMappings[i].func;
        }
    }
    return NULL; // Si no se encuentra el especificador
}

