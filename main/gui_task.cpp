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
        if(new_val > max_val) {
            val = max_val;
        } else {
            val = new_val;
        }

        sprintf(text, "%ld", val);
    }
    const char* get_text(void) {
        return text;
    }

    int32_t get_val(void) {
        return val;
    }

    void set_max_val(int32_t _max_val) {
        max_val = _max_val;
    }

private:
    char text[32];
    int32_t val = 0;
    int32_t max_val = INT32_MAX;
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
    uint8_t is_long_press = 0;
    if(e->code == LV_EVENT_LONG_PRESSED) {
        is_long_press = 1;
    }

    if(obj == objects.btn_process_stop) {
        //loadScreen(SCREEN_ID_MAIN);
        mcu_uart_btn_pressed(0, BTN_PROCESS_FINISH, is_long_press);
    } else if(obj == objects.page_process) {
        ESP_LOGI(TAG, "Process loaded");
        mcu_uart_process_settings(
            0,
            T_Top_target.get_val(),
            T_Bot_target.get_val(),
            lv_arc_get_value(objects.main_time_arc) * 2);

        lv_label_set_text_fmt(
            objects.l_time_to_finish,
            "%u мин",
            lv_arc_get_value(objects.main_time_arc) * 2);
    }
}

void action_event_btn_main_scr(lv_event_t* e) {
    lv_obj_t* obj = lv_event_get_target(e);
    uint8_t is_long_press = 0;
    if(e->code == LV_EVENT_LONG_PRESSED) {
        is_long_press = 1;
    }
    if(obj == objects.btn_main_run) {
        mcu_uart_btn_pressed(0, BTN_RUN, is_long_press);
    } else if(obj == objects.main) {
        ESP_LOGI(TAG, "Main loaded");
    } else if(obj == objects.main_time_arc) {
        lv_label_set_text_fmt(
            objects.l_main_time,
            "%d мин",
            lv_arc_get_value(objects.main_time_arc) * 2);
    }
}

static void custom_events_cb_main_btns(lv_event_t* e) {
    lv_event_code_t event = lv_event_get_code(e);
    lv_obj_t* obj = lv_event_get_target(e);
    uint8_t is_long_press = 0;
    if(e->code == LV_EVENT_LONG_PRESSED) {
        is_long_press = 1;
    } else if(e->code == LV_EVENT_SHORT_CLICKED) {
        is_long_press = 0;
    } else {
        return;
    }
    if(obj == objects.btn_p_out_inc) {
        ESP_LOGI(TAG, "btn_p_top_inc %u", e->code);
        mcu_uart_btn_pressed(0, BTN_P_TOP_INC, is_long_press);

    } else if(obj == objects.btn_p_out_dec) {
        ESP_LOGI(TAG, "btn_p_top_dec");
        mcu_uart_btn_pressed(0, BTN_P_TOP_DEC, is_long_press);
    } else if(obj == objects.btn_p_in_inc) {
        ESP_LOGI(TAG, "btn_p_bot_inc");
        mcu_uart_btn_pressed(0, BTN_P_BOT_INC, is_long_press);
    } else if(obj == objects.btn_p_in_dec) {
        ESP_LOGI(TAG, "btn_p_bot_dec");
        mcu_uart_btn_pressed(0, BTN_P_BOT_DEC, is_long_press);
    }
}

