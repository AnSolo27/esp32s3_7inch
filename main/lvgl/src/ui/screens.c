#include "screens.h"
#include "images.h"
#include "fonts.h"
#include "actions.h"
#include "vars.h"
#include "styles.h"
#include "ui.h"

objects_t objects;
lv_obj_t* tick_value_change_obj;

static void event_handler_cb_main_main(lv_event_t* e) {
    lv_event_code_t event = lv_event_get_code(e);
    if(event == LV_EVENT_SCREEN_LOADED) {
        action_event_btn_main_scr(e);
    }
}

static void event_handler_cb_main_btn_p_out_inc(lv_event_t* e) {
    lv_event_code_t event = lv_event_get_code(e);
    if(event == LV_EVENT_PRESSED) {
        action_event_btn_main_scr(e);
    }
}

static void event_handler_cb_main_btn_main_run(lv_event_t* e) {
    lv_event_code_t event = lv_event_get_code(e);
    if(event == LV_EVENT_RELEASED) {
        action_event_btn_main_scr(e);
    }
}

static void event_handler_cb_main_obj0(lv_event_t* e) {
    lv_event_code_t event = lv_event_get_code(e);
    if(event == LV_EVENT_PRESSED) {
        action_event_btn_main_scr(e);
    }
}

static void event_handler_cb_main_meter_p_bot(lv_event_t* e) {
    lv_event_code_t event = lv_event_get_code(e);
    if(event == LV_EVENT_DRAW_PART_BEGIN) {
        action_event_meter_main_bot(e);
    }
}

static void event_handler_cb_main_meter_p_top(lv_event_t* e) {
    lv_event_code_t event = lv_event_get_code(e);
    if(event == LV_EVENT_DRAW_PART_BEGIN) {
        action_event_meter_main_bot(e);
    }
}

static void event_handler_cb_main_main_time_arc(lv_event_t* e) {
    lv_event_code_t event = lv_event_get_code(e);
    if(event == LV_EVENT_VALUE_CHANGED) {
        action_event_btn_main_scr(e);
    }
}

static void event_handler_cb_page_process_page_process(lv_event_t* e) {
    lv_event_code_t event = lv_event_get_code(e);
    if(event == LV_EVENT_SCREEN_LOADED) {
        action_event_btn_process_scr(e);
    }
}

static void event_handler_cb_page_process_btn_process_stop(lv_event_t* e) {
    lv_event_code_t event = lv_event_get_code(e);
    if(event == LV_EVENT_RELEASED) {
        action_event_btn_process_scr(e);
    }
}

static void event_handler_cb_page_process_obj1(lv_event_t* e) {
    lv_event_code_t event = lv_event_get_code(e);
    if(event == LV_EVENT_PRESSED) {
        action_event_btn_process_scr(e);
    }
}

