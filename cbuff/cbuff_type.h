#ifndef __CBUFF_TYPE_H__
#define __CBUFF_TYPE_H__

#ifndef CBUFF_BUFFER_SIZE
#error Must define CBUFF_BUFFER_SIZE before including cbuff_type.h
#endif // CBUFF_BUFFER_SIZE

typedef struct
{
    volatile uint8_t put_index;
    volatile uint8_t get_index;
    volatile uint8_t is_empty;
    volatile uint8_t buffer[CBUFF_BUFFER_SIZE];
} CBUFF;

#endif // __CBUFF_TYPE_H__
