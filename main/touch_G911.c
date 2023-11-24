/******Include******/
#include "touch_G911.h"

#include "esp_lvgl_port.h"
#include "bsp_err_check.h"
#include "esp_lcd_touch_gt911.h"
#include "display.h"

#ifdef __cplusplus
extern "C" {
#endif

#ifdef __cplusplus
}
#endif

/******LOG******/
static const char *TAG = "touch_G911";



static esp_err_t bsp_i2c_init(void);
static lv_indev_t *bsp_display_indev_init(lv_disp_t *disp);
/******Funcs******/

void touch_G911_init(lv_disp_t *disp) {
    bsp_i2c_init();
    bsp_display_indev_init(disp);

}

esp_err_t bsp_i2c_init(void)
{
    const i2c_config_t i2c_conf = {
        .mode = I2C_MODE_MASTER,
        .sda_io_num = BSP_I2C_SDA,
        .sda_pullup_en = GPIO_PULLUP_ENABLE,
        .scl_io_num = BSP_I2C_SCL,
        .scl_pullup_en = GPIO_PULLUP_ENABLE,
        .master.clk_speed = BSP_I2C_CLK_SPEED_HZ
    };
    BSP_ERROR_CHECK_RETURN_ERR(i2c_param_config(BSP_I2C_NUM, &i2c_conf));
    BSP_ERROR_CHECK_RETURN_ERR(i2c_driver_install(BSP_I2C_NUM, i2c_conf.mode, 0, 0, 0));

    return ESP_OK;
}

static lv_indev_t *bsp_display_indev_init(lv_disp_t *disp)
{
    esp_lcd_touch_handle_t tp;

    /* Initialize touch */
    const esp_lcd_touch_config_t tp_cfg = {
        .x_max = EXAMPLE_LCD_H_RES,
        .y_max = EXAMPLE_LCD_V_RES,
        .rst_gpio_num = BSP_RST, // Shared with LCD reset
        .int_gpio_num = GPIO_NUM_NC,
        .levels = {
            .reset = 0,
            .interrupt = 0,
        },
        .flags = {
            .swap_xy = 0,
            .mirror_x = 0,
            .mirror_y = 0,
        },
    };
    esp_lcd_panel_io_handle_t tp_io_handle = NULL;
    const esp_lcd_panel_io_i2c_config_t tp_io_config = ESP_LCD_TOUCH_IO_I2C_GT911_CONFIG();
    BSP_ERROR_CHECK_RETURN_NULL(esp_lcd_new_panel_io_i2c((esp_lcd_i2c_bus_handle_t)BSP_I2C_NUM, &tp_io_config, &tp_io_handle));
    BSP_ERROR_CHECK_RETURN_NULL(esp_lcd_touch_new_i2c_gt911(tp_io_handle, &tp_cfg, &tp));
    assert(tp);

    /* Add touch input (for selected screen) */
    const lvgl_port_touch_cfg_t touch_cfg = {
        .disp = disp,
        .handle = tp,
    };

    return lvgl_port_add_touch(&touch_cfg);
}

