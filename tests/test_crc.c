#include <inttypes.h>
#include <stdio.h>
#include <stdint.h>
#include <stddef.h>
#include <string.h>
#include "crc.h"

/* Standard check string per Ross Williams model */
static const uint8_t CHECK_DATA[] = "123456789";
#define CHECK_LEN 9

static int failures = 0;

static void check(const crc_params_t *p)
{
    uint64_t result = crc_compute(p, CHECK_DATA, CHECK_LEN);
    int ok = (result == p->check);
    int ok_verify = crc_verify(p, CHECK_DATA, CHECK_LEN, p->check);
    if (!ok || !ok_verify) failures++;

    const char *frame_status;
    if (p->width % 8 != 0) {
        frame_status = "skip";
    } else {
        int bytes = p->width / 8;
        uint8_t frame[CHECK_LEN + 8];
        memcpy(frame, CHECK_DATA, CHECK_LEN);
        uint64_t crc = p->check;
        if (p->ref_out) {
            for (int i = 0; i < bytes; i++)
                frame[CHECK_LEN + i] = (crc >> (8 * i)) & 0xff;
        } else {
            for (int i = 0; i < bytes; i++)
                frame[CHECK_LEN + i] = (crc >> (8 * (bytes - 1 - i))) & 0xff;
        }
        int ok_frame = crc_verify_frame(p, frame, CHECK_LEN + bytes);
        if (!ok_frame) failures++;
        frame_status = ok_frame ? "OK" : "FAIL";
    }

    printf("%-30s 0x%016"PRIx64"  %-4s  frame: %s\n",
           p->name, result, ok ? "OK" : "FAIL", frame_status);
}

static const crc_params_t * const all_crcs[] = {
    &CRC_3_GSM,      &CRC_3_ROHC,
    &CRC_4_G704,     &CRC_4_INTERLAKEN,
    &CRC_5_EPC_C1G2, &CRC_5_G704,      &CRC_5_USB,
    &CRC_6_CDMA2000_A, &CRC_6_CDMA2000_B, &CRC_6_DARC, &CRC_6_G704, &CRC_6_GSM,
    &CRC_7_MMC,      &CRC_7_ROHC,      &CRC_7_UMTS,
    &CRC_8_AUTOSAR,  &CRC_8_BLUETOOTH, &CRC_8_CDMA2000,  &CRC_8_DARC,
    &CRC_8_DVB_S2,   &CRC_8_GSM_A,     &CRC_8_GSM_B,     &CRC_8_HITAG,
    &CRC_8_I_432_1,  &CRC_8_I_CODE,    &CRC_8_LTE,       &CRC_8_MAXIM_DOW,
    &CRC_8_MIFARE_MAD, &CRC_8_NRSC_5,  &CRC_8_OPENSAFETY, &CRC_8_ROHC,
    &CRC_8_SAE_J1850, &CRC_8_SMBUS,    &CRC_8_TECH_3250, &CRC_8_WCDMA,
    &CRC_10_ATM,     &CRC_10_CDMA2000, &CRC_10_GSM,
    &CRC_11_FLEXRAY, &CRC_11_UMTS,
    &CRC_12_3GPP,    &CRC_12_DECT,     &CRC_12_GSM,      &CRC_12_UMTS,
    &CRC_13_BBC,
    &CRC_14_DARC,    &CRC_14_GSM,
    &CRC_15_CAN,     &CRC_15_MPT1327,
    &CRC_16_ARC,        &CRC_16_CDMA2000,     &CRC_16_CMS,          &CRC_16_DDS_110,
    &CRC_16_DECT_R,     &CRC_16_DECT_X,       &CRC_16_DNP,          &CRC_16_EN_13757,
    &CRC_16_GENIBUS,    &CRC_16_GSM,           &CRC_16_IBM_3740,     &CRC_16_IBM_SDLC,
    &CRC_16_ISO_IEC_14443_3_A, &CRC_16_KERMIT, &CRC_16_LJ1200,      &CRC_16_M17,
    &CRC_16_MAXIM_DOW,  &CRC_16_MCRF4XX,      &CRC_16_MODBUS,       &CRC_16_NRSC_5,
    &CRC_16_OPENSAFETY_A, &CRC_16_OPENSAFETY_B, &CRC_16_PROFIBUS,   &CRC_16_RIELLO,
    &CRC_16_SPI_FUJITSU, &CRC_16_T10_DIF,     &CRC_16_TELEDISK,     &CRC_16_TMS37157,
    &CRC_16_UMTS,       &CRC_16_USB,           &CRC_16_XMODEM,
    &CRC_17_CAN_FD,
    &CRC_21_CAN_FD,
    &CRC_24_BLE,     &CRC_24_FLEXRAY_A, &CRC_24_FLEXRAY_B, &CRC_24_INTERLAKEN,
    &CRC_24_LTE_A,   &CRC_24_LTE_B,     &CRC_24_OPENPGP,   &CRC_24_OS_9,
    &CRC_30_CDMA,    &CRC_31_PHILIPS,
    &CRC_32_AIXM,    &CRC_32_AUTOSAR,  &CRC_32_BASE91_D, &CRC_32_BZIP2,
    &CRC_32_CD_ROM_EDC, &CRC_32_CKSUM, &CRC_32_ISCSI,    &CRC_32_ISO_HDLC,
    &CRC_32_JAMCRC,  &CRC_32_MEF,      &CRC_32_MPEG_2,   &CRC_32_XFER,
    &CRC_40_GSM,
    &CRC_64_ECMA_182, &CRC_64_GO_ISO,  &CRC_64_MS,       &CRC_64_NVME,
    &CRC_64_REDIS,    &CRC_64_WE,      &CRC_64_XZ,
};
#define N_CRCS (sizeof(all_crcs) / sizeof(all_crcs[0]))

int main(void)
{
    printf("%-30s %-18s  %-4s  %s\n", "Algorithm", "Result", "CRC", "Frame");
    printf("%.60s\n", "------------------------------------------------------------");

    for (size_t i = 0; i < N_CRCS; i++)
        check(all_crcs[i]);

    printf("%.60s\n", "------------------------------------------------------------");
    printf("Result: %d FAIL\n", failures);
    return failures == 0 ? 0 : 1;
}
