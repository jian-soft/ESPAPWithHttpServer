
#ifndef __MY_GPIO_H__
#define __MY_GPIO_H__

#ifdef __cplusplus
extern "C" {
#endif

void gpio_init(void);
void gpio_enable_drv8833(void);
void gpio_disable_drv8833(void);


void gpio_set_pwrkeyout(uint8_t val);
int gpio_get_pwrkeyin();





#ifdef __cplusplus
}
#endif

#endif /* __MY_GPIO_H__ */
