#ifndef GUI_TASK_H
#define GUI_TASK_H

#include <stdint.h>
#include <stddef.h>

#ifdef __cplusplus
extern "C" {
#endif

enum main_screen_btn {
    BTN_P_BOT_DEC = 0,
    BTN_P_BOT_INC = 1,
    BTN_P_TOP_DEC = 2,
    BTN_P_TOP_INC = 3,
    BTN_RUN = 4,
    BTN_PROCESS_FINISH = 5,
};

void gui_task_create(uint32_t stack_size, uint32_t prio);
void p_top_set(uint8_t val);
void p_bot_set(uint8_t val);

#ifdef __cplusplus
}
#endif

#endif /* GUI_TASK_H */