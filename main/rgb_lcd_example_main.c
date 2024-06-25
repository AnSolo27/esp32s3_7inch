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
#include "mcu_uart_task.h"

#include "ble_pult_task.h"
#include "gui_task.h"

static const char* TAG = "main";

void Draw_Task(void* arg);

#include "nvs_flash.h"

#include "driver/uart.h"

#include "lvgl/src/ui/ui.h"
#include "lvgl/src/ui/vars.h"

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
TaskHandle_t hMCU_UART_Task = NULL;

int sendData(const char* logName, const char* data) {
    const int len = strlen(data);
    const int txBytes = uart_write_bytes(UART_NUM_1, data, len);
    ESP_LOGI(logName, "Wrote %d bytes", txBytes);
    return txBytes;
}

void app_main(void) {
    //ESP_ERROR_CHECK(esp_netif_init());
    //ESP_ERROR_CHECK(esp_event_loop_create_default());
    wifi_init_sta();

    ble_pult_task_create(4096, configMAX_PRIORITIES - 1);

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
    int i = 0;

    uint8_t buf[32] = {0};

    mcu_uart_task_create(1024 * 4, configMAX_PRIORITIES - 1);
    gui_task_create(1024 * 4, configMAX_PRIORITIES - 1);
    while(1) {
        /*
        uint32_t event_cnt =
            lv_obj_get_event_count(guider_ui.screen_main_spinbox_1);
        for(int i = 0; i < event_cnt; i++) {
            lv_event_dsc_t* event_dsc =
                lv_obj_get_event_dsc(guider_ui.screen_main_spinbox_1, i);
        }
        */

        //tick_screen(0);

        vTaskDelay(pdMS_TO_TICKS(1000));
        free_heap = xPortGetFreeHeapSize();
        /*
        ESP_LOGI(TAG, "rtos free heap %u", free_heap);

        ESP_LOGI(
            TAG,
            "uart free heap %u",
            uxTaskGetStackHighWaterMark(hMCU_UART_Task) * sizeof(StackType_t));
            */
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
