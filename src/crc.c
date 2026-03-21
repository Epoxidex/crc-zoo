#include <stdint.h>
#include <stddef.h>
#include "crc.h"


uint8_t crc8(const uint8_t *data, size_t len)
{
  const uint8_t poly = 0x07;
  uint8_t crc = 0x00;

  for (size_t i = 0; i < len; i++) {
    crc ^= data[i];
    for (int bit = 0; bit < 8; bit++) {
      if (crc & 0x80) {
        crc <<= 1;
        crc ^= poly;
      } else {
        crc <<= 1;
      }
    }
  }
  return crc;
}

uint64_t reflect(uint64_t x, int n)
{
    uint64_t result = 0;
    for (int i = 0; i < n; i++)
        if (x & (1ULL << i))
            result |= 1ULL << (n - 1 - i);
    return result;
}

uint64_t crc_compute(const crc_params_t *p, const uint8_t *data, size_t len)
{
    uint64_t mask = (p->width == 64) ? ~0ULL : (1ULL << p->width) - 1;
    uint64_t top_bit = 1ULL << (p->width-1);
    uint64_t crc = p->init & mask;
    
    for (int i = 0; i < len; i++)
    {
        for (int bit = 0; bit < 8; bit++)
        {
           uint64_t in_bit = p->ref_in ? ((data[i] >> bit) & 1) : ((data[i] >> (7 - bit)) & 1);
           uint64_t do_xor = in_bit ^ ((crc & top_bit) ? 1ULL : 0ULL);      
           crc = (crc << 1) & mask;
           if (do_xor)
              crc ^= p->poly;
        }
    }
    
    if (p->ref_out)
        crc = reflect(crc, p->width);
    
    return (crc ^ p->xor_out) & mask;
}