void create_screen_main() {
    lv_obj_t* obj = lv_obj_create(0);
    objects.main = obj;
    lv_obj_set_pos(obj, 0, 0);
    lv_obj_set_size(obj, 800, 480);
    lv_obj_add_event_cb(obj, event_handler_cb_main_main, LV_EVENT_ALL, 0);
    lv_obj_clear_flag(obj, LV_OBJ_FLAG_SCROLLABLE);
    {
        lv_obj_t* parent_obj = obj;
        {
            // l_p_out
            lv_obj_t* obj = lv_label_create(parent_obj);
            objects.l_p_out = obj;
            lv_obj_set_pos(obj, 105, 277);
            lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
            lv_label_set_text(obj, "0.0");
            lv_obj_set_style_text_font(
                obj, &ui_font_gost_32, LV_PART_MAIN | LV_STATE_DEFAULT);
        }
        {
            // l_p_in
            lv_obj_t* obj = lv_label_create(parent_obj);
            objects.l_p_in = obj;
            lv_obj_set_pos(obj, 643, 256);
            lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
            lv_label_set_text(obj, "0.0");
            lv_obj_set_style_text_font(
                obj, &ui_font_gost_32, LV_PART_MAIN | LV_STATE_DEFAULT);
        }
        {
            // btn_p_out_inc
            lv_obj_t* obj = lv_imgbtn_create(parent_obj);
            objects.btn_p_out_inc = obj;
            lv_obj_set_pos(obj, 159, 276);
            lv_obj_set_size(obj, LV_SIZE_CONTENT, 40);
            lv_imgbtn_set_src(
                obj, LV_IMGBTN_STATE_RELEASED, NULL, &img_plus, NULL);
            lv_imgbtn_set_src(
                obj, LV_IMGBTN_STATE_PRESSED, NULL, &img_plus_pressed, NULL);
            lv_obj_add_event_cb(
                obj, event_handler_cb_main_btn_p_out_inc, LV_EVENT_ALL, 0);
        }
        {
            // btn_p_in_inc
            lv_obj_t* obj = lv_imgbtn_create(parent_obj);
            objects.btn_p_in_inc = obj;
            lv_obj_set_pos(obj, 699, 255);
            lv_obj_set_size(obj, LV_SIZE_CONTENT, 40);
            lv_imgbtn_set_src(
                obj, LV_IMGBTN_STATE_RELEASED, NULL, &img_plus, NULL);
            lv_imgbtn_set_src(
                obj, LV_IMGBTN_STATE_PRESSED, NULL, &img_plus_pressed, NULL);
        }
        {
            // btn_p_out_dec
            lv_obj_t* obj = lv_imgbtn_create(parent_obj);
            objects.btn_p_out_dec = obj;
            lv_obj_set_pos(obj, 41, 277);
            lv_obj_set_size(obj, LV_SIZE_CONTENT, 40);
            lv_imgbtn_set_src(
                obj, LV_IMGBTN_STATE_RELEASED, NULL, &img_minus, NULL);
            lv_imgbtn_set_src(
                obj, LV_IMGBTN_STATE_PRESSED, NULL, &img_minus_pressed, NULL);
        }
        {
            // btn_p_in_dec
            lv_obj_t* obj = lv_imgbtn_create(parent_obj);
            objects.btn_p_in_dec = obj;
            lv_obj_set_pos(obj, 582, 255);
            lv_obj_set_size(obj, LV_SIZE_CONTENT, 40);
            lv_imgbtn_set_src(
                obj, LV_IMGBTN_STATE_RELEASED, NULL, &img_minus, NULL);
            lv_imgbtn_set_src(
                obj, LV_IMGBTN_STATE_PRESSED, NULL, &img_minus_pressed, NULL);
        }
        {
            lv_obj_t* obj = lv_img_create(parent_obj);
            lv_obj_set_pos(obj, 80, 338);
            lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
            lv_img_set_src(obj, &img_temp);
            lv_obj_add_flag(obj, LV_OBJ_FLAG_ADV_HITTEST);
            lv_obj_clear_flag(obj, LV_OBJ_FLAG_SCROLLABLE);
        }
        {
            lv_obj_t* obj = lv_img_create(parent_obj);
            lv_obj_set_pos(obj, 631, 338);
            lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
            lv_img_set_src(obj, &img_temp);
            lv_obj_add_flag(obj, LV_OBJ_FLAG_ADV_HITTEST);
            lv_obj_clear_flag(obj, LV_OBJ_FLAG_SCROLLABLE);
        }
        {
            // l_temp_out_target
            lv_obj_t* obj = lv_label_create(parent_obj);
            objects.l_temp_out_target = obj;
            lv_obj_set_pos(obj, 93, 431);
            lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
            lv_label_set_text(obj, "100");
            lv_obj_set_style_text_font(
                obj, &ui_font_gost_32, LV_PART_MAIN | LV_STATE_DEFAULT);
        }
        {
            // l_temp_in_target
            lv_obj_t* obj = lv_label_create(parent_obj);
            objects.l_temp_in_target = obj;
            lv_obj_set_pos(obj, 644, 431);
            lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
            lv_label_set_text(obj, "100");
            lv_obj_set_style_text_font(
                obj, &ui_font_gost_32, LV_PART_MAIN | LV_STATE_DEFAULT);
        }
        {
            // btn_t_out_inc
            lv_obj_t* obj = lv_imgbtn_create(parent_obj);
            objects.btn_t_out_inc = obj;
            lv_obj_set_pos(obj, 154, 426);
            lv_obj_set_size(obj, LV_SIZE_CONTENT, 40);
            lv_imgbtn_set_src(
                obj, LV_IMGBTN_STATE_RELEASED, NULL, &img_plus, NULL);
            lv_imgbtn_set_src(
                obj, LV_IMGBTN_STATE_PRESSED, NULL, &img_plus_pressed, NULL);
        }
        {
            // btn_t_in_inc
            lv_obj_t* obj = lv_imgbtn_create(parent_obj);
            objects.btn_t_in_inc = obj;
            lv_obj_set_pos(obj, 710, 426);
            lv_obj_set_size(obj, LV_SIZE_CONTENT, 40);
            lv_imgbtn_set_src(
                obj, LV_IMGBTN_STATE_RELEASED, NULL, &img_plus, NULL);
            lv_imgbtn_set_src(
                obj, LV_IMGBTN_STATE_PRESSED, NULL, &img_plus_pressed, NULL);
        }
        {
            // btn_t_out_dec
            lv_obj_t* obj = lv_imgbtn_create(parent_obj);
            objects.btn_t_out_dec = obj;
            lv_obj_set_pos(obj, 44, 426);
            lv_obj_set_size(obj, LV_SIZE_CONTENT, 40);
            lv_imgbtn_set_src(
                obj, LV_IMGBTN_STATE_RELEASED, NULL, &img_minus, NULL);
            lv_imgbtn_set_src(
                obj, LV_IMGBTN_STATE_PRESSED, NULL, &img_minus_pressed, NULL);
        }
        {
            // btn_t_in_dec
            lv_obj_t* obj = lv_imgbtn_create(parent_obj);
            objects.btn_t_in_dec = obj;
            lv_obj_set_pos(obj, 591, 426);
            lv_obj_set_size(obj, LV_SIZE_CONTENT, 40);
            lv_imgbtn_set_src(
                obj, LV_IMGBTN_STATE_RELEASED, NULL, &img_minus, NULL);
            lv_imgbtn_set_src(
                obj, LV_IMGBTN_STATE_PRESSED, NULL, &img_minus_pressed, NULL);
        }
        {
            lv_obj_t* obj = lv_label_create(parent_obj);
            lv_obj_set_pos(obj, 310, 15);
            lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
            lv_label_set_text(obj, "Настройка");
            lv_obj_set_style_text_font(
                obj, &ui_font_gost_48, LV_PART_MAIN | LV_STATE_DEFAULT);
        }
        {
            // btn_main_run
            lv_obj_t* obj = lv_btn_create(parent_obj);
            objects.btn_main_run = obj;
            lv_obj_set_pos(obj, 339, 416);
            lv_obj_set_size(obj, 100, 50);
            lv_obj_add_event_cb(
                obj, event_handler_cb_main_btn_main_run, LV_EVENT_ALL, 0);
            lv_obj_add_flag(obj, LV_OBJ_FLAG_SCROLL_ON_FOCUS);
            lv_obj_clear_flag(obj, LV_OBJ_FLAG_SCROLLABLE);
        }
        {
            lv_obj_t* obj = lv_label_create(parent_obj);
            objects.obj0 = obj;
            lv_obj_set_pos(obj, 365, 431);
            lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
            lv_label_set_text(obj, "Запуск");
            lv_obj_add_event_cb(
                obj, event_handler_cb_main_obj0, LV_EVENT_ALL, 0);
            lv_obj_set_style_text_font(
                obj, &ui_font_gost_20, LV_PART_MAIN | LV_STATE_DEFAULT);
        }
        {
            // meter_p_bot
            lv_obj_t* obj = lv_meter_create(parent_obj);
            objects.meter_p_bot = obj;
            lv_obj_set_pos(obj, 570, 55);
            lv_obj_set_size(obj, 180, 180);
            {
                lv_meter_scale_t* scale = lv_meter_add_scale(obj);
                lv_meter_set_scale_ticks(
                    obj, scale, 41, 1, 5, lv_color_hex(0xffa0a0a0));
                lv_meter_set_scale_major_ticks(
                    obj, scale, 5, 3, 10, lv_color_hex(0xff000000), 15);
                lv_meter_set_scale_range(obj, scale, 0, 40, 300, 120);
                {
                    lv_meter_indicator_t* indicator = lv_meter_add_arc(
                        obj, scale, 1, lv_color_hex(0xffff0000), 0);
                    lv_meter_set_indicator_start_value(obj, indicator, 30);
                    lv_meter_set_indicator_end_value(obj, indicator, 40);
                }
                {
                    lv_meter_indicator_t* indicator = lv_meter_add_needle_line(
                        obj, scale, 2, lv_color_hex(0xffff0000), -35);
                }
            }
            lv_obj_add_event_cb(
                obj, event_handler_cb_main_meter_p_bot, LV_EVENT_ALL, 0);
        }
        {
            lv_obj_t* obj = lv_label_create(parent_obj);
            lv_obj_set_pos(obj, 630, 1);
            lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
            lv_label_set_text(obj, "IN");
            lv_obj_set_style_text_font(
                obj, &ui_font_gost_48, LV_PART_MAIN | LV_STATE_DEFAULT);
        }
        {
            lv_obj_t* obj = lv_label_create(parent_obj);
            lv_obj_set_pos(obj, 76, 15);
            lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
            lv_label_set_text(obj, "OUT");
            lv_obj_set_style_text_font(
                obj, &ui_font_gost_48, LV_PART_MAIN | LV_STATE_DEFAULT);
        }
        {
            // meter_p_top
            lv_obj_t* obj = lv_meter_create(parent_obj);
            objects.meter_p_top = obj;
            lv_obj_set_pos(obj, 31, 76);
            lv_obj_set_size(obj, 180, 180);
            {
                lv_meter_scale_t* scale = lv_meter_add_scale(obj);
                lv_meter_set_scale_ticks(
                    obj, scale, 41, 1, 5, lv_color_hex(0xffa0a0a0));
                lv_meter_set_scale_major_ticks(
                    obj, scale, 5, 3, 10, lv_color_hex(0xff000000), 15);
                lv_meter_set_scale_range(obj, scale, 0, 40, 300, 120);
                {
                    lv_meter_indicator_t* indicator = lv_meter_add_arc(
                        obj, scale, 1, lv_color_hex(0xffff0000), 0);
                    lv_meter_set_indicator_start_value(obj, indicator, 30);
                    lv_meter_set_indicator_end_value(obj, indicator, 40);
                }
                {
                    lv_meter_indicator_t* indicator = lv_meter_add_needle_line(
                        obj, scale, 2, lv_color_hex(0xffff0000), -35);
                }
            }
            lv_obj_add_event_cb(
                obj, event_handler_cb_main_meter_p_top, LV_EVENT_ALL, 0);
        }
        {
            // main_time_arc
            lv_obj_t* obj = lv_arc_create(parent_obj);
            objects.main_time_arc = obj;
            lv_obj_set_pos(obj, 297, 76);
            lv_obj_set_size(obj, 203, 192);
            lv_arc_set_value(obj, 25);
            lv_arc_set_bg_end_angle(obj, 60);
            lv_obj_add_event_cb(
                obj, event_handler_cb_main_main_time_arc, LV_EVENT_ALL, 0);
        }
        {
            // check_b_sensor_top
            lv_obj_t* obj = lv_checkbox_create(parent_obj);
            objects.check_b_sensor_top = obj;
            lv_obj_set_pos(obj, 288, 279);
            lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
            lv_checkbox_set_text(obj, "Датчик OUT");
            lv_obj_clear_flag(obj, LV_OBJ_FLAG_CLICKABLE);
            lv_obj_set_style_text_font(
                obj, &ui_font_gost_32, LV_PART_MAIN | LV_STATE_DEFAULT);
        }
        {
            // check_b_sensor_bot
            lv_obj_t* obj = lv_checkbox_create(parent_obj);
            objects.check_b_sensor_bot = obj;
            lv_obj_set_pos(obj, 288, 338);
            lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
            lv_checkbox_set_text(obj, "Датчик IN");
            lv_obj_clear_flag(obj, LV_OBJ_FLAG_CLICKABLE);
            lv_obj_set_style_text_font(
                obj, &ui_font_gost_32, LV_PART_MAIN | LV_STATE_DEFAULT);
        }
        {
            // l_main_time
            lv_obj_t* obj = lv_label_create(parent_obj);
            objects.l_main_time = obj;
            lv_obj_set_pos(obj, 334, 146);
            lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
            lv_label_set_text(obj, "100 мин");
            lv_obj_set_style_text_font(
                obj, &ui_font_gost_48, LV_PART_MAIN | LV_STATE_DEFAULT);
        }
    }
}

