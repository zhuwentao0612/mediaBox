#include "pwm.h"
#include "app_error.h"
#include "nrf_gpio.h"
#include "app_pwm.h"
#include "nrf_delay.h"

#define PWM_PIN  10 
APP_PWM_INSTANCE(PWM1,1);                   // Create the instance "PWM1" using TIMER1.

bool duty_flag = false;

void pwm_init()
{
		//PWM, 200Hz,  5000L
		uint32_t err_code;
		app_pwm_config_t pwm1_cfg = APP_PWM_DEFAULT_CONFIG_1CH(1000L, PWM_PIN);
		err_code = app_pwm_init(&PWM1,&pwm1_cfg,NULL);
		APP_ERROR_CHECK(err_code);
		app_pwm_enable(&PWM1);
		app_pwm_channel_duty_set(&PWM1, 0, 50);
}

void pwm_uninit()
{
		app_pwm_disable(&PWM1);
		app_pwm_uninit(&PWM1);
}

void pwm_work()
{
		if(!duty_flag){
			 while (app_pwm_channel_duty_set(&PWM1, 0, 0) == NRF_ERROR_BUSY);
			 nrf_delay_ms(50);	
			 duty_flag = true;
		}else if(duty_flag)
		{
			 while (app_pwm_channel_duty_set(&PWM1, 0, 50) == NRF_ERROR_BUSY);
			 nrf_delay_ms(50);	
			 duty_flag = false;
		}
}

void pwm_work_short()
{
		pwm_init();		
		nrf_delay_ms(100);
		pwm_uninit();	
}