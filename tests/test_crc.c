#include <stdio.h>
#include <stdint.h>
#include <stddef.h>
#include "crc.h"

int main(void)
{
    const uint8_t data[] = "123456789";
    int failures = 0;

    crc_params_t crc8 = {"CRC-8", 8, 0x07, 0x00, 0, 0, 0x00, 0xF4};
    uint64_t result = crc_compute(&crc8, data, 9);
    printf("CRC-8: 0x%02lX (ожидается 0xF4) — %s\n",
           result, result == 0xF4 ? "OK" : "FAIL");
    if (result != 0xF4) failures++;

    crc_params_t crc16_modbus = {"CRC-16/MODBUS", 16, 0x8005, 0xFFFF, 1, 1, 0x00, 0x4B37};
    result = crc_compute(&crc16_modbus, data, 9);
    printf("CRC-16/MODBUS: 0x%04lX (ожидается 0x4B37) — %s\n",
       result, result == 0x4B37 ? "OK" : "FAIL");
    if (result != 0x4B37) failures++;

    crc_params_t crc32 = {"CRC-32/zlib", 32, 0x04C11DB7, 0xFFFFFFFF, 1, 1, 0xFFFFFFFF, 0xCBF43926};
    result = crc_compute(&crc32, data, 9);
    printf("CRC-32/zlib:   0x%08lX (ожидается 0xCBF43926) — %s\n",
       result, result == 0xCBF43926 ? "OK" : "FAIL");
    if (result != 0xCBF43926) failures++;

    return failures == 0 ? 0 : 1;
}
