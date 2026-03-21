#include <stdio.h>
#include <stdint.h>
#include <stddef.h>
#include "crc.h"

/* Standard check string per Ross Williams model */
static const uint8_t CHECK_DATA[] = "123456789";
#define CHECK_LEN 9

static int failures = 0;

static void check(const crc_params_t *p)
{
    uint64_t result = crc_compute(p, CHECK_DATA, CHECK_LEN);
    int ok = (result == p->check);
    if (!ok) failures++;
    printf("%-30s 0x%016lX  %s\n", p->name, result, ok ? "OK" : "FAIL");
}

int main(void)
{
    printf("%-30s %-18s  %s\n", "Algorithm", "Result", "Status");
    printf("%.60s\n", "------------------------------------------------------------");

    check(&CRC_3_GSM);
    check(&CRC_3_ROHC);
    check(&CRC_4_G704);
    check(&CRC_4_INTERLAKEN);
    check(&CRC_5_EPC_C1G2);
    check(&CRC_5_G704);
    check(&CRC_5_USB);
    check(&CRC_6_CDMA2000_A);
    check(&CRC_6_CDMA2000_B);
    check(&CRC_6_DARC);
    check(&CRC_6_G704);
    check(&CRC_6_GSM);
    check(&CRC_7_MMC);
    check(&CRC_7_ROHC);
    check(&CRC_7_UMTS);
    check(&CRC_8_AUTOSAR);
    check(&CRC_8_BLUETOOTH);
    check(&CRC_8_CDMA2000);
    check(&CRC_8_DARC);
    check(&CRC_8_DVB_S2);
    check(&CRC_8_GSM_A);
    check(&CRC_8_GSM_B);
    check(&CRC_8_HITAG);
    check(&CRC_8_I_432_1);
    check(&CRC_8_I_CODE);
    check(&CRC_8_LTE);
    check(&CRC_8_MAXIM_DOW);
    check(&CRC_8_MIFARE_MAD);
    check(&CRC_8_NRSC_5);
    check(&CRC_8_OPENSAFETY);
    check(&CRC_8_ROHC);
    check(&CRC_8_SAE_J1850);
    check(&CRC_8_SMBUS);
    check(&CRC_8_TECH_3250);
    check(&CRC_8_WCDMA);
    check(&CRC_10_ATM);
    check(&CRC_10_CDMA2000);
    check(&CRC_10_GSM);
    check(&CRC_11_FLEXRAY);
    check(&CRC_11_UMTS);
    check(&CRC_12_3GPP);
    check(&CRC_12_DECT);
    check(&CRC_12_GSM);
    check(&CRC_12_UMTS);
    check(&CRC_13_BBC);
    check(&CRC_14_DARC);
    check(&CRC_14_GSM);
    check(&CRC_15_CAN);
    check(&CRC_15_MPT1327);
    check(&CRC_16_ARC);
    check(&CRC_16_CDMA2000);
    check(&CRC_16_CMS);
    check(&CRC_16_DDS_110);
    check(&CRC_16_DECT_R);
    check(&CRC_16_DECT_X);
    check(&CRC_16_DNP);
    check(&CRC_16_EN_13757);
    check(&CRC_16_GENIBUS);
    check(&CRC_16_GSM);
    check(&CRC_16_IBM_3740);
    check(&CRC_16_IBM_SDLC);
    check(&CRC_16_ISO_IEC_14443_3_A);
    check(&CRC_16_KERMIT);
    check(&CRC_16_LJ1200);
    check(&CRC_16_M17);
    check(&CRC_16_MAXIM_DOW);
    check(&CRC_16_MCRF4XX);
    check(&CRC_16_MODBUS);
    check(&CRC_16_NRSC_5);
    check(&CRC_16_OPENSAFETY_A);
    check(&CRC_16_OPENSAFETY_B);
    check(&CRC_16_PROFIBUS);
    check(&CRC_16_RIELLO);
    check(&CRC_16_SPI_FUJITSU);
    check(&CRC_16_T10_DIF);
    check(&CRC_16_TELEDISK);
    check(&CRC_16_TMS37157);
    check(&CRC_16_UMTS);
    check(&CRC_16_USB);
    check(&CRC_16_XMODEM);
    check(&CRC_17_CAN_FD);
    check(&CRC_21_CAN_FD);
    check(&CRC_24_BLE);
    check(&CRC_24_FLEXRAY_A);
    check(&CRC_24_FLEXRAY_B);
    check(&CRC_24_INTERLAKEN);
    check(&CRC_24_LTE_A);
    check(&CRC_24_LTE_B);
    check(&CRC_24_OPENPGP);
    check(&CRC_24_OS_9);
    check(&CRC_30_CDMA);
    check(&CRC_31_PHILIPS);
    check(&CRC_32_AIXM);
    check(&CRC_32_AUTOSAR);
    check(&CRC_32_BASE91_D);
    check(&CRC_32_BZIP2);
    check(&CRC_32_CD_ROM_EDC);
    check(&CRC_32_CKSUM);
    check(&CRC_32_ISCSI);
    check(&CRC_32_ISO_HDLC);
    check(&CRC_32_JAMCRC);
    check(&CRC_32_MEF);
    check(&CRC_32_MPEG_2);
    check(&CRC_32_XFER);
    check(&CRC_40_GSM);
    check(&CRC_64_ECMA_182);
    check(&CRC_64_GO_ISO);
    check(&CRC_64_MS);
    check(&CRC_64_NVME);
    check(&CRC_64_REDIS);
    check(&CRC_64_WE);
    check(&CRC_64_XZ);

    printf("%.60s\n", "------------------------------------------------------------");
    printf("Result: %d FAIL\n", failures);
    return failures == 0 ? 0 : 1;
}
