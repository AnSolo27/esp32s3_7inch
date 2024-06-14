#ifndef BLE_PULT_TASK_H
#define BLE_PULT_TASK_H

#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif

void ble_pult_task_create(uint32_t stack_size, uint32_t prio);
void ble_pult_bind(void);

#ifdef __cplusplus
}
#endif

#endif /* BLE_PULT_TASK_H */