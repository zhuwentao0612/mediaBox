#include "adc.h"
#include "nrf_drv_saadc.h"
#include "app_error.h"
#include "app_uart.h"
#include "nrf_gpio.h"

#define ADC_ENABLE_PIN 4
uint32_t   adc_err_code;

void saadc_callback(nrf_drv_saadc_evt_t const * p_event)
{

}

void adc_enable()
{
		nrf_gpio_cfg_output(ADC_ENABLE_PIN);
		nrf_gpio_pin_set(ADC_ENABLE_PIN);
}

void adc_disable()
{
		nrf_gpio_cfg_output(ADC_ENABLE_PIN);
		nrf_gpio_pin_clear(ADC_ENABLE_PIN);
}

void adc_init()
{	
    nrf_saadc_channel_config_t channel_config =NRF_DRV_SAADC_DEFAULT_CHANNEL_CONFIG_SE(NRF_SAADC_INPUT_AIN3);
    adc_err_code = nrf_drv_saadc_init(NULL, saadc_callback);
    APP_ERROR_CHECK(adc_err_code);

    adc_err_code = nrf_drv_saadc_channel_init(NRF_SAADC_INPUT_AIN3, &channel_config);
    APP_ERROR_CHECK(adc_err_code);
	
	  adc_enable();
}

void adc_uninit()
{
		adc_disable();
		nrf_drv_saadc_uninit();
		nrf_drv_saadc_channel_uninit(NRF_SAADC_INPUT_AIN3);
}

/*int32_t adc_convert()
{ 
		 int32_t ls32AdcResult = 0;
		 int32_t result = 0;
		 nrf_saadc_value_t ls16AdcTmp = 0;
	
		 for(uint8_t i = 0; i < 10; i ++)
		 {
				adc_err_code  = nrf_drv_saadc_sample_convert(NRF_SAADC_INPUT_AIN3,&ls16AdcTmp);
			  APP_ERROR_CHECK(adc_err_code);
			  ls32AdcResult += ls16AdcTmp;
			
		 }	
		 
		 result = ls32AdcResult / 10;
		 SEGGER_RTT_printf(0, "adc data = %02x\r\n",(result & 0x0000ff00) >> 8);
		 SEGGER_RTT_printf(0, "adc data = %02x\r\n",result & 0x000000ff);
		 return result;
}
*/

int16_t adc_convert()
{ 
		 nrf_saadc_value_t ls16AdcTmp = 0;
			
		 nrf_drv_saadc_sample_convert(NRF_SAADC_INPUT_AIN3,&ls16AdcTmp);
		 			 
		 //SEGGER_RTT_printf(0, "adc data = %02x\r\n",(ls16AdcTmp & 0xff00) >> 8);
		 //SEGGER_RTT_printf(0, "adc data = %02x\r\n",ls16AdcTmp & 0x00ff);
		 return ls16AdcTmp;
}