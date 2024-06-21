/**********Includes**********/
#include "mcu_uart_task.h"

#include "esp_system.h"
#include "esp_ota_ops.h"
#include "esp_partition.h"
#include "esp_log.h"
#include "esp_http_client.h"
#include "esp_wifi.h"
#include "esp_mac.h"

#include <string.h>

#include "freertos/FreeRTOS.h"
#include "freertos/ringbuf.h"

#include "config.h"
#include "settings.h"

#include "driver/gpio.h"
#include "driver/uart.h"

#include <string>
using namespace std;
/**********Extern**********/

/**********LOG**********/

static const char* TAG = "MCU_UART_TASK";

/**********Functions declaration**********/
static void mcu_uart_task(void* arg);

/**********Task**********/
TaskHandle_t mcu_uart_task_h;
QueueHandle_t client_task_q;

/**********Settings**********/

/**********Vars**********/
char recv_buf_update[2048 + 1];

/**********Functions definition**********/
void mcu_uart_task_create(uint32_t stack_size, uint32_t prio) {
    xTaskCreate(
        &mcu_uart_task,
        "mcu_uart_task",
        stack_size,
        NULL,
        prio,
        &mcu_uart_task_h);
}

#define TXD_PIN (GPIO_NUM_17)
#define RXD_PIN (GPIO_NUM_18)

static const int RX_BUF_SIZE = 1024;
static QueueHandle_t uart0_queue;

/*
115200 - 5*200us
921600 - 1.5*200us
*/

void uart_init(void) {
    const uart_config_t uart_config = {
        .baud_rate = 921600,
        .data_bits = UART_DATA_8_BITS,
        .parity = UART_PARITY_DISABLE,
        .stop_bits = UART_STOP_BITS_1,
        .flow_ctrl = UART_HW_FLOWCTRL_DISABLE,
        .source_clk = UART_SCLK_DEFAULT,
    };
    // We won't use a buffer for sending data.
    uart_driver_install(
        UART_NUM_1, RX_BUF_SIZE * 2, RX_BUF_SIZE * 2, 20, &uart0_queue, 0);
    uart_param_config(UART_NUM_1, &uart_config);
    uart_set_pin(
        UART_NUM_1, TXD_PIN, RXD_PIN, UART_PIN_NO_CHANGE, UART_PIN_NO_CHANGE);
}

#define HEADER_REQUEST 0xD0
#define HEADER_ANSWER  0xD1

#define ASP_MIN_MSG_SIZE  7
#define ASP_CMD_UPDATE_FW 0x01
#define ASP_CMD_POLL      0x02
#define ASP_CMD_GET_SN    0x03

#define ASP_CMD_GET_FW_VER 0x05
#define ASP_CMD_RESET      0x13

#define ASP_CMD_READ_PARAM  0xA0
#define ASP_CMD_WRITE_PARAM 0xA1

#define DISPLAY_MIN_MSG_SIZE 6U

void mcu_uart_answer_fw_ver(void) {
    uint8_t tx_buf[] = {
        HEADER_ANSWER,
        0x00,
        0x00,
        ASP_CMD_GET_FW_VER,
        MAJOR,
        MINOR,
        PATCH,
        0x00,
        0x00};
    tx_buf[1] = (uint8_t)(sizeof(tx_buf) >> 8);
    tx_buf[2] = (uint8_t)(sizeof(tx_buf));
    //get_crc_and_write(tx_buf, sizeof(tx_buf) - 2, &tx_buf[sizeof(tx_buf) - 2]);
    uart_write_bytes(UART_NUM_1, tx_buf, sizeof(tx_buf));
}

