#include <esp_log.h>
#include "driver/gpio.h"
#include "driver/ledc.h"

//static const char *TAG = "pwm";

#define DRV8833_ENABLE_IO   GPIO_NUM_3
#define PWRKEYOUT           GPIO_NUM_20
#define PWRKEYIN            GPIO_NUM_21
#define GPIO_OUTPUT_PIN_SEL ((1ULL<<DRV8833_ENABLE_IO) | (1<<PWRKEYOUT))
#define GPIO_INPUT_PIN_SEL  (1ULL<<PWRKEYIN)

void gpio_init(void)
{
    //设置IO3为OUTPUT，控制DRV8833的使能
    //设置IO21为OUTPUT，控制供电
    gpio_config_t io_conf = {};
    io_conf.intr_type = GPIO_INTR_DISABLE;
    io_conf.mode = GPIO_MODE_OUTPUT;
    //bit mask of the pins that you want to set,e.g.GPIO18/19
    io_conf.pin_bit_mask = GPIO_OUTPUT_PIN_SEL;
    io_conf.pull_down_en = 0;
    io_conf.pull_up_en = 0;
    gpio_config(&io_conf);

    //设置IO20为INPUT，检测按键
    io_conf.intr_type = GPIO_INTR_DISABLE;
    io_conf.mode = GPIO_MODE_INPUT;
    //bit mask of the pins that you want to set,e.g.GPIO18/19
    io_conf.pin_bit_mask = GPIO_INPUT_PIN_SEL;
    io_conf.pull_down_en = 0;
    io_conf.pull_up_en = 1;
    gpio_config(&io_conf);
}


void gpio_enable_drv8833(void)
{
    gpio_set_level(DRV8833_ENABLE_IO, 1);
}

void gpio_disable_drv8833(void)
{
    gpio_set_level(DRV8833_ENABLE_IO, 0);
}


void gpio_set_pwrkeyout(uint8_t val)
{
    gpio_set_level(PWRKEYOUT, val);
}

int gpio_get_pwrkeyin()
{
    return gpio_get_level(PWRKEYIN);
}

