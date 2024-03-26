#include "custom_formatter.h"

// Implementación de la función para copiar memoria en el buffer personalizado
unsigned int copy_to_buffer(buffer_t *buffer, const char *source, unsigned int count) {
    unsigned int i;

    for (i = 0; i < count; i++) {
        *(buffer->current) = *(source + i);
        buffer->length++;

        // Flush the buffer if it's full
        if (buffer->length == BUFFER_SIZE) {
            write(1, buffer->start, buffer->length);
            buffer->current = buffer->start;
            buffer->length = 0;
        } else {
            (buffer->current)++;
        }
    }

    return count;
}

// Libera la memoria asignada para el buffer
void release_buffer(buffer_t *buffer) {
    if (buffer != NULL) {
        free(buffer->start); // Asegura liberar primero la memoria del contenido
        free(buffer); // Luego libera el struct en sí
    }
}

// Inicializa y retorna una nueva estructura de buffer
buffer_t *create_buffer(void) {
    buffer_t *newBuffer = malloc(sizeof(buffer_t));
    if (newBuffer == NULL) {
        return NULL;
    }

    newBuffer->current = malloc(BUFFER_SIZE);
    if (newBuffer->current == NULL) {
        free(newBuffer);
        return NULL;
    }

    newBuffer->start = newBuffer->current;
    newBuffer->length = 0;

    return newBuffer;
}
