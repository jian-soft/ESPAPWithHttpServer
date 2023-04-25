#include <esp_log.h>
#include "driver/gpio.h"
#include "driver/ledc.h"

//static const char *TAG = "pwm";

#define DRV8833_ENABLE_IO   GPIO_NUM_4
#define DRV8833_AIN1_IO     GPIO_NUM_5
#define DRV8833_AIN2_IO     GPIO_NUM_6
#define DRV8833_BIN1_IO     GPIO_NUM_7
#define DRV8833_BIN2_IO     GPIO_NUM_8

static void gpio_init(void)
{
    //设置IO4为OUTPUT，控制DRV8833的使能
    gpio_config_t io_conf = {};
    io_conf.intr_type = GPIO_INTR_DISABLE;
    io_conf.mode = GPIO_MODE_OUTPUT;
    //bit mask of the pins that you want to set,e.g.GPIO18/19
    io_conf.pin_bit_mask = ((1ULL<<DRV8833_ENABLE_IO));
    io_conf.pull_down_en = 0;
    io_conf.pull_up_en = 0;
    gpio_config(&io_conf);
}

void pwm_init(void)
{
    gpio_init();  //顺带初始化下GPIO

    //第一步 设置定时器
    ledc_timer_config_t ledc_timer = {
        .speed_mode       = LEDC_LOW_SPEED_MODE,
        .timer_num        = LEDC_TIMER_0,
        .duty_resolution  = LEDC_TIMER_10_BIT,
        .freq_hz          = 100,
        .clk_cfg          = LEDC_AUTO_CLK
    };
    ESP_ERROR_CHECK(ledc_timer_config(&ledc_timer));

    //第二步 设置每个通道对应的GPIO
#define PWM_CH_NUM 4
    ledc_channel_config_t ledc_channel[PWM_CH_NUM] = {
        {
            .channel    = LEDC_CHANNEL_0,
            .duty       = 0,
            .gpio_num   = DRV8833_AIN1_IO,
            .speed_mode = LEDC_LOW_SPEED_MODE,
            .hpoint     = 0,
            .timer_sel  = LEDC_TIMER_0,
            .intr_type  = LEDC_INTR_DISABLE,
        },
        {
            .channel    = LEDC_CHANNEL_1,
            .duty       = 0,
            .gpio_num   = DRV8833_AIN2_IO,
            .speed_mode = LEDC_LOW_SPEED_MODE,
            .hpoint     = 0,
            .timer_sel  = LEDC_TIMER_0,
            .intr_type  = LEDC_INTR_DISABLE,
        },
        {
            .channel    = LEDC_CHANNEL_2,
            .duty       = 0,
            .gpio_num   = DRV8833_BIN1_IO,
            .speed_mode = LEDC_LOW_SPEED_MODE,
            .hpoint     = 0,
            .timer_sel  = LEDC_TIMER_0,
            .intr_type  = LEDC_INTR_DISABLE,
        },
        {
            .channel    = LEDC_CHANNEL_3,
            .duty       = 0,
            .gpio_num   = DRV8833_BIN2_IO,
            .speed_mode = LEDC_LOW_SPEED_MODE,
            .hpoint     = 0,
            .timer_sel  = LEDC_TIMER_0,
            .intr_type  = LEDC_INTR_DISABLE,
        },
    };
    int ch;
    for (ch = 0; ch < PWM_CH_NUM; ch++) {
        ESP_ERROR_CHECK(ledc_channel_config(&ledc_channel[ch]));
    }
}

static void __drv8833_enable(void)
{
    gpio_set_level(DRV8833_ENABLE_IO, 1);
}
static void __drv8833_disable(void)
{
    gpio_set_level(DRV8833_ENABLE_IO, 0);
}

/* @speed: 0~100 @direction: >=0-foward -1-back */
void drv8833_motorA_run(int speed, int direction)
{
    int duty = speed*100/1024;
    if (direction >= 0) {
        ESP_ERROR_CHECK(ledc_set_duty(LEDC_LOW_SPEED_MODE, LEDC_CHANNEL_0, duty));
        ESP_ERROR_CHECK(ledc_set_duty(LEDC_LOW_SPEED_MODE, LEDC_CHANNEL_1, 0));
    } else {
        ESP_ERROR_CHECK(ledc_set_duty(LEDC_LOW_SPEED_MODE, LEDC_CHANNEL_0, 0));
        ESP_ERROR_CHECK(ledc_set_duty(LEDC_LOW_SPEED_MODE, LEDC_CHANNEL_1, duty));

    }

    ESP_ERROR_CHECK(ledc_update_duty(LEDC_LOW_SPEED_MODE, LEDC_CHANNEL_0));
    ESP_ERROR_CHECK(ledc_update_duty(LEDC_LOW_SPEED_MODE, LEDC_CHANNEL_1));
}


void drv8833_motorA_stop(void)
{
    ESP_ERROR_CHECK(ledc_set_duty(LEDC_LOW_SPEED_MODE, LEDC_CHANNEL_0, 1024));
    ESP_ERROR_CHECK(ledc_set_duty(LEDC_LOW_SPEED_MODE, LEDC_CHANNEL_1, 1024));
    ESP_ERROR_CHECK(ledc_update_duty(LEDC_LOW_SPEED_MODE, LEDC_CHANNEL_0));
    ESP_ERROR_CHECK(ledc_update_duty(LEDC_LOW_SPEED_MODE, LEDC_CHANNEL_1));
}

void drv8833_motorB_run(int speed, int direction)
{
    int duty = speed*100/1024;
    if (direction >= 0) {
        ESP_ERROR_CHECK(ledc_set_duty(LEDC_LOW_SPEED_MODE, LEDC_CHANNEL_2, duty));
        ESP_ERROR_CHECK(ledc_set_duty(LEDC_LOW_SPEED_MODE, LEDC_CHANNEL_3, 0));
    } else {
        ESP_ERROR_CHECK(ledc_set_duty(LEDC_LOW_SPEED_MODE, LEDC_CHANNEL_2, 0));
        ESP_ERROR_CHECK(ledc_set_duty(LEDC_LOW_SPEED_MODE, LEDC_CHANNEL_3, duty));

    }

    ESP_ERROR_CHECK(ledc_update_duty(LEDC_LOW_SPEED_MODE, LEDC_CHANNEL_2));
    ESP_ERROR_CHECK(ledc_update_duty(LEDC_LOW_SPEED_MODE, LEDC_CHANNEL_3));
}

void drv8833_motorB_stop(void)
{
    ESP_ERROR_CHECK(ledc_set_duty(LEDC_LOW_SPEED_MODE, LEDC_CHANNEL_2, 1024));
    ESP_ERROR_CHECK(ledc_set_duty(LEDC_LOW_SPEED_MODE, LEDC_CHANNEL_3, 1024));
    ESP_ERROR_CHECK(ledc_update_duty(LEDC_LOW_SPEED_MODE, LEDC_CHANNEL_2));
    ESP_ERROR_CHECK(ledc_update_duty(LEDC_LOW_SPEED_MODE, LEDC_CHANNEL_3));
}

void car_forward(int speed1, int speed2)
{
    __drv8833_enable();
    drv8833_motorA_run(speed1, 1);
    drv8833_motorB_run(speed2, 1);
}

void car_back(int speed1, int speed2)
{
    __drv8833_enable();
    drv8833_motorA_run(speed1, -1);
    drv8833_motorB_run(speed2, -1);
}


void car_stop(void)
{
    drv8833_motorA_stop();
    drv8833_motorB_stop();
    __drv8833_disable();
}