void tick_screen_main() {
    {
        lv_meter_indicator_t* indicator;

        lv_ll_t* indicators = &((lv_meter_t*)objects.meter_p_bot)->indicator_ll;
        int index = 1;
        for(indicator = _lv_ll_get_tail(indicators);
            index > 0 && indicator != NULL;
            indicator = _lv_ll_get_prev(indicators, indicator), index--);

        if(indicator) {
            int32_t new_val = get_var_p_bot_meter();
            int32_t cur_val = indicator->start_value;
            if(new_val != cur_val) {
                tick_value_change_obj = objects.meter_p_bot;
                lv_meter_set_indicator_value(
                    objects.meter_p_bot, indicator, new_val);
                tick_value_change_obj = NULL;
            }
        }
    }
    {
        lv_meter_indicator_t* indicator;

        lv_ll_t* indicators = &((lv_meter_t*)objects.meter_p_top)->indicator_ll;
        int index = 1;
        for(indicator = _lv_ll_get_tail(indicators);
            index > 0 && indicator != NULL;
            indicator = _lv_ll_get_prev(indicators, indicator), index--);

        if(indicator) {
            int32_t new_val = get_var_p_top_meter();
            int32_t cur_val = indicator->start_value;
            if(new_val != cur_val) {
                tick_value_change_obj = objects.meter_p_top;
                lv_meter_set_indicator_value(
                    objects.meter_p_top, indicator, new_val);
                tick_value_change_obj = NULL;
            }
        }
    }
}

