#include "oled.h"
#include "nrf_gpio.h"
#include <stdbool.h>
#include <stdio.h>
#include <stdint.h>
#include "nrf_delay.h"

void Clear_Screen();

void I2C_START_OLED(void)      
{
    I2C_SDA_1;
		nrf_delay_us(4);	
		I2C_SCL_1;
		nrf_delay_us(4);			
		I2C_SDA_0;
		nrf_delay_us(4);
}
 
void I2C_STOP_OLED(void)
{
    I2C_SDA_0;
		nrf_delay_us(4);
		I2C_SCL_1;
		nrf_delay_us(4);
		I2C_SDA_1;
		nrf_delay_us(4);
}

bool I2C_Wait_Ack(void)     //SCL由低变高，读取SDA是低电平，确认Ack    
{
		uint8_t i = 0;
		I2C_SCL_0;              
		nrf_delay_us(4);
		I2C_SCL_1;
		I2C_SDA_IN;
		nrf_delay_us(4);

		while(I2C_SDA_READ && (i < 250)){
				 i++;
		}
		if(i == 250)  
				 SEGGER_RTT_printf(0, "I2CWaitAck error \r\n");	
		
		I2C_SCL_0;
		I2C_SDA_OUT;  
		return true;
}


void Write_IIC_Data_OLED(uint8_t data)
{
	  uint8_t i = 8;
    while(i--)
    { 
      I2C_SCL_0;    
      nrf_delay_us(4);
      if(data&0x80){ 
         I2C_SDA_1;
      }else{ 
         I2C_SDA_0;
			}
			data<<=1;
      nrf_delay_us(4);
      I2C_SCL_1;
      nrf_delay_us(4);
    }
		I2C_SCL_0;

		return;		
}

void Write_Command(uint8_t command)
{
   I2C_START_OLED();
   Write_IIC_Data_OLED(0x78);   
	 I2C_Wait_Ack();	
   Write_IIC_Data_OLED(0x00);       
	 I2C_Wait_Ack();		
   Write_IIC_Data_OLED(command); 
	 I2C_Wait_Ack();	
   I2C_STOP_OLED();
}

void Write_Data(uint8_t date)
{
   I2C_START_OLED();
   Write_IIC_Data_OLED(0x78);   
	 I2C_Wait_Ack();		
   Write_IIC_Data_OLED(0x40); 
	 I2C_Wait_Ack();		
   Write_IIC_Data_OLED(date);
	 I2C_Wait_Ack();	
   I2C_STOP_OLED();
}

void Reset_IC_OLED()
{
	 I2C_VCC_EN_OUT;
	 I2C_VCC_EN_1;
	 nrf_delay_ms(1);
	 I2C_RES_OUT;
   nrf_delay_ms(1);
   I2C_RES_0;
   nrf_delay_ms(1);
   I2C_RES_1;
   nrf_delay_ms(1);
}

void Init_IC_OLED()
{
		I2C_SDA_OUT;
		I2C_SCL_OUT;
		Write_Command(0xAE); // Set Display Off
		Write_Command(0xD5); // Display divide ratio/osc. freq. mode
		Write_Command(0xC1); // 115HZ
		Write_Command(0xA8); // Multiplex ration mode:
		Write_Command(0x1F);
		Write_Command(0xAD); // External or Internal VCOMH/ IREF Selection
		Write_Command(0x00); // Internal VCOMH/ External IREF
		Write_Command(0x20); // Set Memory Addressing Mode
		Write_Command(0x02); // Page Addressing Mode
		Write_Command(0xD3); // Set Display Offset
		Write_Command(0x00);
		Write_Command(0x40); // Set Display Start Line
		Write_Command(0x8D); // DC-DC Control Mode Set
		Write_Command(0x14); // DC-DC ON/OFF Mode Set
		Write_Command(0xA0); // Segment Remap
		Write_Command(0xC8); // Set COM Output Scan Direction
		Write_Command(0xDA); // Set pads hardware: alternative
		Write_Command(0x12);
		Write_Command(0x81); // Contrast control
		Write_Command(0x53);
		Write_Command(0xD9); // Set pre-charge period
		Write_Command(0x22);
		Write_Command(0xDB); // VCOMH deselect level mode
		Write_Command(0x00);
		Write_Command(0xA4); // Set Entire Display On/Off
		Write_Command(0xA6); // Set Normal Display
		//Clear_Screen();
		Write_Command(0xAF); // Set Display On
}


void Clear_Screen()
{
   uint8_t i,j;
   Write_Command(0xaf);
   Write_Command(0x40);  //开启写数据命令
   for(i=0;i<8;i++)
   {
	  Write_Command(0xb0+i); //page mode
	  Write_Command(0x10);  //起始列地址高四位
	  Write_Command(0x02);  //起始列地址低四位
      for(j=0;j<128;j++)
				Write_Data(0x00);
   }
}

void All_Screen()                                          
  {
   uint8_t i,j;
   Write_Command(0xaf);
   Write_Command(0x40);
   for(i=0;i<8;i++)
   {
			Write_Command(0xb0+i);
			Write_Command(0x10);
			Write_Command(0x02);
      for(j=0;j<128;j++)
				Write_Data(0xff);
    }
}
