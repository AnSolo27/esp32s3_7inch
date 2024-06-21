#ifndef TOUCH_G911_H
#define TOUCH_G911_H

#ifdef __cplusplus
extern "C" {
#endif

/******Include******/
#include "esp_system.h"
#include "driver/gpio.h"
#include "driver/i2c.h"

#include "lvgl.h";
/******Functions******/
void touch_G911_init(lv_disp_t *disp);

/******Settings******/
/* I2C */
#define BSP_I2C_SCL           (GPIO_NUM_20)
#define BSP_I2C_SDA           (GPIO_NUM_19)
#define BSP_RST               (GPIO_NUM_38)

#define BSP_I2C_NUM             0
#define BSP_I2C_CLK_SPEED_HZ    400000


#ifdef __cplusplus
}
#endif

#endif /* TOUCH_G911_H */