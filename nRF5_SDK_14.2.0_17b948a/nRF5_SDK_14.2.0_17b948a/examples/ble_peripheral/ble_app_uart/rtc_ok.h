#ifndef _OLED_H_
#define _OLED_H_

#include "stdint.h"
#include "nrf_delay.h"
#include <string.h>
#include "nrf_gpio.h"

#define    true    1
#define    false   0 
#define    RTC_Address      0x64                //RTC address
#define    IDcode           0x72                //8bit ID begin address
#define    Bat_bit8         0x1A                //电量高8位寄存器地址
#define    Bat_Low8         0x1B                //电量低8位寄存器地址
	
#define    SDA     30                 
#define    SCL     25    


#define    I2C_SCL_0          nrf_gpio_pin_clear(SCL)
#define    I2C_SCL_1          nrf_gpio_pin_set(SCL)
                              
#define    I2C_SDA_0          nrf_gpio_pin_clear(SDA)
#define    I2C_SDA_1          nrf_gpio_pin_set(SDA)

#define    I2C_SDA_IN        nrf_gpio_cfg_input(SDA,NRF_GPIO_PIN_NOPULL)
#define    I2C_SDA_OUT       nrf_gpio_cfg_output(SDA)
#define    I2C_SDA_READ      nrf_gpio_pin_read(SDA) 
#define    I2C_SCL_OUT       nrf_gpio_cfg_output(SCL)
#define    I2C_RES_OUT       nrf_gpio_cfg_output(RES)

void test_rtc();
void test_rtc_init();

#endif
