
#ifndef CONFIG_H
#define CONFIG_H
/**********Includes**********/
#include "main.h"
/**********Typedef**********/

/**********Functions**********/
void device_reset(void);
uint32_t flash_read(uint32_t address);

/**********Buld_type**********/
#define BUILD_DEBUG   0
#define BUILD_RELEASE 1

#if BUILD_DEBUG == BUILD_RELEASE
#error "Choose one build!"
#endif

/**********Device type**********/
#define DEV_TYPE 0x70B0

/**********Version**********/
#define MAJOR 0
#define MINOR 0
#define PATCH 2

/**********Settings**********/

#define DEBUG_STACK_USAGE 1

#define FLASH_SECTOR_SIZE 0x400U

#define MAIN_APP_ADDR          0x08002800
#define MAIN_APP_SECTOR        MAIN_APP_ADDR
#define MAIN_APP_SECTOR_AMOUNT 57U

#define UPDATE_CANDIDATE_ADDR \
    FLASH_SECTOR_SIZE* MAIN_APP_SECTOR_AMOUNT + MAIN_APP_ADDR
#define UPDATE_CANDIDATE_SECTOR        UPDATE_CANDIDATE_ADDR
#define UPDATE_CANDIDATE_SECTOR_AMOUNT MAIN_APP_SECTOR_AMOUNT

#define UPDATE_INFO_ADDR   0x0801FC00
#define UPDATE_INFO_SECTOR UPDATE_INFO_ADDR
#define UPDATE_FLAG_VAL    0xBACE

#define SN_ADDR    0x0801F800
#define MAGIC_WORD 0xBACE

#define MAIN_SETTINGS_ADDR   0x0801F000
#define MAIN_SETTINGS_SECTOR MAIN_SETTINGS_ADDR

#define RESERVE_SETTINGS_ADDR   0x0801F400
#define RESERVE_SETTINGS_SECTOR RESERVE_SETTINGS_ADDR

/*
How to tell bootloader that fw is pending
*/
#define UPDATE_FLAG_RTC   0
#define UPDATE_FLAG_FLASH 1

#define ASP_UPDATE 0

#define ARTERY 1

/**********Device specific**********/

/**********Extern**********/

#endif /* CONFIG_H */
