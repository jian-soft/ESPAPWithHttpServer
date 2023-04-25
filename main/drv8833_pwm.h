
#ifndef __DRV8833_PWM_H__
#define __DRV8833_PWM_H__

#ifdef __cplusplus
extern "C" {
#endif

void pwm_init(void);


void car_forward(int speed1, int speed2);
void car_back(int speed1, int speed2);
void car_stop(void);






#ifdef __cplusplus
}
#endif

#endif /* __DRV8833_PWM_H__ */
