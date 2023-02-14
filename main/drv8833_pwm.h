
#ifndef __DRV8833_PWM_H__
#define __DRV8833_PWM_H__

#ifdef __cplusplus
extern "C" {
#endif

void pwm_init(void);
void drv8833_enable(void);
void drv8833_disable(void);
void drv8833_motorA_foward(void);
void drv8833_motorA_back(void);
void drv8833_motorA_stop(void);

void drv8833_motorB_foward(void);
void drv8833_motorB_back(void);




#ifdef __cplusplus
}
#endif

#endif /* __DRV8833_PWM_H__ */
