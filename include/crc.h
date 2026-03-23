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
    uint64_t    residue;
} crc_params_t;

uint64_t crc_compute(const crc_params_t *p, const uint8_t *data, size_t len);

int crc_verify(const crc_params_t *p, const uint8_t *data, size_t len, uint64_t received_crc);
int crc_verify_frame(const crc_params_t *p, const uint8_t *frame, size_t frame_len);

extern const crc_params_t CRC_3_GSM;
extern const crc_params_t CRC_3_ROHC;
extern const crc_params_t CRC_4_G704;
extern const crc_params_t CRC_4_INTERLAKEN;
extern const crc_params_t CRC_5_EPC_C1G2;
extern const crc_params_t CRC_5_G704;
extern const crc_params_t CRC_5_USB;
extern const crc_params_t CRC_6_CDMA2000_A;
extern const crc_params_t CRC_6_CDMA2000_B;
extern const crc_params_t CRC_6_DARC;
extern const crc_params_t CRC_6_G704;
extern const crc_params_t CRC_6_GSM;
extern const crc_params_t CRC_7_MMC;
extern const crc_params_t CRC_7_ROHC;
extern const crc_params_t CRC_7_UMTS;
extern const crc_params_t CRC_8_AUTOSAR;
extern const crc_params_t CRC_8_BLUETOOTH;
extern const crc_params_t CRC_8_CDMA2000;
extern const crc_params_t CRC_8_DARC;
extern const crc_params_t CRC_8_DVB_S2;
extern const crc_params_t CRC_8_GSM_A;
extern const crc_params_t CRC_8_GSM_B;
extern const crc_params_t CRC_8_HITAG;
extern const crc_params_t CRC_8_I_432_1;
extern const crc_params_t CRC_8_I_CODE;
extern const crc_params_t CRC_8_LTE;
extern const crc_params_t CRC_8_MAXIM_DOW;
extern const crc_params_t CRC_8_MIFARE_MAD;
extern const crc_params_t CRC_8_NRSC_5;
extern const crc_params_t CRC_8_OPENSAFETY;
extern const crc_params_t CRC_8_ROHC;
extern const crc_params_t CRC_8_SAE_J1850;
extern const crc_params_t CRC_8_SMBUS;
extern const crc_params_t CRC_8_TECH_3250;
extern const crc_params_t CRC_8_WCDMA;
extern const crc_params_t CRC_10_ATM;
extern const crc_params_t CRC_10_CDMA2000;
extern const crc_params_t CRC_10_GSM;
extern const crc_params_t CRC_11_FLEXRAY;
extern const crc_params_t CRC_11_UMTS;
extern const crc_params_t CRC_12_3GPP;
extern const crc_params_t CRC_12_DECT;
extern const crc_params_t CRC_12_GSM;
extern const crc_params_t CRC_12_UMTS;
extern const crc_params_t CRC_13_BBC;
extern const crc_params_t CRC_14_DARC;
extern const crc_params_t CRC_14_GSM;
extern const crc_params_t CRC_15_CAN;
extern const crc_params_t CRC_15_MPT1327;
extern const crc_params_t CRC_16_ARC;
extern const crc_params_t CRC_16_CDMA2000;
extern const crc_params_t CRC_16_CMS;
extern const crc_params_t CRC_16_DDS_110;
extern const crc_params_t CRC_16_DECT_R;
extern const crc_params_t CRC_16_DECT_X;
extern const crc_params_t CRC_16_DNP;
extern const crc_params_t CRC_16_EN_13757;
extern const crc_params_t CRC_16_GENIBUS;
extern const crc_params_t CRC_16_GSM;
extern const crc_params_t CRC_16_IBM_3740;
extern const crc_params_t CRC_16_IBM_SDLC;
extern const crc_params_t CRC_16_ISO_IEC_14443_3_A;
extern const crc_params_t CRC_16_KERMIT;
extern const crc_params_t CRC_16_LJ1200;
extern const crc_params_t CRC_16_M17;
extern const crc_params_t CRC_16_MAXIM_DOW;
extern const crc_params_t CRC_16_MCRF4XX;
extern const crc_params_t CRC_16_MODBUS;
extern const crc_params_t CRC_16_NRSC_5;
extern const crc_params_t CRC_16_OPENSAFETY_A;
extern const crc_params_t CRC_16_OPENSAFETY_B;
extern const crc_params_t CRC_16_PROFIBUS;
extern const crc_params_t CRC_16_RIELLO;
extern const crc_params_t CRC_16_SPI_FUJITSU;
extern const crc_params_t CRC_16_T10_DIF;
extern const crc_params_t CRC_16_TELEDISK;
extern const crc_params_t CRC_16_TMS37157;
extern const crc_params_t CRC_16_UMTS;
extern const crc_params_t CRC_16_USB;
extern const crc_params_t CRC_16_XMODEM;
extern const crc_params_t CRC_17_CAN_FD;
extern const crc_params_t CRC_21_CAN_FD;
extern const crc_params_t CRC_24_BLE;
extern const crc_params_t CRC_24_FLEXRAY_A;
extern const crc_params_t CRC_24_FLEXRAY_B;
extern const crc_params_t CRC_24_INTERLAKEN;
extern const crc_params_t CRC_24_LTE_A;
extern const crc_params_t CRC_24_LTE_B;
extern const crc_params_t CRC_24_OPENPGP;
extern const crc_params_t CRC_24_OS_9;
extern const crc_params_t CRC_30_CDMA;
extern const crc_params_t CRC_31_PHILIPS;
extern const crc_params_t CRC_32_AIXM;
extern const crc_params_t CRC_32_AUTOSAR;
extern const crc_params_t CRC_32_BASE91_D;
extern const crc_params_t CRC_32_BZIP2;
extern const crc_params_t CRC_32_CD_ROM_EDC;
extern const crc_params_t CRC_32_CKSUM;
extern const crc_params_t CRC_32_ISCSI;
extern const crc_params_t CRC_32_ISO_HDLC;
extern const crc_params_t CRC_32_JAMCRC;
extern const crc_params_t CRC_32_MEF;
extern const crc_params_t CRC_32_MPEG_2;
extern const crc_params_t CRC_32_XFER;
extern const crc_params_t CRC_40_GSM;
extern const crc_params_t CRC_64_ECMA_182;
extern const crc_params_t CRC_64_GO_ISO;
extern const crc_params_t CRC_64_MS;
extern const crc_params_t CRC_64_NVME;
extern const crc_params_t CRC_64_REDIS;
extern const crc_params_t CRC_64_WE;
extern const crc_params_t CRC_64_XZ;

