/**********Includes**********/
#include "gui_task.h"

#include "esp_system.h"
#include "esp_ota_ops.h"
#include "esp_partition.h"
#include "esp_log.h"
#include "esp_http_client.h"
#include "esp_wifi.h"
#include "esp_mac.h"

#include <string.h>

#include "freertos/FreeRTOS.h"
#include "freertos/ringbuf.h"

#include "config.h"
#include "settings.h"

#include "driver/gpio.h"
#include "driver/uart.h"

#include "lvgl.h"
#include "lvgl/src/ui/ui.h"
#include "lvgl/src/ui/vars.h"

#include "mcu_uart_task.h"

/**********Extern**********/

/**********LOG**********/

static const char* TAG = "GUI_TASK";

/**********Functions declaration**********/
static void gui_task(void* arg);

/**********Task**********/
TaskHandle_t gui_task_h;
QueueHandle_t gui_task_q;

/**********Settings**********/

/**********Vars**********/

/**********Functions definition**********/
void gui_task_create(uint32_t stack_size, uint32_t prio) {
    xTaskCreate(&gui_task, "gui_task", stack_size, NULL, prio, &gui_task_h);
}

void action_btn_stop_ev(lv_event_t* e) {
    ESP_LOGI(TAG, "action_btn_stop_ev");
}

void action_btn_run_ev(lv_event_t* e) {
    ESP_LOGI(TAG, "action_btn_run_ev");
    loadScreen(SCREEN_ID_PAGE_PROCESS);
}

void action_event_btn_process_scr(lv_event_t* e) {
    lv_obj_t* obj = lv_event_get_target(e);
    if(obj == objects.btn_process_stop) {
        loadScreen(SCREEN_ID_MAIN);
    }
}

void action_event_meter_main_bot(lv_event_t* e) {
    lv_obj_draw_part_dsc_t* dsc =
        (lv_obj_draw_part_dsc_t*)lv_event_get_param(e);
    double value;

    if(dsc->text != NULL) { // Filter major ticks...
        value = dsc->value / 10.0f;
        sprintf(dsc->text, "%5.1f", value);
    }
}

int32_t meter_cnt = 0;
int32_t temp_second_target_32 = 0;
char temp_second_target[32];

typedef struct sensor_val {
    char text[32];
    float val;
} sensor_val_t;

sensor_val_t temp_top;
sensor_val_t temp_bot;

sensor_val_t p_top;
sensor_val_t p_bot;

//LV_EVENT_DRAW_PART_BEGIN

void sensor_update_val(sensor_val_t* sens) {
    sprintf(sens->text, "%.1f", sens->val);
}

void action_event_btn_main_scr(lv_event_t* e) {
    lv_obj_t* obj = lv_event_get_target(e);
    if(obj == objects.btn_main_run) {
        loadScreen(SCREEN_ID_PAGE_PROCESS);
    } else if(obj == objects.btn_p_top_inc) {
        ESP_LOGI(TAG, "btn_p_top_inc");
        mcu_uart_btn_pressed(0, 3);
    } else if(obj == objects.btn_p_top_dec) {
        ESP_LOGI(TAG, "btn_p_top_dec");
        mcu_uart_btn_pressed(0, 2);
    } else if(obj == objects.btn_p_bot_inc) {
        ESP_LOGI(TAG, "btn_p_bot_inc");
        mcu_uart_btn_pressed(0, 1);
    } else if(obj == objects.btn_p_bot_dec) {
        ESP_LOGI(TAG, "btn_p_bot_dec");
        mcu_uart_btn_pressed(0, 0);
    } else if(obj == objects.btn_t_top_inc) {
        ESP_LOGI(TAG, "btn_t_top_inc");
        temp_top.val++;
        sensor_update_val(&temp_top);
    } else if(obj == objects.btn_t_top_dec) {
        ESP_LOGI(TAG, "btn_t_top_dec");
        temp_top.val--;
        sensor_update_val(&temp_top);
    } else if(obj == objects.btn_t_bot_inc) {
        ESP_LOGI(TAG, "btn_t_bot_inc");
        temp_bot.val++;
        sensor_update_val(&temp_bot);
    } else if(obj == objects.btn_t_bot_dec) {
        ESP_LOGI(TAG, "btn_t_bot_dec");
        temp_bot.val--;
        sensor_update_val(&temp_bot);
    }
}

void set_var_meter_cnt(int32_t value) {
    meter_cnt = value;
}

int32_t get_var_meter_cnt() {
    return meter_cnt;
}

const char* get_var_temp_top_target(void) {
    return temp_top.text;
}

const char* get_var_temp_bot_target(void) {
    return temp_bot.text;
}

float get_var_p_top_meter(void) {
    return p_top.val;
}

float get_var_p_bot_meter(void) {
    return p_bot.val;
}

const char* get_var_p_top_l(void) {
    return p_top.text;
}

const char* get_var_p_bot_l(void) {
    return p_bot.text;
}

void set_var_temp_second_target(const char* value) {
    //temp_second_target = value;
}

void gui_task(void* pvParameters) {
    ESP_LOGI(TAG, "created");

    temp_top.val = 100;
    temp_bot.val = 100;

    p_top.val = 0;
    p_bot.val = 0;

    sensor_update_val(&temp_top);
    sensor_update_val(&temp_bot);

    sensor_update_val(&p_top);
    sensor_update_val(&p_bot);

    for(;;) {
        tick_screen(0);
        vTaskDelay(pdMS_TO_TICKS(500));
    }
}
