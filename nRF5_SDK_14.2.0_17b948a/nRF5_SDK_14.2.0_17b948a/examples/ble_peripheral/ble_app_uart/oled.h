#ifndef _OLED_H_
#define _OLED_H_

#include "stdint.h"
#include "nrf_delay.h"
#include <string.h>
#include "nrf_gpio.h"

#define SDA   18
#define SCL   20
#define RES   21
#define VCC_EN   16

#define    I2C_SCL_0          nrf_gpio_pin_clear(SCL)
#define    I2C_SCL_1          nrf_gpio_pin_set(SCL)

#define    I2C_RES_0          nrf_gpio_pin_clear(RES)
#define    I2C_RES_1          nrf_gpio_pin_set(RES)
                              
#define    I2C_SDA_0          nrf_gpio_pin_clear(SDA)
#define    I2C_SDA_1          nrf_gpio_pin_set(SDA)

#define    I2C_VCC_EN_0          nrf_gpio_pin_clear(VCC_EN)
#define    I2C_VCC_EN_1          nrf_gpio_pin_set(VCC_EN)

#define    I2C_SDA_IN        nrf_gpio_cfg_input(SDA,NRF_GPIO_PIN_NOPULL)
#define    I2C_SDA_OUT       nrf_gpio_cfg_output(SDA)
#define    I2C_SDA_READ      nrf_gpio_pin_read(SDA) 
#define    I2C_SCL_OUT       nrf_gpio_cfg_output(SCL)
#define    I2C_RES_OUT       nrf_gpio_cfg_output(RES)
#define    I2C_VCC_EN_OUT    nrf_gpio_cfg_output(VCC_EN)

void Init_IC_OLED();
void Clear_Screen();
void All_Screen();
void Reset_IC_OLED();

#endif