void mcu_uart_handle_msg(uint8_t* data, uint32_t len) {
    uint8_t header = data[0];
    uint8_t cmd;
    /* Minimal length check */
    if(len >= DISPLAY_MIN_MSG_SIZE) {
        /* Device type check */
        if(header == HEADER_REQUEST || header == HEADER_ANSWER) {
            /* CRC check 
            crc_in.crc_u8[0] = data[len - 2];
            crc_in.crc_u8[1] = data[len - 1];

            if(crc_modbus_compare_u16(data, len - 2, crc_in.crc_u16) == 0) {

            printf("crc in %x\r\n", crc_in.crc_u16);
            printf("crc %x\r\n", crc.crc_u16);
            return;
        }
        */
            cmd = data[3];

            if(header == HEADER_REQUEST) {
                ESP_LOGI(TAG, "HEADER_REQUEST\r\n");
                switch(cmd) {
                case ASP_CMD_POLL:
                    //display_send_status(cmd, 1);
                    break;

                case ASP_CMD_GET_FW_VER:
                    //display_send_fw_ver();
                    mcu_uart_answer_fw_ver();
                    break;

                case ASP_CMD_RESET:
                    //display_send_status(cmd, 1);
                    //NVIC_SystemReset();
                    break;

                case ASP_CMD_GET_SN:
                    //ASP_send_sn();
                    break;
                }
            } else {
                ESP_LOGI(TAG, "HEADER_ANSWER\r\n");
                switch(cmd) {
                case ASP_CMD_POLL:
                    //display_send_status(cmd, 1);
                    break;

                case ASP_CMD_GET_FW_VER:
                    //display_send_fw_ver();
                    break;

                case ASP_CMD_RESET:
                    //display_send_status(cmd, 1);
                    //NVIC_SystemReset();
                    break;

                case ASP_CMD_GET_SN:
                    //ASP_send_sn();
                    break;
                }
            }
        }
    }
}

void mcu_uart_task(void* pvParameters) {
    uart_event_t event;
    uint8_t dtmp[RX_BUF_SIZE];
    ESP_LOGI(TAG, "created");
    uart_init();
    int cnt = 0;
    for(;;) {
        //Waiting for UART event.
        if(xQueueReceive(
               uart0_queue, (void*)&event, (TickType_t)portMAX_DELAY)) {
            bzero(dtmp, RX_BUF_SIZE);
            ESP_LOGI(TAG, "uart[%d] event:", UART_NUM_1);
            cnt++;
            ESP_LOGI(TAG, "cnt %d:", cnt);
            switch(event.type) {
                //Event of UART receving data
                /*We'd better handler data event fast, there would be much more data events than
            other types of events. If we take too much time on data event, the queue might
            be full.*/
            case UART_DATA:
                ESP_LOGI(TAG, "[UART DATA]: %d", event.size);
                uart_read_bytes(UART_NUM_1, dtmp, event.size, portMAX_DELAY);
                mcu_uart_handle_msg(dtmp, event.size);
                break;
            //Event of HW FIFO overflow detected
            case UART_FIFO_OVF:
                ESP_LOGI(TAG, "hw fifo overflow");
                // If fifo overflow happened, you should consider adding flow control for your application.
                // The ISR has already reset the rx FIFO,
                // As an example, we directly flush the rx buffer here in order to read more data.
                uart_flush_input(UART_NUM_1);
                xQueueReset(uart0_queue);
                break;
            //Event of UART ring buffer full
            case UART_BUFFER_FULL:
                ESP_LOGI(TAG, "ring buffer full");
                // If buffer full happened, you should consider increasing your buffer size
                // As an example, we directly flush the rx buffer here in order to read more data.
                uart_flush_input(UART_NUM_1);
                xQueueReset(uart0_queue);
                break;
            //Event of UART RX break detected
            case UART_BREAK:
                ESP_LOGI(TAG, "uart rx break");
                break;
            //Event of UART parity check error
            case UART_PARITY_ERR:
                ESP_LOGI(TAG, "uart parity error");
                break;
            //Event of UART frame error
            case UART_FRAME_ERR:
                ESP_LOGI(TAG, "uart frame error");
                break;
            //UART_PATTERN_DET
            case UART_PATTERN_DET:
                break;
            //Others
            default:
                ESP_LOGI(TAG, "uart event type: %d", event.type);
                break;
            }
        }
    }
}
