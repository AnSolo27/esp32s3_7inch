#include "ble_task.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "lvgl.h"
#include "lvgl/generated/gui_guider.h"

static const char *TAG = "BLE_TASK";

#include <string>
#include <vector>
#include <unordered_map>


using namespace std;

extern lv_ui guider_ui;

unordered_map<string, string> ble_devices;

void ble_add_device(char *name, int rssi) {
    char tmp[32] = {0};
    itoa(rssi, tmp, 10);
    ble_devices[name] = tmp;
}


void BLE_Task(void *arg) {
    
    while (1) {
        int i = 1;
        for (auto dev : ble_devices) {
            lv_table_set_cell_value(guider_ui.screen_main_table_1, i, 0, dev.first.c_str());
            lv_table_set_cell_value(guider_ui.screen_main_table_1, i, 1, dev.second.c_str());
            i++;
        }
        if (ble_devices.size() > 0) {
            

        }

        vTaskDelay(pdMS_TO_TICKS(1000));
        /* code */
    }
    

}