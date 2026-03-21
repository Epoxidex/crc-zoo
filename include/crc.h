#ifndef CRC_H
#define CRC_H

#include <stdint.h>
#include <stddef.h>

typedef struct {
    const char *name;
    int         width;
    uint64_t    poly;
    uint64_t    init;
    int         ref_in;
    int         ref_out;
    uint64_t    xor_out;
    uint64_t    check;
} crc_params_t;

uint64_t crc_compute(const crc_params_t *p, const uint8_t *data, size_t len);

#endif
