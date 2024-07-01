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
    FLOW_GLOBAL_VARIABLE_TEMP_TOP_TARGET = 1,
    FLOW_GLOBAL_VARIABLE_TEMP_BOT_TARGET = 2,
    FLOW_GLOBAL_VARIABLE_P_TOP_L = 3,
    FLOW_GLOBAL_VARIABLE_P_BOT_L = 4,
    FLOW_GLOBAL_VARIABLE_P_TOP_METER = 5,
    FLOW_GLOBAL_VARIABLE_P_BOT_METER = 6,
    FLOW_GLOBAL_VARIABLE_TIME_TO_FINISH = 7
};

// Native global variables

extern int32_t get_var_meter_cnt();
extern void set_var_meter_cnt(int32_t value);
extern const char *get_var_temp_top_target();
extern void set_var_temp_top_target(const char *value);
extern const char *get_var_temp_bot_target();
extern void set_var_temp_bot_target(const char *value);
extern const char *get_var_p_top_l();
extern void set_var_p_top_l(const char *value);
extern const char *get_var_p_bot_l();
extern void set_var_p_bot_l(const char *value);
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