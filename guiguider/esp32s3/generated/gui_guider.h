/*
* Copyright 2023 NXP
* NXP Confidential and Proprietary. This software is owned or controlled by NXP and may only be used strictly in
* accordance with the applicable license terms. By expressly accepting such terms or by downloading, installing,
* activating and/or otherwise using the software, you are agreeing that you have read, and that you agree to
* comply with and are bound by, such license terms.  If you do not agree to be bound by the applicable license
* terms, then you may not retain, install, activate or otherwise use the software.
*/

#ifndef GUI_GUIDER_H
#define GUI_GUIDER_H
#ifdef __cplusplus
extern "C" {
#endif

#include "lvgl.h"

typedef struct
{
  
	lv_obj_t *screen_main;
	bool screen_main_del;
	lv_obj_t *screen_main_ddlist_1;
	lv_obj_t *screen_main_qrcode_1;
	lv_obj_t *screen_main_menu_1;
	lv_obj_t *screen_main_menu_1_sidebar_page;
	lv_obj_t *screen_main_menu_1_subpage_1;
	lv_obj_t *screen_main_menu_1_cont_1;
	lv_obj_t *screen_main_menu_1_label_1;
	lv_obj_t *screen_main_menu_1_subpage_2;
	lv_obj_t *screen_main_menu_1_cont_2;
	lv_obj_t *screen_main_menu_1_label_2;
	lv_obj_t *screen_main_menu_1_subpage_3;
	lv_obj_t *screen_main_menu_1_cont_3;
	lv_obj_t *screen_main_menu_1_label_3;
	lv_obj_t *screen_1;
	bool screen_1_del;
}lv_ui;

void ui_init_style(lv_style_t * style);
void init_scr_del_flag(lv_ui *ui);
void setup_ui(lv_ui *ui);
extern lv_ui guider_ui;

void setup_scr_screen_main(lv_ui *ui);
void setup_scr_screen_1(lv_ui *ui);

LV_FONT_DECLARE(lv_font_montserratMedium_12)


#ifdef __cplusplus
}
#endif
#endif
