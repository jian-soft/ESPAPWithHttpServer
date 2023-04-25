
#ifndef __DRV8833_PWM_H__
#define __DRV8833_PWM_H__

#ifdef __cplusplus
extern "C" {
#endif

void pwm_init(void);
void drv8833_motorA_foward(void);
void drv8833_motorA_back(void);
void drv8833_motorA_stop(void);

void drv8833_motorB_foward(void);
void drv8833_motorB_back(void);
void drv8833_motorB_stop(void);

void car_foward(void);
void car_back(void);
void car_stop(void);
void car_turn_left();
void car_turn_right();






#ifdef __cplusplus
}
#endif

#endif /* __DRV8833_PWM_H__ */