#define MAKE_CRC_FUNC(fname, params) \
    static inline uint64_t fname(const uint8_t *data, size_t len) { \
        return crc_compute(&(params), data, len); \
    }

MAKE_CRC_FUNC(crc3_gsm,           CRC_3_GSM)
MAKE_CRC_FUNC(crc3_rohc,          CRC_3_ROHC)
MAKE_CRC_FUNC(crc4_g704,          CRC_4_G704)
MAKE_CRC_FUNC(crc4_interlaken,    CRC_4_INTERLAKEN)
MAKE_CRC_FUNC(crc5_epc,           CRC_5_EPC_C1G2)
MAKE_CRC_FUNC(crc5_g704,          CRC_5_G704)
MAKE_CRC_FUNC(crc5_usb,           CRC_5_USB)
MAKE_CRC_FUNC(crc6_cdma2000a,     CRC_6_CDMA2000_A)
MAKE_CRC_FUNC(crc6_cdma2000b,     CRC_6_CDMA2000_B)
MAKE_CRC_FUNC(crc6_darc,          CRC_6_DARC)
MAKE_CRC_FUNC(crc6_g704,          CRC_6_G704)
MAKE_CRC_FUNC(crc6_gsm,           CRC_6_GSM)
MAKE_CRC_FUNC(crc7_mmc,           CRC_7_MMC)
MAKE_CRC_FUNC(crc7_rohc,          CRC_7_ROHC)
MAKE_CRC_FUNC(crc7_umts,          CRC_7_UMTS)
MAKE_CRC_FUNC(crc8_autosar,       CRC_8_AUTOSAR)
MAKE_CRC_FUNC(crc8_bluetooth,     CRC_8_BLUETOOTH)
MAKE_CRC_FUNC(crc8_cdma2000,      CRC_8_CDMA2000)
MAKE_CRC_FUNC(crc8_darc,          CRC_8_DARC)
MAKE_CRC_FUNC(crc8_dvb_s2,        CRC_8_DVB_S2)
MAKE_CRC_FUNC(crc8_gsm_a,         CRC_8_GSM_A)
MAKE_CRC_FUNC(crc8_gsm_b,         CRC_8_GSM_B)
MAKE_CRC_FUNC(crc8_hitag,         CRC_8_HITAG)
MAKE_CRC_FUNC(crc8_i_432_1,       CRC_8_I_432_1)
MAKE_CRC_FUNC(crc8_i_code,        CRC_8_I_CODE)
MAKE_CRC_FUNC(crc8_lte,           CRC_8_LTE)
MAKE_CRC_FUNC(crc8_maxim_dow,     CRC_8_MAXIM_DOW)
MAKE_CRC_FUNC(crc8_mifare_mad,    CRC_8_MIFARE_MAD)
MAKE_CRC_FUNC(crc8_nrsc_5,        CRC_8_NRSC_5)
MAKE_CRC_FUNC(crc8_opensafety,    CRC_8_OPENSAFETY)
MAKE_CRC_FUNC(crc8_rohc,          CRC_8_ROHC)
MAKE_CRC_FUNC(crc8_sae_j1850,     CRC_8_SAE_J1850)
MAKE_CRC_FUNC(crc8_smbus,         CRC_8_SMBUS)
MAKE_CRC_FUNC(crc8_tech_3250,     CRC_8_TECH_3250)
MAKE_CRC_FUNC(crc8_wcdma,         CRC_8_WCDMA)
MAKE_CRC_FUNC(crc10_atm,          CRC_10_ATM)
MAKE_CRC_FUNC(crc10_cdma2000,     CRC_10_CDMA2000)
MAKE_CRC_FUNC(crc10_gsm,          CRC_10_GSM)
MAKE_CRC_FUNC(crc11_flexray,      CRC_11_FLEXRAY)
MAKE_CRC_FUNC(crc11_umts,         CRC_11_UMTS)
MAKE_CRC_FUNC(crc12_3gpp,         CRC_12_3GPP)
MAKE_CRC_FUNC(crc12_dect,         CRC_12_DECT)
MAKE_CRC_FUNC(crc12_gsm,          CRC_12_GSM)
MAKE_CRC_FUNC(crc12_umts,         CRC_12_UMTS)
MAKE_CRC_FUNC(crc13_bbc,          CRC_13_BBC)
MAKE_CRC_FUNC(crc14_darc,         CRC_14_DARC)
MAKE_CRC_FUNC(crc14_gsm,          CRC_14_GSM)
MAKE_CRC_FUNC(crc15_can,          CRC_15_CAN)
MAKE_CRC_FUNC(crc15_mpt1327,      CRC_15_MPT1327)
MAKE_CRC_FUNC(crc16_arc,          CRC_16_ARC)
MAKE_CRC_FUNC(crc16_cdma2000,     CRC_16_CDMA2000)
MAKE_CRC_FUNC(crc16_cms,          CRC_16_CMS)
MAKE_CRC_FUNC(crc16_dds_110,      CRC_16_DDS_110)
MAKE_CRC_FUNC(crc16_dect_r,       CRC_16_DECT_R)
MAKE_CRC_FUNC(crc16_dect_x,       CRC_16_DECT_X)
MAKE_CRC_FUNC(crc16_dnp,          CRC_16_DNP)
MAKE_CRC_FUNC(crc16_en_13757,     CRC_16_EN_13757)
MAKE_CRC_FUNC(crc16_genibus,      CRC_16_GENIBUS)
MAKE_CRC_FUNC(crc16_gsm,          CRC_16_GSM)
MAKE_CRC_FUNC(crc16_ibm_3740,     CRC_16_IBM_3740)
MAKE_CRC_FUNC(crc16_ibm_sdlc,     CRC_16_IBM_SDLC)
MAKE_CRC_FUNC(crc16_iso_14443_3a, CRC_16_ISO_IEC_14443_3_A)
MAKE_CRC_FUNC(crc16_kermit,       CRC_16_KERMIT)
MAKE_CRC_FUNC(crc16_lj1200,       CRC_16_LJ1200)
MAKE_CRC_FUNC(crc16_m17,          CRC_16_M17)
MAKE_CRC_FUNC(crc16_maxim_dow,    CRC_16_MAXIM_DOW)
MAKE_CRC_FUNC(crc16_mcrf4xx,      CRC_16_MCRF4XX)
MAKE_CRC_FUNC(crc16_modbus,       CRC_16_MODBUS)
MAKE_CRC_FUNC(crc16_nrsc_5,       CRC_16_NRSC_5)
MAKE_CRC_FUNC(crc16_opensafety_a, CRC_16_OPENSAFETY_A)
MAKE_CRC_FUNC(crc16_opensafety_b, CRC_16_OPENSAFETY_B)
MAKE_CRC_FUNC(crc16_profibus,     CRC_16_PROFIBUS)
MAKE_CRC_FUNC(crc16_riello,       CRC_16_RIELLO)
MAKE_CRC_FUNC(crc16_spi_fujitsu,  CRC_16_SPI_FUJITSU)
MAKE_CRC_FUNC(crc16_t10_dif,      CRC_16_T10_DIF)
MAKE_CRC_FUNC(crc16_teledisk,     CRC_16_TELEDISK)
MAKE_CRC_FUNC(crc16_tms37157,     CRC_16_TMS37157)
MAKE_CRC_FUNC(crc16_umts,         CRC_16_UMTS)
MAKE_CRC_FUNC(crc16_usb,          CRC_16_USB)
MAKE_CRC_FUNC(crc16_xmodem,       CRC_16_XMODEM)
MAKE_CRC_FUNC(crc17_can_fd,       CRC_17_CAN_FD)
MAKE_CRC_FUNC(crc21_can_fd,       CRC_21_CAN_FD)
MAKE_CRC_FUNC(crc24_ble,          CRC_24_BLE)
MAKE_CRC_FUNC(crc24_flexray_a,    CRC_24_FLEXRAY_A)
MAKE_CRC_FUNC(crc24_flexray_b,    CRC_24_FLEXRAY_B)
MAKE_CRC_FUNC(crc24_interlaken,   CRC_24_INTERLAKEN)
MAKE_CRC_FUNC(crc24_lte_a,        CRC_24_LTE_A)
MAKE_CRC_FUNC(crc24_lte_b,        CRC_24_LTE_B)
MAKE_CRC_FUNC(crc24_openpgp,      CRC_24_OPENPGP)
MAKE_CRC_FUNC(crc24_os_9,         CRC_24_OS_9)
MAKE_CRC_FUNC(crc30_cdma,         CRC_30_CDMA)
MAKE_CRC_FUNC(crc31_philips,      CRC_31_PHILIPS)
MAKE_CRC_FUNC(crc32_aixm,         CRC_32_AIXM)
MAKE_CRC_FUNC(crc32_autosar,      CRC_32_AUTOSAR)
MAKE_CRC_FUNC(crc32_base91_d,     CRC_32_BASE91_D)
MAKE_CRC_FUNC(crc32_bzip2,        CRC_32_BZIP2)
MAKE_CRC_FUNC(crc32_cd_rom_edc,   CRC_32_CD_ROM_EDC)
MAKE_CRC_FUNC(crc32_cksum,        CRC_32_CKSUM)
MAKE_CRC_FUNC(crc32_iscsi,        CRC_32_ISCSI)
MAKE_CRC_FUNC(crc32_iso_hdlc,     CRC_32_ISO_HDLC)
MAKE_CRC_FUNC(crc32_jamcrc,       CRC_32_JAMCRC)
MAKE_CRC_FUNC(crc32_mef,          CRC_32_MEF)
MAKE_CRC_FUNC(crc32_mpeg_2,       CRC_32_MPEG_2)
MAKE_CRC_FUNC(crc32_xfer,         CRC_32_XFER)
MAKE_CRC_FUNC(crc40_gsm,          CRC_40_GSM)
MAKE_CRC_FUNC(crc64_ecma_182,     CRC_64_ECMA_182)
MAKE_CRC_FUNC(crc64_go_iso,       CRC_64_GO_ISO)
MAKE_CRC_FUNC(crc64_ms,           CRC_64_MS)
MAKE_CRC_FUNC(crc64_nvme,         CRC_64_NVME)
MAKE_CRC_FUNC(crc64_redis,        CRC_64_REDIS)
MAKE_CRC_FUNC(crc64_we,           CRC_64_WE)
MAKE_CRC_FUNC(crc64_xz,           CRC_64_XZ)

#endif /* CRC_H */
