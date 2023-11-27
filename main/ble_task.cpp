#include "ble_task.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "lvgl.h"
#include "lvgl/generated/gui_guider.h"

static const char *TAG = "BLE_TASK";

#include <string>
#include <vector>
#include <unordered_map>
#include <algorithm>


using namespace std;

extern lv_ui guider_ui;

string empty_str = "empty";

unordered_map<string, string> ble_devices;

void ble_add_device(char *name, int rssi) {
    char tmp[32] = {0};
    itoa(rssi, tmp, 10);
    ble_devices[name] = tmp;
}

static void event_handler(lv_event_t * e)
{
    lv_event_code_t code = lv_event_get_code(e);

    if(code == LV_EVENT_CLICKED) {
        int i = 1;
        for (auto dev : ble_devices) {
            lv_table_set_cell_value(guider_ui.screen_main_table_1, i, 0, "empty");
            lv_table_set_cell_value(guider_ui.screen_main_table_1, i, 1, "0");
            i++;
            if (i > 10) {
                break;
            }
        }
        ble_devices.clear();
    }
}

bool comp(pair<string,string> a, pair<string,string> b) {
    return atoi(a.second.c_str()) > atoi(b.second.c_str());
}


void BLE_Task(void *arg) {
    lv_obj_add_event_cb(guider_ui.screen_main_btn_1, event_handler, LV_EVENT_ALL, NULL);
    
    while (1) {
        int i = 1;
        vector<std::pair<string, string>> elems(ble_devices.begin(), ble_devices.end());
        sort(elems.begin(), elems.end(), comp);
        for (auto el : elems) {
            lv_table_set_cell_value(guider_ui.screen_main_table_1, i, 0, el.first.c_str());
            lv_table_set_cell_value(guider_ui.screen_main_table_1, i, 1, el.second.c_str());
            i++;
            if (i > 10) {
                break;
            }
        }
        if (ble_devices.size() > 0) {
            

        }

        vTaskDelay(pdMS_TO_TICKS(2000));
        /* code */
    }
    

}