void create_screen_page_process() {
    lv_obj_t* obj = lv_obj_create(0);
    objects.page_process = obj;
    lv_obj_set_pos(obj, 0, 0);
    lv_obj_set_size(obj, 800, 480);
    lv_obj_add_event_cb(
        obj, event_handler_cb_page_process_page_process, LV_EVENT_ALL, 0);
    lv_obj_clear_flag(obj, LV_OBJ_FLAG_SCROLLABLE);
    {
        lv_obj_t* parent_obj = obj;
        {
            lv_obj_t* obj = lv_label_create(parent_obj);
            lv_obj_set_pos(obj, 297, 10);
            lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
            lv_label_set_text(obj, "Вулканизация");
            lv_obj_set_style_text_font(
                obj, &ui_font_gost_48, LV_PART_MAIN | LV_STATE_DEFAULT);
        }
        {
            // btn_process_stop
            lv_obj_t* obj = lv_btn_create(parent_obj);
            objects.btn_process_stop = obj;
            lv_obj_set_pos(obj, 350, 414);
            lv_obj_set_size(obj, 100, 50);
            lv_obj_add_event_cb(
                obj,
                event_handler_cb_page_process_btn_process_stop,
                LV_EVENT_ALL,
                0);
            lv_obj_add_flag(obj, LV_OBJ_FLAG_SCROLL_ON_FOCUS);
            lv_obj_clear_flag(obj, LV_OBJ_FLAG_SCROLLABLE);
            lv_obj_set_style_bg_color(
                obj, lv_color_hex(0xfff32121), LV_PART_MAIN | LV_STATE_DEFAULT);
        }
        {
            lv_obj_t* obj = lv_label_create(parent_obj);
            objects.obj1 = obj;
            lv_obj_set_pos(obj, 383, 429);
            lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
            lv_label_set_text(obj, "Стоп");
            lv_obj_add_event_cb(
                obj, event_handler_cb_page_process_obj1, LV_EVENT_ALL, 0);
            lv_obj_set_style_text_font(
                obj, &ui_font_gost_20, LV_PART_MAIN | LV_STATE_DEFAULT);
        }
        {
            // vulc_meter
            lv_obj_t* obj = lv_meter_create(parent_obj);
            objects.vulc_meter = obj;
            lv_obj_set_pos(obj, 566, 82);
            lv_obj_set_size(obj, 180, 180);
            {
                lv_meter_scale_t* scale = lv_meter_add_scale(obj);
                lv_meter_set_scale_ticks(
                    obj, scale, 41, 1, 5, lv_color_hex(0xffa0a0a0));
                lv_meter_set_scale_major_ticks(
                    obj, scale, 5, 3, 10, lv_color_hex(0xff000000), 10);
                lv_meter_set_scale_range(obj, scale, 0, 160, 300, 90);
                {
                    lv_meter_indicator_t* indicator = lv_meter_add_arc(
                        obj, scale, 2, lv_color_hex(0xff000000), 0);
                    lv_meter_set_indicator_start_value(obj, indicator, 0);
                    lv_meter_set_indicator_end_value(obj, indicator, 100);
                }
                {
                    lv_meter_indicator_t* indicator = lv_meter_add_needle_line(
                        obj, scale, 3, lv_color_hex(0xffff0000), -28);
                }
            }
        }
        {
            // process_chart
            lv_obj_t* obj = lv_chart_create(parent_obj);
            objects.process_chart = obj;
            lv_obj_set_pos(obj, 52, 82);
            lv_obj_set_size(obj, 317, 269);
        }
        {
            // l_time_to_finish
            lv_obj_t* obj = lv_label_create(parent_obj);
            objects.l_time_to_finish = obj;
            lv_obj_set_pos(obj, 599, 297);
            lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
            lv_label_set_text(obj, "100 мин");
            lv_obj_set_style_text_font(
                obj, &ui_font_gost_32, LV_PART_MAIN | LV_STATE_DEFAULT);
        }
    }
}

