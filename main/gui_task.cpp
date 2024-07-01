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
#include "lvgl/src/ui/actions.h"

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

class Sensor_P {
public:
    Sensor_P(){};
    void set(uint8_t new_val) {
        val_u8 = new_val;
        val_f = val_u8 / 10.0f;
        sprintf(text, "%.1f", val_f);
    }
    const char* get_text(void) {
        return text;
    }

    float get_val_f(void) {
        return val_f;
    }

    uint8_t get_val_u8(void) {
        return val_u8;
    }

private:
    char text[32];
    uint8_t val_u8 = 0;
    float val_f = 0;
};

class Sensor_T {
public:
    Sensor_T(){};
    void set(int32_t new_val) {
        val = new_val;
        sprintf(text, "%ld", val);
    }
    const char* get_text(void) {
        return text;
    }

    int32_t get_val(void) {
        return val;
    }

private:
    char text[32];
    int32_t val = 0;
};

Sensor_T T_Top_target;
Sensor_T T_Bot_target;

Sensor_P P_Top;
Sensor_P P_Bot;

//LV_EVENT_DRAW_PART_BEGIN
//event_handler_cb_main_meter_p_bot

void sensor_update_val(sensor_val_t* sens) {
    sprintf(sens->text, "%.1f", sens->val / 10.0f);
}

void action_event_btn_process_scr(lv_event_t* e) {
    lv_obj_t* obj = lv_event_get_target(e);
    if(obj == objects.btn_process_stop) {
        //loadScreen(SCREEN_ID_MAIN);
        mcu_uart_btn_pressed(0, BTN_PROCESS_FINISH);
    }
}

void action_event_btn_main_scr(lv_event_t* e) {
    lv_obj_t* obj = lv_event_get_target(e);
    if(obj == objects.btn_main_run) {
        mcu_uart_btn_pressed(0, BTN_RUN);
    } else if(obj == objects.btn_p_top_inc) {
        ESP_LOGI(TAG, "btn_p_top_inc");
        mcu_uart_btn_pressed(0, BTN_P_TOP_INC);
    } else if(obj == objects.btn_p_top_dec) {
        ESP_LOGI(TAG, "btn_p_top_dec");
        mcu_uart_btn_pressed(0, BTN_P_TOP_DEC);
    } else if(obj == objects.btn_p_bot_inc) {
        ESP_LOGI(TAG, "btn_p_bot_inc");
        mcu_uart_btn_pressed(0, BTN_P_BOT_INC);
    } else if(obj == objects.btn_p_bot_dec) {
        ESP_LOGI(TAG, "btn_p_bot_dec");
        mcu_uart_btn_pressed(0, BTN_P_BOT_DEC);
    } else if(obj == objects.btn_t_top_inc) {
        ESP_LOGI(TAG, "btn_t_top_inc");
        T_Top_target.set(T_Top_target.get_val() + 1);
    } else if(obj == objects.btn_t_top_dec) {
        ESP_LOGI(TAG, "btn_t_top_dec");
        T_Top_target.set(T_Top_target.get_val() - 1);
    } else if(obj == objects.btn_t_bot_inc) {
        ESP_LOGI(TAG, "btn_t_bot_inc");
        T_Bot_target.set(T_Bot_target.get_val() + 1);
    } else if(obj == objects.btn_t_bot_dec) {
        ESP_LOGI(TAG, "btn_t_bot_dec");
        T_Bot_target.set(T_Bot_target.get_val() - 1);
    }
}

void set_var_meter_cnt(int32_t value) {
    meter_cnt = value;
}

int32_t get_var_meter_cnt() {
    return meter_cnt;
}

const char* get_var_temp_top_target(void) {
    return T_Top_target.get_text();
}

const char* get_var_temp_bot_target(void) {
    return T_Bot_target.get_text();
}

float get_var_p_top_meter(void) {
    return P_Top.get_val_u8();
}

float get_var_p_bot_meter(void) {
    return P_Bot.get_val_u8();
}

const char* get_var_p_top_l(void) {
    return P_Top.get_text();
}

const char* get_var_p_bot_l(void) {
    return P_Bot.get_text();
}

const char* get_var_time_to_finish(void) {
    return "01:40:00";
}

void set_var_temp_second_target(const char* value) {
    //temp_second_target = value;
}

void p_top_set(uint8_t val) {
    P_Top.set(val);
}

void p_bot_set(uint8_t val) {
    P_Bot.set(val);
}

void gui_task(void* pvParameters) {
    ESP_LOGI(TAG, "created");

    T_Top_target.set(100);
    T_Bot_target.set(100);

    P_Top.set(0);
    P_Bot.set(0);

    for(;;) {
        tick_screen(0);
        vTaskDelay(pdMS_TO_TICKS(500));
        tick_screen(1);
        vTaskDelay(pdMS_TO_TICKS(500));
    }
}
