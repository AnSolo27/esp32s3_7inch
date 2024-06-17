/*
 * SPDX-FileCopyrightText: 2022 Espressif Systems (Shanghai) CO LTD
 *
 * SPDX-License-Identifier: CC0-1.0
 */

#include <stdio.h>
#include "sdkconfig.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "freertos/semphr.h"

#include "esp_timer.h"

#include "driver/gpio.h"
#include "esp_err.h"
#include "esp_log.h"
#include "lvgl.h"
//#include "lvgl/generated/gui_guider.h"
//#include "lvgl/generated/events_init.h"

#include "display.h"

#include "lwip/err.h"
#include "lwip/sys.h"

#include "esp_event.h"
#include "esp_system.h"

#include "wifi_sta.h"
#include "ble_task.h"
#include "sdcard_task.h"

#include "ble_pult_task.h"

static const char* TAG = "main";

void Draw_Task(void* arg);

#include "nvs_flash.h"

#include "driver/uart.h"

#include "lvgl/src/ui/ui.h"

/*
GPIO

//10 sd
//11 sd
//12 sd
//13 sd

//17 out
//18 out

//19 touch - max98 conflict
//20 touch
//38 touch

*/

//lv_ui guider_ui;

void WIFI_Task(void* arg);

TaskHandle_t hBLE_Task = NULL;
TaskHandle_t hWIFI_Task = NULL;
TaskHandle_t hSDCARD_Task = NULL;
TaskHandle_t hDraw_Task = NULL;

#define TXD_PIN (GPIO_NUM_17)
#define RXD_PIN (GPIO_NUM_18)

static const int RX_BUF_SIZE = 1024;

/*
115200 - 5*200us
921600 - 1.5*200us
*/

void init(void) {
    const uart_config_t uart_config = {
        .baud_rate = 921600,
        .data_bits = UART_DATA_8_BITS,
        .parity = UART_PARITY_DISABLE,
        .stop_bits = UART_STOP_BITS_1,
        .flow_ctrl = UART_HW_FLOWCTRL_DISABLE,
        .source_clk = UART_SCLK_DEFAULT,
    };
    // We won't use a buffer for sending data.
    uart_driver_install(UART_NUM_1, RX_BUF_SIZE * 2, 0, 0, NULL, 0);
    uart_param_config(UART_NUM_1, &uart_config);
    uart_set_pin(
        UART_NUM_1, TXD_PIN, RXD_PIN, UART_PIN_NO_CHANGE, UART_PIN_NO_CHANGE);
}

int sendData(const char* logName, const char* data) {
    const int len = strlen(data);
    const int txBytes = uart_write_bytes(UART_NUM_1, data, len);
    ESP_LOGI(logName, "Wrote %d bytes", txBytes);
    return txBytes;
}

void action_test(lv_event_t* e) {
    ESP_LOGI(TAG, "action");
}

void app_main(void) {
    //ESP_ERROR_CHECK(esp_netif_init());
    //ESP_ERROR_CHECK(esp_event_loop_create_default());
    wifi_init_sta();

    ble_pult_task_create(4096, 12);

    display_init();
    ui_init();

    int rc;
    /* Initialize NVS — it is used to store PHY calibration data */
    esp_err_t ret;

    xTaskCreatePinnedToCore(
        Draw_Task, "Draw_Task", 4096, NULL, 11, &hDraw_Task, 1);
    //xTaskCreatePinnedToCore(WIFI_Task, "WIFI_Task", 4096, NULL, 10, &hWIFI_Task, 0);
    //xTaskCreatePinnedToCore(SDCARD_Task, "SDCARD_Task", 4096, NULL, 10, &hSDCARD_Task, 0);
    size_t free_heap = 0;

    init();
    while(1) {
        /*
        uint32_t event_cnt =
            lv_obj_get_event_count(guider_ui.screen_main_spinbox_1);
        for(int i = 0; i < event_cnt; i++) {
            lv_event_dsc_t* event_dsc =
                lv_obj_get_event_dsc(guider_ui.screen_main_spinbox_1, i);
        }
        */
        vTaskDelay(pdMS_TO_TICKS(5000));
        free_heap = xPortGetFreeHeapSize();
        //ESP_LOGI(TAG, "rtos free heap %u", free_heap);
        //sendData(TAG, "Hello world");
    }
}

void Draw_Task(void* arg) {
    while(1) {
        // raise the task priority of LVGL and/or reduce the handler period can improve the performance
        vTaskDelay(pdMS_TO_TICKS(4));
        // The task running lv_timer_handler should have lower priority than that running `lv_tick_inc`
        lv_timer_handler();
    }
}
