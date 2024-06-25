#ifndef MCU_UART_TASK_H
#define MCU_UART_TASK_H

#include <stdint.h>
#include <stddef.h>

#ifdef __cplusplus
extern "C" {
#endif

void mcu_uart_task_create(uint32_t stack_size, uint32_t prio);
void mcu_uart_btn_pressed(uint8_t screen, uint8_t btn);

#ifdef __cplusplus
}
#endif

#endif /* MCU_UART_TASK_H */