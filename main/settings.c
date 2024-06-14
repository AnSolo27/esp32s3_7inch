// This is an independent project of an individual developer. Dear PVS-Studio,
// please check it.

// PVS-Studio Static Code Analyzer for C, C++, C#, and Java:
// http://www.viva64.com
/**********Includes**********/
#include "settings.h"

#include "esp_system.h"
#include "esp_log.h"

#include "esp_spiffs.h"
#include "esp_cpu.h"
#include "esp_http_client.h"
#include "esp_http_server.h"

#include "nvs_flash.h"

#include "config.h"

#include <unistd.h>
/**********Extern**********/

/**********GPIO**********/

/**********Vars**********/
static const char* TAG = "SETTINGS";

static char ssid[32] = {0};
static char password[32] = {0};
static uint8_t btn_mac[6] = {0};
static const uint8_t empty_arr[6] = {0};

/**********Functions declaration**********/

/**********Functions definition**********/

char* settings_get_ssid(void) {
    char* ret = NULL;
    if(strlen(ssid) > 0) {
        ret = ssid;
    }
    return ret;
}

char* settings_get_password(void) {
    char* ret = NULL;
    if(strlen(password) > 0) {
        ret = password;
    }
    return ret;
}

uint8_t settings_is_btn_binded(void) {
    uint8_t ret = 1;
    if(memcmp(btn_mac, empty_arr, sizeof(btn_mac)) == 0) {
        ret = 0;
    }
    return ret;
}

uint8_t* settings_get_btn_mac(void) {
    return btn_mac;
}

void save_wifi_credentials(const char* text) {
    esp_err_t err;
    esp_err_t ret;
    size_t len = 0;
    char* ptr = NULL;
    ptr = strstr(text, "SSID");
    if(ptr != NULL) {
        ESP_LOGI(TAG, "data = %s", ptr);
        ret = httpd_query_key_value(ptr, "SSID", ssid, sizeof(ssid));
        if(ret == ESP_OK) {
            ESP_LOGI(TAG, "SSID = %s len %u", ssid, strlen(ssid));
        }
        ret =
            httpd_query_key_value(ptr, "password", password, sizeof(password));
        if(ret == ESP_OK) {
            ESP_LOGI(TAG, "password = %s len %u", password, strlen(password));
        }
    }

    nvs_handle_t my_handle;
    err = nvs_open("settings", NVS_READWRITE, &my_handle);
    if(err != ESP_OK) {
        ESP_LOGI(TAG, "Error (%s) opening NVS handle!\n", esp_err_to_name(err));
    } else {
        len = strlen(ssid);
        if(len > 0) {
            nvs_set_str(my_handle, "ssid", ssid);
        }
        len = strlen(password);
        if(len > 0) {
            nvs_set_str(my_handle, "password", password);
        }

        nvs_commit(my_handle);

        // Close
        nvs_close(my_handle);
    }

    ESP_LOGI(TAG, "File written");
    esp_cpu_reset(0);
}

void settings_save_ble_btn(uint8_t* new_btn) {
    ESP_LOGI(TAG, "Save ble btn");
    esp_err_t err;
    size_t len = 0;
    nvs_handle_t my_handle;
    err = nvs_open("settings", NVS_READWRITE, &my_handle);
    if(err != ESP_OK) {
        ESP_LOGI(TAG, "Error (%s) opening NVS handle!\n", esp_err_to_name(err));
    } else {
        len = 6;

        nvs_set_blob(my_handle, "ble_btn", new_btn, len);

        nvs_commit(my_handle);

        // Close
        nvs_close(my_handle);
    }

    ESP_LOGI(TAG, "File written");
}

void settings_init(void) {
    // Initialize NVS
    esp_err_t err = nvs_flash_init();
    if(err == ESP_ERR_NVS_NO_FREE_PAGES ||
       err == ESP_ERR_NVS_NEW_VERSION_FOUND) {
        // NVS partition was truncated and needs to be erased
        // Retry nvs_flash_init
        ESP_ERROR_CHECK(nvs_flash_erase());
        err = nvs_flash_init();
    }
    ESP_ERROR_CHECK(err);

    size_t len = 0;

    ESP_LOGI(TAG, "init");
    nvs_handle_t my_handle;
    err = nvs_open("settings", NVS_READWRITE, &my_handle);
    if(err != ESP_OK) {
        ESP_LOGI(TAG, "Error (%s) opening NVS handle!", esp_err_to_name(err));
    } else {
        // Read
        ESP_LOGI(TAG, "Reading restart counter from NVS ... ");

        len = sizeof(ssid);

        err = nvs_get_str(my_handle, "ssid", ssid, &len);
        switch(err) {
        case ESP_OK:
            ESP_LOGI(TAG, "ssid = %s %u", ssid, len);
            break;
        default:
            ESP_LOGI(TAG, "Error (%s) reading!", esp_err_to_name(err));
            ESP_LOGI(TAG, "The value is not initialized yet!");
        }

        len = sizeof(password);

        err = nvs_get_str(my_handle, "password", password, &len);
        switch(err) {
        case ESP_OK:
            ESP_LOGI(TAG, "password = %s %u", password, len);
            break;
        default:
            ESP_LOGI(TAG, "Error (%s) reading!", esp_err_to_name(err));
            ESP_LOGI(TAG, "The value is not initialized yet!");
        }

        len = sizeof(btn_mac);

        err = nvs_get_blob(my_handle, "ble_btn", btn_mac, &len);
        switch(err) {
        case ESP_OK:
            ESP_LOGI(
                TAG,
                "MAC %x %x %x %x %x %x",
                btn_mac[0],
                btn_mac[1],
                btn_mac[2],
                btn_mac[3],
                btn_mac[4],
                btn_mac[5]);
            break;
        case ESP_ERR_NVS_NOT_FOUND:
            ESP_LOGI(TAG, "The value is not initialized yet!");
            break;
        default:
            ESP_LOGI(TAG, "Error (%s) reading!", esp_err_to_name(err));
        }

        // Close
        nvs_close(my_handle);
    }
}
