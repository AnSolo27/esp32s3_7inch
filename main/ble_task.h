#ifndef BLE_TASK_H
#define BLE_TASK_H

#ifdef __cplusplus
extern "C" {
#endif

void ble_add_device(char *name, int rssi);
void BLE_Task(void *arg);


#ifdef __cplusplus
}
#endif

#endif /* BLE_TASK_H */