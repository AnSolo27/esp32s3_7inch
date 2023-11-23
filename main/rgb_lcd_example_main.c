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
#include "lvgl/generated/gui_guider.h"
#include "lvgl/generated/events_init.h"

#include "display.h"

static const char *TAG = "main";

lv_ui guider_ui;

void Demo_Task(void *arg);
TaskHandle_t myTaskHandle = NULL;


void app_main(void)
{
    

    display_init(&guider_ui);


    xTaskCreate(Demo_Task, "Demo_Task", 4096, NULL, 10, &myTaskHandle);

    while (1) {
        // raise the task priority of LVGL and/or reduce the handler period can improve the performance
        vTaskDelay(pdMS_TO_TICKS(10));
        // The task running lv_timer_handler should have lower priority than that running `lv_tick_inc`
        lv_timer_handler();
    }
}

void Demo_Task(void *arg) {

    
    while(1){

        vTaskDelay(pdMS_TO_TICKS(100));
    }
}
