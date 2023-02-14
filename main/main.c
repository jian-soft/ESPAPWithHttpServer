/*  WiFi softAP Example

   This example code is in the Public Domain (or CC0 licensed, at your option.)

   Unless required by applicable law or agreed to in writing, this
   software is distributed on an "AS IS" BASIS, WITHOUT WARRANTIES OR
   CONDITIONS OF ANY KIND, either express or implied.
*/
#include <string.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "esp_mac.h"
#include "esp_wifi.h"
#include "esp_event.h"
#include "esp_log.h"
#include "nvs_flash.h"
#include "lwip/err.h"
#include "lwip/sys.h"
#include "my_wifi.h"
#include "drv8833_pwm.h"


void app_main(void)
{
    wifi_init_softap();

    pwm_init();

    drv8833_enable();

    //起一个task, 5s反转一下GPIO4的电平
    ///int cnt = 0;
    //while(1) {
        //printf("cnt: %d\n", cnt++);
        //vTaskDelay(1000 / portTICK_PERIOD_MS);
        //gpio_set_level(GPIO_NUM_4, cnt % 2);
    //}
}
