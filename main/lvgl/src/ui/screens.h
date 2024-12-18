#ifndef EEZ_LVGL_UI_SCREENS_H
#define EEZ_LVGL_UI_SCREENS_H

#include <lvgl.h>

#ifdef __cplusplus
extern "C" {
#endif

typedef struct _objects_t {
    lv_obj_t *main;
    lv_obj_t *page_process;
    lv_obj_t *page_check;
    lv_obj_t *btn_check_stop;
    lv_obj_t *btn_h_dec;
    lv_obj_t *btn_h_inc;
    lv_obj_t *btn_main_check;
    lv_obj_t *btn_main_run;
    lv_obj_t *btn_p_in_dec;
    lv_obj_t *btn_p_in_inc;
    lv_obj_t *btn_p_out_dec;
    lv_obj_t *btn_p_out_inc;
    lv_obj_t *btn_process_stop;
    lv_obj_t *btn_t_in_dec;
    lv_obj_t *btn_t_in_inc;
    lv_obj_t *btn_t_out_dec;
    lv_obj_t *btn_t_out_inc;
    lv_obj_t *check_b_sensor_bot;
    lv_obj_t *check_b_sensor_top;
    lv_obj_t *l_h_check;
    lv_obj_t *l_main_time;
    lv_obj_t *l_p_in;
    lv_obj_t *l_p_out;
    lv_obj_t *l_temp_in_target;
    lv_obj_t *l_temp_out_target;
    lv_obj_t *l_time_to_finish;
    lv_obj_t *l_time_to_start_check;
    lv_obj_t *main_time_arc;
    lv_obj_t *meter_p_bot;
    lv_obj_t *meter_p_top;
    lv_obj_t *obj0;
    lv_obj_t *obj1;
    lv_obj_t *obj2;
    lv_obj_t *obj3;
    lv_obj_t *p_in_proc;
    lv_obj_t *p_out_proc;
    lv_obj_t *process_chart;
} objects_t;

extern objects_t objects;

enum ScreensEnum {
    SCREEN_ID_MAIN = 1,
    SCREEN_ID_PAGE_PROCESS = 2,
    SCREEN_ID_PAGE_CHECK = 3,
};

void create_screen_main();
void tick_screen_main();

void create_screen_page_process();
void tick_screen_page_process();

void create_screen_page_check();
void tick_screen_page_check();

void create_screens();
void tick_screen(int screen_index);


#ifdef __cplusplus
}
#endif

#endif /*EEZ_LVGL_UI_SCREENS_H*/