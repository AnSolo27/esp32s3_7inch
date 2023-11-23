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
#include "custom.h"


void setup_scr_screen_main(lv_ui *ui)
{
	//Write codes screen_main
	ui->screen_main = lv_obj_create(NULL);
	lv_obj_set_size(ui->screen_main, 800, 480);

	//Write style for screen_main, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
	lv_obj_set_style_bg_opa(ui->screen_main, 242, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_bg_color(ui->screen_main, lv_color_hex(0x2F92DA), LV_PART_MAIN|LV_STATE_DEFAULT);

	//Write codes screen_main_ddlist_1
	ui->screen_main_ddlist_1 = lv_dropdown_create(ui->screen_main);
	lv_dropdown_set_options(ui->screen_main_ddlist_1, "list1\nlist2\nlist3");
	lv_obj_set_pos(ui->screen_main_ddlist_1, 147, 103);
	lv_obj_set_size(ui->screen_main_ddlist_1, 130, 30);

	//Write style for screen_main_ddlist_1, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
	lv_obj_set_style_text_color(ui->screen_main_ddlist_1, lv_color_hex(0x0D3055), LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_font(ui->screen_main_ddlist_1, &lv_font_montserratMedium_12, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_border_width(ui->screen_main_ddlist_1, 1, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_border_opa(ui->screen_main_ddlist_1, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_border_color(ui->screen_main_ddlist_1, lv_color_hex(0xe1e6ee), LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_border_side(ui->screen_main_ddlist_1, LV_BORDER_SIDE_FULL, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_pad_top(ui->screen_main_ddlist_1, 8, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_pad_left(ui->screen_main_ddlist_1, 6, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_pad_right(ui->screen_main_ddlist_1, 6, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_radius(ui->screen_main_ddlist_1, 3, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_bg_opa(ui->screen_main_ddlist_1, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_bg_color(ui->screen_main_ddlist_1, lv_color_hex(0xffffff), LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_shadow_width(ui->screen_main_ddlist_1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

	//Write style state: LV_STATE_CHECKED for &style_screen_main_ddlist_1_extra_list_selected_checked
	static lv_style_t style_screen_main_ddlist_1_extra_list_selected_checked;
	ui_init_style(&style_screen_main_ddlist_1_extra_list_selected_checked);
	
	lv_style_set_text_color(&style_screen_main_ddlist_1_extra_list_selected_checked, lv_color_hex(0xffffff));
	lv_style_set_text_font(&style_screen_main_ddlist_1_extra_list_selected_checked, &lv_font_montserratMedium_12);
	lv_style_set_border_width(&style_screen_main_ddlist_1_extra_list_selected_checked, 1);
	lv_style_set_border_opa(&style_screen_main_ddlist_1_extra_list_selected_checked, 255);
	lv_style_set_border_color(&style_screen_main_ddlist_1_extra_list_selected_checked, lv_color_hex(0xe1e6ee));
	lv_style_set_border_side(&style_screen_main_ddlist_1_extra_list_selected_checked, LV_BORDER_SIDE_FULL);
	lv_style_set_radius(&style_screen_main_ddlist_1_extra_list_selected_checked, 3);
	lv_style_set_bg_opa(&style_screen_main_ddlist_1_extra_list_selected_checked, 255);
	lv_style_set_bg_color(&style_screen_main_ddlist_1_extra_list_selected_checked, lv_color_hex(0x00a1b5));
	lv_obj_add_style(lv_dropdown_get_list(ui->screen_main_ddlist_1), &style_screen_main_ddlist_1_extra_list_selected_checked, LV_PART_SELECTED|LV_STATE_CHECKED);

	//Write style state: LV_STATE_DEFAULT for &style_screen_main_ddlist_1_extra_list_main_default
	static lv_style_t style_screen_main_ddlist_1_extra_list_main_default;
	ui_init_style(&style_screen_main_ddlist_1_extra_list_main_default);
	
	lv_style_set_max_height(&style_screen_main_ddlist_1_extra_list_main_default, 90);
	lv_style_set_text_color(&style_screen_main_ddlist_1_extra_list_main_default, lv_color_hex(0x0D3055));
	lv_style_set_text_font(&style_screen_main_ddlist_1_extra_list_main_default, &lv_font_montserratMedium_12);
	lv_style_set_border_width(&style_screen_main_ddlist_1_extra_list_main_default, 1);
	lv_style_set_border_opa(&style_screen_main_ddlist_1_extra_list_main_default, 255);
	lv_style_set_border_color(&style_screen_main_ddlist_1_extra_list_main_default, lv_color_hex(0xe1e6ee));
	lv_style_set_border_side(&style_screen_main_ddlist_1_extra_list_main_default, LV_BORDER_SIDE_FULL);
	lv_style_set_radius(&style_screen_main_ddlist_1_extra_list_main_default, 3);
	lv_style_set_bg_opa(&style_screen_main_ddlist_1_extra_list_main_default, 255);
	lv_style_set_bg_color(&style_screen_main_ddlist_1_extra_list_main_default, lv_color_hex(0xffffff));
	lv_obj_add_style(lv_dropdown_get_list(ui->screen_main_ddlist_1), &style_screen_main_ddlist_1_extra_list_main_default, LV_PART_MAIN|LV_STATE_DEFAULT);

	//Write style state: LV_STATE_DEFAULT for &style_screen_main_ddlist_1_extra_list_scrollbar_default
	static lv_style_t style_screen_main_ddlist_1_extra_list_scrollbar_default;
	ui_init_style(&style_screen_main_ddlist_1_extra_list_scrollbar_default);
	
	lv_style_set_radius(&style_screen_main_ddlist_1_extra_list_scrollbar_default, 3);
	lv_style_set_bg_opa(&style_screen_main_ddlist_1_extra_list_scrollbar_default, 255);
	lv_style_set_bg_color(&style_screen_main_ddlist_1_extra_list_scrollbar_default, lv_color_hex(0x00ff00));
	lv_obj_add_style(lv_dropdown_get_list(ui->screen_main_ddlist_1), &style_screen_main_ddlist_1_extra_list_scrollbar_default, LV_PART_SCROLLBAR|LV_STATE_DEFAULT);

	//Write codes screen_main_qrcode_1
	ui->screen_main_qrcode_1 = lv_qrcode_create(ui->screen_main, 100, lv_color_hex(0x2C3224), lv_color_hex(0xffffff));
	const char * screen_main_qrcode_1_data = "https://www.nxp.com/";
	lv_qrcode_update(ui->screen_main_qrcode_1, screen_main_qrcode_1_data, strlen(screen_main_qrcode_1_data));
	lv_obj_set_pos(ui->screen_main_qrcode_1, 616, 46);
	lv_obj_set_size(ui->screen_main_qrcode_1, 100, 100);

	//Write codes screen_main_menu_1
	ui->screen_main_menu_1 = lv_menu_create(ui->screen_main);

	//Create sidebar page for menu screen_main_menu_1
	ui->screen_main_menu_1_sidebar_page = lv_menu_page_create(ui->screen_main_menu_1, "menu");
	lv_menu_set_sidebar_page(ui->screen_main_menu_1, ui->screen_main_menu_1_sidebar_page);

	//Create subpage for screen_main_menu_1
	ui->screen_main_menu_1_subpage_1 = lv_menu_page_create(ui->screen_main_menu_1, NULL);
	ui->screen_main_menu_1_cont_1 = lv_menu_cont_create(ui->screen_main_menu_1_sidebar_page);
	ui->screen_main_menu_1_label_1 = lv_label_create(ui->screen_main_menu_1_cont_1);
	lv_label_set_text(ui->screen_main_menu_1_label_1, "item_1");
	lv_obj_set_size(ui->screen_main_menu_1_label_1, LV_PCT(100), LV_SIZE_CONTENT);
	lv_menu_set_load_page_event(ui->screen_main_menu_1, ui->screen_main_menu_1_cont_1, ui->screen_main_menu_1_subpage_1);

	//Create subpage for screen_main_menu_1
	ui->screen_main_menu_1_subpage_2 = lv_menu_page_create(ui->screen_main_menu_1, NULL);
	ui->screen_main_menu_1_cont_2 = lv_menu_cont_create(ui->screen_main_menu_1_sidebar_page);
	ui->screen_main_menu_1_label_2 = lv_label_create(ui->screen_main_menu_1_cont_2);
	lv_label_set_text(ui->screen_main_menu_1_label_2, "item_2");
	lv_obj_set_size(ui->screen_main_menu_1_label_2, LV_PCT(100), LV_SIZE_CONTENT);
	lv_menu_set_load_page_event(ui->screen_main_menu_1, ui->screen_main_menu_1_cont_2, ui->screen_main_menu_1_subpage_2);

	//Create subpage for screen_main_menu_1
	ui->screen_main_menu_1_subpage_3 = lv_menu_page_create(ui->screen_main_menu_1, NULL);
	ui->screen_main_menu_1_cont_3 = lv_menu_cont_create(ui->screen_main_menu_1_sidebar_page);
	ui->screen_main_menu_1_label_3 = lv_label_create(ui->screen_main_menu_1_cont_3);
	lv_label_set_text(ui->screen_main_menu_1_label_3, "item_3");
	lv_obj_set_size(ui->screen_main_menu_1_label_3, LV_PCT(100), LV_SIZE_CONTENT);
	lv_menu_set_load_page_event(ui->screen_main_menu_1, ui->screen_main_menu_1_cont_3, ui->screen_main_menu_1_subpage_3);
	lv_obj_set_pos(ui->screen_main_menu_1, 53, 163);
	lv_obj_set_size(ui->screen_main_menu_1, 280, 210);
	lv_obj_set_scrollbar_mode(ui->screen_main_menu_1, LV_SCROLLBAR_MODE_OFF);

	//Write style for screen_main_menu_1, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
	lv_obj_set_style_bg_opa(ui->screen_main_menu_1, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_bg_color(ui->screen_main_menu_1, lv_color_hex(0xffffff), LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_radius(ui->screen_main_menu_1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_shadow_width(ui->screen_main_menu_1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

	//Write style state: LV_STATE_DEFAULT for &style_screen_main_menu_1_extra_sidebar_page_main_default
	static lv_style_t style_screen_main_menu_1_extra_sidebar_page_main_default;
	ui_init_style(&style_screen_main_menu_1_extra_sidebar_page_main_default);
	
	lv_style_set_bg_opa(&style_screen_main_menu_1_extra_sidebar_page_main_default, 255);
	lv_style_set_bg_color(&style_screen_main_menu_1_extra_sidebar_page_main_default, lv_color_hex(0xdaf2f8));
	lv_style_set_radius(&style_screen_main_menu_1_extra_sidebar_page_main_default, 0);
	lv_obj_add_style(ui->screen_main_menu_1_sidebar_page, &style_screen_main_menu_1_extra_sidebar_page_main_default, LV_PART_MAIN|LV_STATE_DEFAULT);

	//Write style state: LV_STATE_DEFAULT for &style_screen_main_menu_1_extra_option_btns_main_default
	static lv_style_t style_screen_main_menu_1_extra_option_btns_main_default;
	ui_init_style(&style_screen_main_menu_1_extra_option_btns_main_default);
	
	lv_style_set_text_color(&style_screen_main_menu_1_extra_option_btns_main_default, lv_color_hex(0x151212));
	lv_style_set_text_font(&style_screen_main_menu_1_extra_option_btns_main_default, &lv_font_montserratMedium_12);
	lv_style_set_text_align(&style_screen_main_menu_1_extra_option_btns_main_default, LV_TEXT_ALIGN_CENTER);
	lv_style_set_pad_top(&style_screen_main_menu_1_extra_option_btns_main_default, 10);
	lv_style_set_pad_bottom(&style_screen_main_menu_1_extra_option_btns_main_default, 10);
	lv_obj_add_style(ui->screen_main_menu_1_cont_3, &style_screen_main_menu_1_extra_option_btns_main_default, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_add_style(ui->screen_main_menu_1_cont_2, &style_screen_main_menu_1_extra_option_btns_main_default, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_add_style(ui->screen_main_menu_1_cont_1, &style_screen_main_menu_1_extra_option_btns_main_default, LV_PART_MAIN|LV_STATE_DEFAULT);

	//Write style state: LV_STATE_CHECKED for &style_screen_main_menu_1_extra_option_btns_main_checked
	static lv_style_t style_screen_main_menu_1_extra_option_btns_main_checked;
	ui_init_style(&style_screen_main_menu_1_extra_option_btns_main_checked);
	
	lv_style_set_text_color(&style_screen_main_menu_1_extra_option_btns_main_checked, lv_color_hex(0x9ab700));
	lv_style_set_text_font(&style_screen_main_menu_1_extra_option_btns_main_checked, &lv_font_montserratMedium_12);
	lv_style_set_text_align(&style_screen_main_menu_1_extra_option_btns_main_checked, LV_TEXT_ALIGN_CENTER);
	lv_style_set_border_width(&style_screen_main_menu_1_extra_option_btns_main_checked, 0);
	lv_style_set_radius(&style_screen_main_menu_1_extra_option_btns_main_checked, 0);
	lv_style_set_bg_opa(&style_screen_main_menu_1_extra_option_btns_main_checked, 60);
	lv_style_set_bg_color(&style_screen_main_menu_1_extra_option_btns_main_checked, lv_color_hex(0x00e0b8));
	lv_obj_add_style(ui->screen_main_menu_1_cont_3, &style_screen_main_menu_1_extra_option_btns_main_checked, LV_PART_MAIN|LV_STATE_CHECKED);
	lv_obj_add_style(ui->screen_main_menu_1_cont_2, &style_screen_main_menu_1_extra_option_btns_main_checked, LV_PART_MAIN|LV_STATE_CHECKED);
	lv_obj_add_style(ui->screen_main_menu_1_cont_1, &style_screen_main_menu_1_extra_option_btns_main_checked, LV_PART_MAIN|LV_STATE_CHECKED);

	//Write style state: LV_STATE_DEFAULT for &style_screen_main_menu_1_extra_main_title_main_default
	static lv_style_t style_screen_main_menu_1_extra_main_title_main_default;
	ui_init_style(&style_screen_main_menu_1_extra_main_title_main_default);
	
	lv_style_set_text_color(&style_screen_main_menu_1_extra_main_title_main_default, lv_color_hex(0x41485a));
	lv_style_set_text_font(&style_screen_main_menu_1_extra_main_title_main_default, &lv_font_montserratMedium_12);
	lv_style_set_text_align(&style_screen_main_menu_1_extra_main_title_main_default, LV_TEXT_ALIGN_CENTER);
	lv_style_set_bg_opa(&style_screen_main_menu_1_extra_main_title_main_default, 255);
	lv_style_set_bg_color(&style_screen_main_menu_1_extra_main_title_main_default, lv_color_hex(0xffffff));
	lv_style_set_pad_top(&style_screen_main_menu_1_extra_main_title_main_default, 0);
	lv_style_set_pad_bottom(&style_screen_main_menu_1_extra_main_title_main_default, 0);
	lv_menu_t * screen_main_menu_1_menu= (lv_menu_t *)ui->screen_main_menu_1;
	lv_obj_t * screen_main_menu_1_title = screen_main_menu_1_menu->sidebar_header_title;
	lv_obj_set_size(screen_main_menu_1_title, LV_PCT(100), LV_SIZE_CONTENT);
	lv_obj_add_style(lv_menu_get_sidebar_header(ui->screen_main_menu_1), &style_screen_main_menu_1_extra_main_title_main_default, LV_PART_MAIN|LV_STATE_DEFAULT);







	//Update current screen layout.
	lv_obj_update_layout(ui->screen_main);

	
}
