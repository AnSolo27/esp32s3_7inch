#ifndef SDCARD_TASK_H
#define SDCARD_TASK_H

#ifdef __cplusplus
extern "C" {
#endif

#define PIN_NUM_MISO  13
#define PIN_NUM_MOSI  11
#define PIN_NUM_CLK   12
#define PIN_NUM_CS    10

#define EXAMPLE_MAX_CHAR_SIZE    64

#define MOUNT_POINT "/sdcard"

void SDCARD_Task(void *arg);


#ifdef __cplusplus
}
#endif

#endif /* SDCARD_TASK_H */