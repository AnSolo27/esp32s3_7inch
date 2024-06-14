#ifndef SETTINGS_H
#define SETTINGS_H
/**********Includes**********/
#include "main.h"

#ifdef __cplusplus
extern "C" {

#endif

/**********Typedef**********/

/**********Extern**********/

/**********Functions**********/
void settings_init(void);
char* settings_get_password(void);
char* settings_get_ssid(void);
void save_wifi_credentials(const char* text);
uint8_t* settings_get_btn_mac(void);
uint8_t settings_is_btn_binded(void);
void settings_save_ble_btn(uint8_t* new_btn);
/**********Settings**********/

#ifdef __cplusplus
}
#endif

#endif /* SETTINGS_H */