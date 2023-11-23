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
    lv_chart_series_t * screen_chart_1_0 = lv_chart_add_series(guider_ui.screen_chart_1, lv_color_hex(0x000000), LV_CHART_AXIS_PRIMARY_Y);
	lv_obj_set_pos(guider_ui.screen_chart_1, 152, 250);
	lv_obj_set_size(guider_ui.screen_chart_1, 205, 155);
	lv_obj_set_scrollbar_mode(guider_ui.screen_chart_1, LV_SCROLLBAR_MODE_OFF);

    lv_chart_series_t * screen_chart_2_0 = lv_chart_add_series(guider_ui.screen_chart_2, lv_color_hex(0x000000), LV_CHART_AXIS_PRIMARY_Y);
	lv_obj_set_pos(guider_ui.screen_chart_2, 515, 261);
	lv_obj_set_size(guider_ui.screen_chart_2, 205, 155);
	lv_obj_set_scrollbar_mode(guider_ui.screen_chart_2, LV_SCROLLBAR_MODE_OFF);

    int chart_1 = 0;
    int chart_2 = 100;
    while(1){
        ESP_LOGI(TAG, "Demo Task");
        chart_1++;
        chart_2--;
        if (chart_2 == 0) {
            chart_2 = 100;
        }
        if (chart_1 > 100) {
            chart_1 = 0;
        }
        
        lv_chart_set_next_value(guider_ui.screen_chart_1, screen_chart_1_0, chart_1);

        lv_chart_set_next_value(guider_ui.screen_chart_2, screen_chart_2_0, chart_2);

        lv_meter_set_indicator_value(guider_ui.screen_meter_1, guider_ui.screen_meter_1_scale_1_ndline_0, chart_1);

        lv_chart_refresh(guider_ui.screen_chart_1);
        lv_chart_refresh(guider_ui.screen_chart_2);
        vTaskDelay(pdMS_TO_TICKS(100));
    }
}
