#ifndef EEZ_LVGL_UI_VARS_H
#define EEZ_LVGL_UI_VARS_H

#include <stdint.h>
#include <stdbool.h>

#ifdef __cplusplus
extern "C" {
#endif

// enum declarations



// Flow global variables

enum FlowGlobalVariables {
    FLOW_GLOBAL_VARIABLE_METER_CNT = 0,
    FLOW_GLOBAL_VARIABLE_P_TOP_METER = 1,
    FLOW_GLOBAL_VARIABLE_P_BOT_METER = 2,
    FLOW_GLOBAL_VARIABLE_TIME_TO_FINISH = 3
};

// Native global variables

extern int32_t get_var_meter_cnt();
extern void set_var_meter_cnt(int32_t value);
extern float get_var_p_top_meter();
extern void set_var_p_top_meter(float value);
extern float get_var_p_bot_meter();
extern void set_var_p_bot_meter(float value);
extern const char *get_var_time_to_finish();
extern void set_var_time_to_finish(const char *value);


#ifdef __cplusplus
}
#endif

#endif /*EEZ_LVGL_UI_VARS_H*/