static void custom_events_cb_main_t_btns(lv_event_t* e) {
    lv_event_code_t event = lv_event_get_code(e);
    lv_obj_t* obj = lv_event_get_target(e);
    uint8_t is_long_press = 0;
    if(e->code == LV_EVENT_LONG_PRESSED) {
        is_long_press = 1;
    } else if(e->code == LV_EVENT_SHORT_CLICKED) {
        is_long_press = 0;
    } else if(e->code == LV_EVENT_LONG_PRESSED_REPEAT) {
        is_long_press = 0;
    } else {
        return;
    }
    if(obj == objects.btn_t_out_inc) {
        ESP_LOGI(TAG, "btn_t_top_inc");
        T_Top_target.set(T_Top_target.get_val() + 1);
        lv_label_set_text_fmt(
            objects.l_temp_out_target, "%ld", T_Top_target.get_val());
    } else if(obj == objects.btn_t_out_dec) {
        ESP_LOGI(TAG, "btn_t_top_dec");
        T_Top_target.set(T_Top_target.get_val() - 1);
        lv_label_set_text_fmt(
            objects.l_temp_out_target, "%ld", T_Top_target.get_val());
    } else if(obj == objects.btn_t_in_inc) {
        ESP_LOGI(TAG, "btn_t_bot_inc");
        T_Bot_target.set(T_Bot_target.get_val() + 1);
        lv_label_set_text_fmt(
            objects.l_temp_in_target, "%ld", T_Bot_target.get_val());
    } else if(obj == objects.btn_t_in_dec) {
        ESP_LOGI(TAG, "btn_t_bot_dec");
        T_Bot_target.set(T_Bot_target.get_val() - 1);
        lv_label_set_text_fmt(
            objects.l_temp_in_target, "%ld", T_Bot_target.get_val());
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

extern uint16_t time_to_finish;

const char* get_var_time_to_finish(void) {
    return "01:40:00";
}

void set_var_temp_second_target(const char* value) {
    //temp_second_target = value;
}

void p_top_set(uint8_t val) {
    P_Top.set(val);
    lv_label_set_text_fmt(objects.l_p_out, "%s", P_Top.get_text());
}

void p_bot_set(uint8_t val) {
    P_Bot.set(val);
    lv_label_set_text_fmt(objects.l_p_in, "%s", P_Bot.get_text());
}

extern uint16_t temp_top;
extern uint16_t temp_bot;

void gui_task(void* pvParameters) {
    ESP_LOGI(TAG, "created");

    T_Top_target.set(100);
    T_Bot_target.set(100);

    T_Top_target.set_max_val(150);
    T_Bot_target.set_max_val(150);

    P_Top.set(0);
    P_Bot.set(0);

    lv_chart_set_range(objects.process_chart, LV_CHART_AXIS_PRIMARY_Y, 0, 160);

    lv_chart_set_axis_tick(
        objects.process_chart, LV_CHART_AXIS_PRIMARY_Y, 10, 5, 5, 5, true, 40);

    static lv_chart_series_t* ser_top;
    ser_top = lv_chart_add_series(
        objects.process_chart,
        lv_palette_main(LV_PALETTE_RED),
        LV_CHART_AXIS_PRIMARY_Y);

    static lv_chart_series_t* ser_bot;
    ser_bot = lv_chart_add_series(
        objects.process_chart,
        lv_palette_main(LV_PALETTE_YELLOW),
        LV_CHART_AXIS_PRIMARY_Y);

    int cnt = 0;
    lv_arc_set_value(objects.main_time_arc, 50);
    lv_label_set_text_fmt(
        objects.l_main_time,
        "%d мин",
        lv_arc_get_value(objects.main_time_arc) * 2);

    //btns
    lv_obj_add_event_cb(
        objects.btn_p_out_inc, custom_events_cb_main_btns, LV_EVENT_ALL, 0);
    lv_obj_add_event_cb(
        objects.btn_p_out_dec, custom_events_cb_main_btns, LV_EVENT_ALL, 0);
    lv_obj_add_event_cb(
        objects.btn_p_in_inc, custom_events_cb_main_btns, LV_EVENT_ALL, 0);
    lv_obj_add_event_cb(
        objects.btn_p_in_dec, custom_events_cb_main_btns, LV_EVENT_ALL, 0);

    //
    lv_obj_add_event_cb(
        objects.btn_t_out_inc, custom_events_cb_main_t_btns, LV_EVENT_ALL, 0);
    lv_obj_add_event_cb(
        objects.btn_t_out_dec, custom_events_cb_main_t_btns, LV_EVENT_ALL, 0);
    lv_obj_add_event_cb(
        objects.btn_t_in_inc, custom_events_cb_main_t_btns, LV_EVENT_ALL, 0);
    lv_obj_add_event_cb(
        objects.btn_t_in_dec, custom_events_cb_main_t_btns, LV_EVENT_ALL, 0);

    for(;;) {
        tick_screen(0);
        vTaskDelay(pdMS_TO_TICKS(500));
        tick_screen(1);
        vTaskDelay(pdMS_TO_TICKS(500));
        if(cnt > 3) {
            cnt = 0;
            lv_chart_set_next_value(
                objects.process_chart, ser_top, temp_top / 10);
            lv_chart_set_next_value(
                objects.process_chart, ser_bot, temp_bot / 10);
        }
        cnt++;
    }
}
