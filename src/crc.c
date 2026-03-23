#include "crc.h"

/* -------------------------------------------------------------------------
 * Reflect n bits of x
 * ------------------------------------------------------------------------- */
static uint64_t reflect(uint64_t x, int n)
{
    uint64_t result = 0;
    for (int i = 0; i < n; i++)
        if (x & (1ULL << i))
            result |= 1ULL << (n - 1 - i);
    return result;
}

/* -------------------------------------------------------------------------
 * Universal CRC compute — works for any width 3..64
 * Note: CRC-82/DARC requires 82-bit arithmetic and is not supported
 * ------------------------------------------------------------------------- */
uint64_t crc_compute(const crc_params_t *p, const uint8_t *data, size_t len)
{
    uint64_t mask    = (p->width == 64) ? ~0ULL : (1ULL << p->width) - 1;
    uint64_t top_bit = 1ULL << (p->width - 1);
    uint64_t crc     = p->init & mask;

    for (size_t i = 0; i < len; i++) {
        uint8_t byte = data[i];
        for (int b = 0; b < 8; b++) {
            uint64_t in_bit = p->ref_in
                ? ((byte >> b) & 1)
                : ((byte >> (7 - b)) & 1);

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

int crc_verify(const crc_params_t *p, const uint8_t *data, size_t len, uint64_t received_crc)
{
    return crc_compute(p, data, len) == received_crc;
}

int crc_verify_frame(const crc_params_t *p, const uint8_t *frame, size_t frame_len)
{
    return crc_compute(p, frame, frame_len) == p->residue;
}
/* -------------------------------------------------------------------------
 * All 113 algorithms from reveng.sourceforge.io/crc-catalogue (Dec 2024)
 * Format: name, width, poly, init, ref_in, ref_out, xor_out, check
 * ------------------------------------------------------------------------- */

/* 3-bit */
const crc_params_t CRC_3_GSM        = {"CRC-3/GSM",        3,  0x3,               0x0,               0,0, 0x7,               0x4,       0x2};
const crc_params_t CRC_3_ROHC       = {"CRC-3/ROHC",       3,  0x3,               0x7,               1,1, 0x0,               0x6,       0x0};

/* 4-bit */
const crc_params_t CRC_4_G704       = {"CRC-4/G-704",      4,  0x3,               0x0,               1,1, 0x0,               0x7,       0x0};
const crc_params_t CRC_4_INTERLAKEN = {"CRC-4/INTERLAKEN", 4,  0x3,               0xf,               0,0, 0xf,               0xb,       0x2};

/* 5-bit */
const crc_params_t CRC_5_EPC_C1G2  = {"CRC-5/EPC-C1G2",   5,  0x09,              0x09,              0,0, 0x00,              0x00,       0x0};
const crc_params_t CRC_5_G704      = {"CRC-5/G-704",       5,  0x15,              0x00,              1,1, 0x00,              0x07,      0x0};
const crc_params_t CRC_5_USB       = {"CRC-5/USB",         5,  0x05,              0x1f,              1,1, 0x1f,              0x19,      0x06};

/* 6-bit */
const crc_params_t CRC_6_CDMA2000_A = {"CRC-6/CDMA2000-A", 6, 0x27,              0x3f,              0,0, 0x00,              0x0d,       0x0};
const crc_params_t CRC_6_CDMA2000_B = {"CRC-6/CDMA2000-B", 6, 0x07,              0x3f,              0,0, 0x00,              0x3b,       0x0};
const crc_params_t CRC_6_DARC      = {"CRC-6/DARC",        6,  0x19,              0x00,              1,1, 0x00,              0x26,      0x0};
const crc_params_t CRC_6_G704      = {"CRC-6/G-704",       6,  0x03,              0x00,              1,1, 0x00,              0x06,      0x0};
const crc_params_t CRC_6_GSM       = {"CRC-6/GSM",         6,  0x2f,              0x00,              0,0, 0x3f,              0x13,      0x3a};

/* 7-bit */
const crc_params_t CRC_7_MMC       = {"CRC-7/MMC",         7,  0x09,              0x00,              0,0, 0x00,              0x75, 0x0};
const crc_params_t CRC_7_ROHC      = {"CRC-7/ROHC",        7,  0x4f,              0x7f,              1,1, 0x00,              0x53, 0x0};
const crc_params_t CRC_7_UMTS      = {"CRC-7/UMTS",        7,  0x45,              0x00,              0,0, 0x00,              0x61, 0x0};

/* 8-bit */
const crc_params_t CRC_8_AUTOSAR   = {"CRC-8/AUTOSAR",     8,  0x2f,              0xff,              0,0, 0xff,              0xdf,       0x42};
const crc_params_t CRC_8_BLUETOOTH = {"CRC-8/BLUETOOTH",   8,  0xa7,              0x00,              1,1, 0x00,              0x26,       0x0};
const crc_params_t CRC_8_CDMA2000  = {"CRC-8/CDMA2000",    8,  0x9b,              0xff,              0,0, 0x00,              0xda,       0x0};
const crc_params_t CRC_8_DARC      = {"CRC-8/DARC",        8,  0x39,              0x00,              1,1, 0x00,              0x15,       0x0};
const crc_params_t CRC_8_DVB_S2    = {"CRC-8/DVB-S2",      8,  0xd5,              0x00,              0,0, 0x00,              0xbc,       0x0};
const crc_params_t CRC_8_GSM_A     = {"CRC-8/GSM-A",       8,  0x1d,              0x00,              0,0, 0x00,              0x37,       0x0};
const crc_params_t CRC_8_GSM_B     = {"CRC-8/GSM-B",       8,  0x49,              0x00,              0,0, 0xff,              0x94,      0x53};
const crc_params_t CRC_8_HITAG     = {"CRC-8/HITAG",       8,  0x1d,              0xff,              0,0, 0x00,              0xb4,       0x0};
const crc_params_t CRC_8_I_432_1   = {"CRC-8/I-432-1",     8,  0x07,              0x00,              0,0, 0x55,              0xa1,      0xac};
const crc_params_t CRC_8_I_CODE    = {"CRC-8/I-CODE",      8,  0x1d,              0xfd,              0,0, 0x00,              0x7e,       0x0};
const crc_params_t CRC_8_LTE       = {"CRC-8/LTE",         8,  0x9b,              0x00,              0,0, 0x00,              0xea,       0x0};
const crc_params_t CRC_8_MAXIM_DOW = {"CRC-8/MAXIM-DOW",   8,  0x31,              0x00,              1,1, 0x00,              0xa1,       0x0};
const crc_params_t CRC_8_MIFARE_MAD= {"CRC-8/MIFARE-MAD",  8,  0x1d,              0xc7,              0,0, 0x00,              0x99,       0x0};
const crc_params_t CRC_8_NRSC_5    = {"CRC-8/NRSC-5",      8,  0x31,              0xff,              0,0, 0x00,              0xf7,       0x0};
const crc_params_t CRC_8_OPENSAFETY= {"CRC-8/OPENSAFETY",  8,  0x2f,              0x00,              0,0, 0x00,              0x3e,       0x0};
const crc_params_t CRC_8_ROHC      = {"CRC-8/ROHC",        8,  0x07,              0xff,              1,1, 0x00,              0xd0,       0x0};
const crc_params_t CRC_8_SAE_J1850 = {"CRC-8/SAE-J1850",   8,  0x1d,              0xff,              0,0, 0xff,              0x4b,      0xc4};
const crc_params_t CRC_8_SMBUS     = {"CRC-8/SMBUS",       8,  0x07,              0x00,              0,0, 0x00,              0xf4,       0x0};
const crc_params_t CRC_8_TECH_3250 = {"CRC-8/TECH-3250",   8,  0x1d,              0xff,              1,1, 0x00,              0x97,       0x0};
const crc_params_t CRC_8_WCDMA     = {"CRC-8/WCDMA",       8,  0x9b,              0x00,              1,1, 0x00,              0x25,       0x0};

/* 10-bit */
const crc_params_t CRC_10_ATM      = {"CRC-10/ATM",        10, 0x233,             0x000,             0,0, 0x000,             0x199,       0x0};
const crc_params_t CRC_10_CDMA2000 = {"CRC-10/CDMA2000",   10, 0x3d9,             0x3ff,             0,0, 0x000,             0x233,       0x0};
const crc_params_t CRC_10_GSM      = {"CRC-10/GSM",        10, 0x175,             0x000,             0,0, 0x3ff,             0x12a,     0x0c6};

/* 11-bit */
const crc_params_t CRC_11_FLEXRAY  = {"CRC-11/FLEXRAY",    11, 0x385,             0x01a,             0,0, 0x000,             0x5a3,       0x0};
const crc_params_t CRC_11_UMTS     = {"CRC-11/UMTS",       11, 0x307,             0x000,             0,0, 0x000,             0x061,       0x0};

/* 12-bit */
const crc_params_t CRC_12_3GPP     = {"CRC-12/3GPP",       12, 0x80f,             0x000,             0,1, 0x000,             0xdaf,       0x0};
const crc_params_t CRC_12_DECT     = {"CRC-12/DECT",       12, 0x80f,             0x000,             0,0, 0x000,             0xf5b,       0x0};
const crc_params_t CRC_12_GSM      = {"CRC-12/GSM",        12, 0xd31,             0x000,             0,0, 0xfff,             0xb34,     0x178};
const crc_params_t CRC_12_UMTS     = {"CRC-12/UMTS",       12, 0x80f,             0x000,             0,1, 0x000,             0xdaf,       0x0};

/* 13-bit */
const crc_params_t CRC_13_BBC      = {"CRC-13/BBC",        13, 0x1cf5,            0x0000,            0,0, 0x0000,            0x04fa,       0x0};

/* 14-bit */
const crc_params_t CRC_14_DARC     = {"CRC-14/DARC",       14, 0x0805,            0x0000,            1,1, 0x0000,            0x082d,       0x0};
const crc_params_t CRC_14_GSM      = {"CRC-14/GSM",        14, 0x202d,            0x0000,            0,0, 0x3fff,            0x30ae,    0x031e};

/* 15-bit */
const crc_params_t CRC_15_CAN      = {"CRC-15/CAN",        15, 0x4599,            0x0000,            0,0, 0x0000,            0x059e,       0x0};
const crc_params_t CRC_15_MPT1327  = {"CRC-15/MPT1327",    15, 0x6815,            0x0000,            0,0, 0x0001,            0x2566,    0x6815};

/* 16-bit */
const crc_params_t CRC_16_ARC           = {"CRC-16/ARC",           16, 0x8005, 0x0000, 1,1, 0x0000, 0xbb3d, 0x0};
const crc_params_t CRC_16_CDMA2000      = {"CRC-16/CDMA2000",      16, 0xc867, 0xffff, 0,0, 0x0000, 0x4c06, 0x0};
const crc_params_t CRC_16_CMS           = {"CRC-16/CMS",           16, 0x8005, 0xffff, 0,0, 0x0000, 0xaee7, 0x0};
const crc_params_t CRC_16_DDS_110       = {"CRC-16/DDS-110",       16, 0x8005, 0x800d, 0,0, 0x0000, 0x9ecf, 0x0};
const crc_params_t CRC_16_DECT_R        = {"CRC-16/DECT-R",        16, 0x0589, 0x0000, 0,0, 0x0001, 0x007e, 0x0589};
const crc_params_t CRC_16_DECT_X        = {"CRC-16/DECT-X",        16, 0x0589, 0x0000, 0,0, 0x0000, 0x007f, 0x0};
const crc_params_t CRC_16_DNP           = {"CRC-16/DNP",           16, 0x3d65, 0x0000, 1,1, 0xffff, 0xea82, 0x66c5};
const crc_params_t CRC_16_EN_13757      = {"CRC-16/EN-13757",      16, 0x3d65, 0x0000, 0,0, 0xffff, 0xc2b7, 0xa366};
const crc_params_t CRC_16_GENIBUS       = {"CRC-16/GENIBUS",       16, 0x1021, 0xffff, 0,0, 0xffff, 0xd64e, 0x1d0f};
const crc_params_t CRC_16_GSM           = {"CRC-16/GSM",           16, 0x1021, 0x0000, 0,0, 0xffff, 0xce3c, 0x1d0f};
const crc_params_t CRC_16_IBM_3740      = {"CRC-16/IBM-3740",      16, 0x1021, 0xffff, 0,0, 0x0000, 0x29b1, 0x0};
const crc_params_t CRC_16_IBM_SDLC      = {"CRC-16/IBM-SDLC",      16, 0x1021, 0xffff, 1,1, 0xffff, 0x906e, 0xf0b8};
const crc_params_t CRC_16_ISO_IEC_14443_3_A = {"CRC-16/ISO-IEC-14443-3-A", 16, 0x1021, 0xc6c6, 1,1, 0x0000, 0xbf05, 0x0};
/* Note: check value 0xbf05 matches CRC-A; ISO-IEC-14443-3-A is an alias */
const crc_params_t CRC_16_KERMIT        = {"CRC-16/KERMIT",        16, 0x1021, 0x0000, 1,1, 0x0000, 0x2189, 0x0};
const crc_params_t CRC_16_LJ1200        = {"CRC-16/LJ1200",        16, 0x6f63, 0x0000, 0,0, 0x0000, 0xbdf4, 0x0};
const crc_params_t CRC_16_M17           = {"CRC-16/M17",           16, 0x5935, 0xffff, 0,0, 0x0000, 0x772b, 0x0};
const crc_params_t CRC_16_MAXIM_DOW     = {"CRC-16/MAXIM-DOW",     16, 0x8005, 0x0000, 1,1, 0xffff, 0x44c2, 0xb001};
const crc_params_t CRC_16_MCRF4XX       = {"CRC-16/MCRF4XX",       16, 0x1021, 0xffff, 1,1, 0x0000, 0x6f91, 0x0};
const crc_params_t CRC_16_MODBUS        = {"CRC-16/MODBUS",        16, 0x8005, 0xffff, 1,1, 0x0000, 0x4b37, 0x0};
const crc_params_t CRC_16_NRSC_5        = {"CRC-16/NRSC-5",        16, 0x080b, 0xffff, 1,1, 0x0000, 0xa066, 0x0};
const crc_params_t CRC_16_OPENSAFETY_A  = {"CRC-16/OPENSAFETY-A",  16, 0x5935, 0x0000, 0,0, 0x0000, 0x5d38, 0x0};
const crc_params_t CRC_16_OPENSAFETY_B  = {"CRC-16/OPENSAFETY-B",  16, 0x755b, 0x0000, 0,0, 0x0000, 0x20fe, 0x0};
const crc_params_t CRC_16_PROFIBUS      = {"CRC-16/PROFIBUS",      16, 0x1dcf, 0xffff, 0,0, 0xffff, 0xa819, 0xe394};
const crc_params_t CRC_16_RIELLO        = {"CRC-16/RIELLO",        16, 0x1021, 0xb2aa, 1,1, 0x0000, 0x63d0, 0x0};
const crc_params_t CRC_16_SPI_FUJITSU   = {"CRC-16/SPI-FUJITSU",   16, 0x1021, 0x1d0f, 0,0, 0x0000, 0xe5cc, 0x0};
const crc_params_t CRC_16_T10_DIF       = {"CRC-16/T10-DIF",       16, 0x8bb7, 0x0000, 0,0, 0x0000, 0xd0db, 0x0};
const crc_params_t CRC_16_TELEDISK      = {"CRC-16/TELEDISK",      16, 0xa097, 0x0000, 0,0, 0x0000, 0x0fb3, 0x0};
const crc_params_t CRC_16_TMS37157      = {"CRC-16/TMS37157",      16, 0x1021, 0x89ec, 1,1, 0x0000, 0x26b1, 0x0};
const crc_params_t CRC_16_UMTS          = {"CRC-16/UMTS",          16, 0x8005, 0x0000, 0,0, 0x0000, 0xfee8, 0x0};
const crc_params_t CRC_16_USB           = {"CRC-16/USB",           16, 0x8005, 0xffff, 1,1, 0xffff, 0xb4c8, 0xb001};
const crc_params_t CRC_16_XMODEM        = {"CRC-16/XMODEM",        16, 0x1021, 0x0000, 0,0, 0x0000, 0x31c3, 0x0};

/* 17-bit */
const crc_params_t CRC_17_CAN_FD   = {"CRC-17/CAN-FD",    17, 0x1685b,           0x00000,           0,0, 0x00000,           0x04f03, 0x0};

/* 21-bit */
const crc_params_t CRC_21_CAN_FD   = {"CRC-21/CAN-FD",    21, 0x102899,          0x000000,          0,0, 0x000000,          0x0ed841, 0x0};

/* 24-bit */
const crc_params_t CRC_24_BLE       = {"CRC-24/BLE",       24, 0x00065b,          0x555555,          1,1, 0x000000,          0xc25a56, 0x0};
const crc_params_t CRC_24_FLEXRAY_A = {"CRC-24/FLEXRAY-A", 24, 0x5d6dcb,          0xfedcba,          0,0, 0x000000,          0x7979bd, 0x0};
const crc_params_t CRC_24_FLEXRAY_B = {"CRC-24/FLEXRAY-B", 24, 0x5d6dcb,          0xabcdef,          0,0, 0x000000,          0x1f23b8, 0x0};
const crc_params_t CRC_24_INTERLAKEN= {"CRC-24/INTERLAKEN",24, 0x328b63,          0xffffff,          0,0, 0xffffff,          0xb4f3e6,        0x144e63};
const crc_params_t CRC_24_LTE_A     = {"CRC-24/LTE-A",     24, 0x864cfb,          0x000000,          0,0, 0x000000,          0xcde703, 0x0};
const crc_params_t CRC_24_LTE_B     = {"CRC-24/LTE-B",     24, 0x800063,          0x000000,          0,0, 0x000000,          0x23ef52, 0x0};
const crc_params_t CRC_24_OPENPGP   = {"CRC-24/OPENPGP",   24, 0x864cfb,          0xb704ce,          0,0, 0x000000,          0x21cf02, 0x0};
const crc_params_t CRC_24_OS_9      = {"CRC-24/OS-9",      24, 0x800063,          0xffffff,          0,0, 0xffffff,          0x200fa5,        0x800fe3};

/* 30-bit */
const crc_params_t CRC_30_CDMA      = {"CRC-30/CDMA",      30, 0x2030b9c7,        0x3fffffff,        0,0, 0x3fffffff,        0x04c34abf,      0x34efa55a};

/* 31-bit */
const crc_params_t CRC_31_PHILIPS   = {"CRC-31/PHILIPS",   31, 0x04c11db7,        0x7fffffff,        0,0, 0x7fffffff,        0x0ce9e46c,      0x4eaf26f1};

/* 32-bit */
const crc_params_t CRC_32_AIXM      = {"CRC-32/AIXM",      32, 0x814141ab,        0x00000000,        0,0, 0x00000000,        0x3010bf7f, 0x0};
const crc_params_t CRC_32_AUTOSAR   = {"CRC-32/AUTOSAR",   32, 0xf4acfb13,        0xffffffff,        1,1, 0xffffffff,        0x1697d06a,      0x904cddbf};
const crc_params_t CRC_32_BASE91_D  = {"CRC-32/BASE91-D",  32, 0xa833982b,        0xffffffff,        1,1, 0xffffffff,        0x87315576,      0x45270551};
const crc_params_t CRC_32_BZIP2     = {"CRC-32/BZIP2",     32, 0x04c11db7,        0xffffffff,        0,0, 0xffffffff,        0xfc891918,      0xc704dd7b};
const crc_params_t CRC_32_CD_ROM_EDC= {"CRC-32/CD-ROM-EDC",32, 0x8001801b,        0x00000000,        1,1, 0x00000000,        0x6ec2edc4, 0x0};
const crc_params_t CRC_32_CKSUM     = {"CRC-32/CKSUM",     32, 0x04c11db7,        0x00000000,        0,0, 0xffffffff,        0x765e7680,      0xc704dd7b};
const crc_params_t CRC_32_ISCSI     = {"CRC-32/ISCSI",     32, 0x1edc6f41,        0xffffffff,        1,1, 0xffffffff,        0xe3069283,      0xb798b438};
const crc_params_t CRC_32_ISO_HDLC  = {"CRC-32/ISO-HDLC",  32, 0x04c11db7,        0xffffffff,        1,1, 0xffffffff,        0xcbf43926,      0xdebb20e3};
const crc_params_t CRC_32_JAMCRC    = {"CRC-32/JAMCRC",    32, 0x04c11db7,        0xffffffff,        1,1, 0x00000000,        0x340bc6d9, 0x0};
const crc_params_t CRC_32_MEF       = {"CRC-32/MEF",       32, 0x741b8cd7,        0xffffffff,        1,1, 0x00000000,        0xd2c22f51, 0x0};
const crc_params_t CRC_32_MPEG_2    = {"CRC-32/MPEG-2",    32, 0x04c11db7,        0xffffffff,        0,0, 0x00000000,        0x0376e6e7, 0x0};
const crc_params_t CRC_32_XFER      = {"CRC-32/XFER",      32, 0x000000af,        0x00000000,        0,0, 0x00000000,        0xbd0be338, 0x0};

/* 40-bit */
const crc_params_t CRC_40_GSM       = {"CRC-40/GSM",       40, 0x0004820009ULL,   0x0000000000ULL,   0,0, 0xffffffffffULL,   0xd4164fc646ULL, 0xc4ff8071ff};

/* 64-bit */
const crc_params_t CRC_64_ECMA_182  = {"CRC-64/ECMA-182",  64, 0x42f0e1eba9ea3693ULL, 0x0000000000000000ULL, 0,0, 0x0000000000000000ULL, 0x6c40df5f0b497347ULL, 0x0};
const crc_params_t CRC_64_GO_ISO    = {"CRC-64/GO-ISO",    64, 0x000000000000001bULL, 0xffffffffffffffffULL, 1,1, 0xffffffffffffffffULL, 0xb90956c775a41001ULL, 0x5300000000000000};
const crc_params_t CRC_64_MS        = {"CRC-64/MS",        64, 0x259c84cba6426349ULL, 0xffffffffffffffffULL, 1,1, 0x0000000000000000ULL, 0x75d4b74f024eceeaULL, 0x0};
const crc_params_t CRC_64_NVME      = {"CRC-64/NVME",      64, 0xad93d23594c93659ULL, 0xffffffffffffffffULL, 1,1, 0xffffffffffffffffULL, 0xae8b14860a799888ULL, 0xf310303b2b6f6e42};
const crc_params_t CRC_64_REDIS     = {"CRC-64/REDIS",     64, 0xad93d23594c935a9ULL, 0x0000000000000000ULL, 1,1, 0x0000000000000000ULL, 0xe9c6d914c4b8d9caULL, 0x0};
const crc_params_t CRC_64_WE        = {"CRC-64/WE",        64, 0x42f0e1eba9ea3693ULL, 0xffffffffffffffffULL, 0,0, 0xffffffffffffffffULL, 0x62ec59e3f1a4f00aULL, 0xfcacbebd5931a992};
const crc_params_t CRC_64_XZ        = {"CRC-64/XZ",        64, 0x42f0e1eba9ea3693ULL, 0xffffffffffffffffULL, 1,1, 0xffffffffffffffffULL, 0x995dc9bbdf1939faULL, 0x49958c9abd7d353f};