void tick_screen_page_process() {
    {
        lv_meter_indicator_t* indicator;

        lv_ll_t* indicators = &((lv_meter_t*)objects.vulc_meter)->indicator_ll;
        int index = 1;
        for(indicator = _lv_ll_get_tail(indicators);
            index > 0 && indicator != NULL;
            indicator = _lv_ll_get_prev(indicators, indicator), index--);

        if(indicator) {
            int32_t new_val = get_var_meter_cnt();
            int32_t cur_val = indicator->start_value;
            if(new_val != cur_val) {
                tick_value_change_obj = objects.vulc_meter;
                lv_meter_set_indicator_value(
                    objects.vulc_meter, indicator, new_val);
                tick_value_change_obj = NULL;
            }
        }
    }
}

void create_screens() {
    lv_disp_t* dispp = lv_disp_get_default();
    lv_theme_t* theme = lv_theme_default_init(
        dispp,
        lv_palette_main(LV_PALETTE_BLUE),
        lv_palette_main(LV_PALETTE_RED),
        false,
        LV_FONT_DEFAULT);
    lv_disp_set_theme(dispp, theme);

    create_screen_main();
    create_screen_page_process();
}

typedef void (*tick_screen_func_t)();

tick_screen_func_t tick_screen_funcs[] = {
    tick_screen_main,
    tick_screen_page_process,
};

void tick_screen(int screen_index) {
    tick_screen_funcs[screen_index]();
}
