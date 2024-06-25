#ifndef GUI_TASK_H
#define GUI_TASK_H

#include <stdint.h>
#include <stddef.h>

#ifdef __cplusplus
extern "C" {
#endif

void gui_task_create(uint32_t stack_size, uint32_t prio);

#ifdef __cplusplus
}
#endif

#endif /* GUI_TASK_H */