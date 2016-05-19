#include <inttypes.h>
#include <stdlib.h>

#include "fifo.h"

fifo_result_t fifo_init(fifo_t *fifo, uint8_t *buffer, uint16_t size)
{
    /*
     * Maximum value of size is UINT16_MAX - 1. This is due to the fact that
     * we often add 1 to the first/last counters and we do not want them
     * to overflow.
     */
    if (NULL != fifo && NULL != buffer && UINT16_MAX > size && 0 < size) {
        fifo->buffer = buffer;
        fifo->first = 0;
        fifo->last = 0;
        fifo->size = size + 1;

        return FIFO_SUCCESS;
    } else {
        return FIFO_ERROR;
    }
}

fifo_result_t fifo_push(fifo_t *fifo, uint8_t data)
{
    if (FIFO_FALSE == fifo_is_full(fifo)) {
        fifo->buffer[fifo->last] = data;
        fifo->last = (fifo->last + 1) % fifo->size;
        return FIFO_SUCCESS;
    } else {
        return FIFO_ERROR;
    }
}

fifo_result_t fifo_push_multiple(fifo_t *fifo, uint8_t *data, uint16_t size)
{
    (void)fifo;
    (void)data;
    (void)size;

    return FIFO_SUCCESS;
}

uint8_t fifo_pop(fifo_t *fifo)
{
    uint8_t data = 0;

    data = fifo->buffer[fifo->first];
    fifo->first = (fifo->first + 1) % fifo->size;

    return data;
}

uint8_t* fifo_pop_multiple(fifo_t *fifo, uint16_t size)
{
    (void)fifo;
    (void)size;

    return fifo->buffer;
}

fifo_result_t fifo_is_empty(fifo_t *fifo)
{
    if (fifo->first == fifo->last) {
        return FIFO_TRUE;
    } else {
        return FIFO_FALSE;
    }
}

fifo_result_t fifo_is_full(fifo_t *fifo)
{
    (void)fifo;

    /* TODO */
    return FIFO_FALSE;
}

uint16_t fifo_length(fifo_t *fifo) {
    (void)fifo;

    return 0;
}

fifo_result_t fifo_search(fifo_t *fifo, uint8_t data)
{
    for (uint16_t i; fifo->size > i; ++i) {
        if (data == fifo->buffer[i]) {
            return FIFO_TRUE;
        }
    }

    return FIFO_FALSE;
}