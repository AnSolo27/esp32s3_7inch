#ifndef MCU_UART_TASK_H
#define MCU_UART_TASK_H

#include <stdint.h>
#include <stddef.h>

#ifdef __cplusplus
extern "C" {
#endif

void mcu_uart_task_create(uint32_t stack_size, uint32_t prio);
void mcu_uart_btn_pressed(uint8_t screen, uint8_t btn, uint8_t event_type);
void mcu_uart_process_settings(
    uint8_t type,
    uint8_t top_t,
    uint8_t bot_t,
    uint8_t time);
void mcu_uart_check_start(uint8_t time_h);
#ifdef __cplusplus
}
#endif

#endif /* MCU_UART_TASK_H */