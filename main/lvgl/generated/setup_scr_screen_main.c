/*
* Copyright 2023 NXP
* NXP Confidential and Proprietary. This software is owned or controlled by NXP and may only be used strictly in
* accordance with the applicable license terms. By expressly accepting such terms or by downloading, installing,
* activating and/or otherwise using the software, you are agreeing that you have read, and that you agree to
* comply with and are bound by, such license terms.  If you do not agree to be bound by the applicable license
* terms, then you may not retain, install, activate or otherwise use the software.
*/

#include "lvgl.h"
#include <stdio.h>
#include "gui_guider.h"
#include "events_init.h"
#include "widgets_init.h"
#include "../custom/custom.h"


void setup_scr_screen_main(lv_ui *ui)
{
	//Write codes screen_main
	ui->screen_main = lv_obj_create(NULL);
	lv_obj_set_size(ui->screen_main, 800, 480);

	//Write style for screen_main, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
	lv_obj_set_style_bg_opa(ui->screen_main, 242, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_bg_color(ui->screen_main, lv_color_hex(0x2F92DA), LV_PART_MAIN|LV_STATE_DEFAULT);

	//Write codes screen_main_table_1
	ui->screen_main_table_1 = lv_table_create(ui->screen_main);
	lv_table_set_col_cnt(ui->screen_main_table_1,2);
	lv_table_set_row_cnt(ui->screen_main_table_1,9);
	lv_table_set_cell_value(ui->screen_main_table_1,0,0,"Name");
	lv_table_set_cell_value(ui->screen_main_table_1,1,0,"Apple");
	lv_table_set_cell_value(ui->screen_main_table_1,2,0,"Banana");
	lv_table_set_cell_value(ui->screen_main_table_1,3,0,"Citron");
	lv_table_set_cell_value(ui->screen_main_table_1,4,0,"Name");
	lv_table_set_cell_value(ui->screen_main_table_1,5,0,"Name");
	lv_table_set_cell_value(ui->screen_main_table_1,6,0,"Name");
	lv_table_set_cell_value(ui->screen_main_table_1,7,0,"Name");
	lv_table_set_cell_value(ui->screen_main_table_1,8,0,"Name");
	lv_table_set_cell_value(ui->screen_main_table_1,0,1,"RSSI");
	lv_table_set_cell_value(ui->screen_main_table_1,1,1,"$1");
	lv_table_set_cell_value(ui->screen_main_table_1,2,1,"$2");
	lv_table_set_cell_value(ui->screen_main_table_1,3,1,"$3");
	lv_table_set_cell_value(ui->screen_main_table_1,4,1,"Price");
	lv_table_set_cell_value(ui->screen_main_table_1,5,1,"Price");
	lv_table_set_cell_value(ui->screen_main_table_1,6,1,"Price");
	lv_table_set_cell_value(ui->screen_main_table_1,7,1,"Price");
	lv_table_set_cell_value(ui->screen_main_table_1,8,1,"Price");
	lv_obj_set_pos(ui->screen_main_table_1, 207, 73);
	lv_obj_set_scrollbar_mode(ui->screen_main_table_1, LV_SCROLLBAR_MODE_OFF);

	//Write style for screen_main_table_1, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
	lv_obj_set_style_pad_top(ui->screen_main_table_1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_pad_bottom(ui->screen_main_table_1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_pad_left(ui->screen_main_table_1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_pad_right(ui->screen_main_table_1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_bg_opa(ui->screen_main_table_1, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_bg_color(ui->screen_main_table_1, lv_color_hex(0xffffff), LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_border_width(ui->screen_main_table_1, 2, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_border_opa(ui->screen_main_table_1, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_border_color(ui->screen_main_table_1, lv_color_hex(0xd5dee6), LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_border_side(ui->screen_main_table_1, LV_BORDER_SIDE_FULL, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_radius(ui->screen_main_table_1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_shadow_width(ui->screen_main_table_1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

	//Write style for screen_main_table_1, Part: LV_PART_ITEMS, State: LV_STATE_DEFAULT.
	lv_obj_set_style_text_color(ui->screen_main_table_1, lv_color_hex(0x393c41), LV_PART_ITEMS|LV_STATE_DEFAULT);
	lv_obj_set_style_text_font(ui->screen_main_table_1, &lv_font_montserratMedium_12, LV_PART_ITEMS|LV_STATE_DEFAULT);
	lv_obj_set_style_text_align(ui->screen_main_table_1, LV_TEXT_ALIGN_CENTER, LV_PART_ITEMS|LV_STATE_DEFAULT);
	lv_obj_set_style_bg_opa(ui->screen_main_table_1, 0, LV_PART_ITEMS|LV_STATE_DEFAULT);
	lv_obj_set_style_border_width(ui->screen_main_table_1, 3, LV_PART_ITEMS|LV_STATE_DEFAULT);
	lv_obj_set_style_border_opa(ui->screen_main_table_1, 255, LV_PART_ITEMS|LV_STATE_DEFAULT);
	lv_obj_set_style_border_color(ui->screen_main_table_1, lv_color_hex(0xd5dee6), LV_PART_ITEMS|LV_STATE_DEFAULT);
	lv_obj_set_style_border_side(ui->screen_main_table_1, LV_BORDER_SIDE_FULL, LV_PART_ITEMS|LV_STATE_DEFAULT);
	lv_obj_set_style_pad_top(ui->screen_main_table_1, 10, LV_PART_ITEMS|LV_STATE_DEFAULT);
	lv_obj_set_style_pad_bottom(ui->screen_main_table_1, 10, LV_PART_ITEMS|LV_STATE_DEFAULT);
	lv_obj_set_style_pad_left(ui->screen_main_table_1, 10, LV_PART_ITEMS|LV_STATE_DEFAULT);
	lv_obj_set_style_pad_right(ui->screen_main_table_1, 10, LV_PART_ITEMS|LV_STATE_DEFAULT);

	//Update current screen layout.
	lv_obj_update_layout(ui->screen_main);

	
}
