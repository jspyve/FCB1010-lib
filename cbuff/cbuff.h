#ifndef __CBUFF_H__
#define __CBUFF_H__

#include <string.h>
#include "cbuff_type.h"

#define CBUFF_INLINE_SPEC static inline

CBUFF_INLINE_SPEC void CB_init(CBUFF *cb) __critical
{
    memset(cb, 0, sizeof(CBUFF));
    cb->get_index = cb->put_index = 0;
    cb->is_empty = 1;
}

CBUFF_INLINE_SPEC void CB_put(CBUFF *cb, uint8_t c) __critical
{
    if (cb->get_index == cb->put_index && !cb->is_empty)
    {
        return;
    }

    cb->buffer[cb->put_index++] = c;

    cb->is_empty = 0;

    if (cb->put_index >= CBUFF_BUFFER_SIZE)
    {
        cb->put_index = 0;
    }
}

CBUFF_INLINE_SPEC uint8_t CB_get(CBUFF *cb) __critical
{
    uint8_t c;

    if (cb->is_empty)
    {
        return 0xff;
    }

    c = cb->buffer[cb->get_index++];

    if (cb->get_index >= CBUFF_BUFFER_SIZE)
    {
        cb->get_index = 0;
    }

    if (cb->get_index == cb->put_index)
    {
        cb->is_empty = 1;
    }

    return c;
}

CBUFF_INLINE_SPEC uint8_t CB_isEmpty(CBUFF *cb) __critical
{
    return cb->is_empty;
}

CBUFF_INLINE_SPEC uint8_t CB_isFull(CBUFF *cb) __critical
{
    return (!cb->is_empty) && (cb->get_index == cb->put_index);
}

#endif // __CBUFF_H__
