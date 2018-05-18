#include "app_error.h"
#include "nrf_gpio.h"
#include "nrf_delay.h"
#include "rtc.h"

typedef unsigned char uchar;
typedef unsigned int uint;

uchar         Batbit8,Batlow7;        //电池电量寄存器值
uint          Bat;                    //电池电量值
uchar         Sram[8];                
uchar         data1[8];  

typedef        struct
{
        uchar        second;
        uchar        minute;
        uchar        hour;
        uchar        week;
        uchar        day;
        uchar        month;
        uchar        year;
}S_Time;        

S_Time  RTC={0x23,0x43,0x9,0x05,0x11,0x5,0x18};        //初始化时间结构体变量
//           秒   分   时   周  日   月   年


uchar I2CReadOneByte(uchar DeviceAddress,uchar add);//读一个字节
void I2CWriteOneByte(uchar DeviceAddress,uchar add, uchar date);//写一个字节
void I2CReadSerial(uchar DeviceAddress, uchar Address, uchar length,uchar *ps);//连续读
void I2CWriteSerial(uchar DeviceAddress, uchar Address, uchar length,uchar *ps);//连续写
void I2CWriteDate(S_Time        SetRTC);//写时间      
void I2CReadDate(S_Time        *psRTC);//读时间
void WriteTimeOn(void);//写允许
void WriteTimeOff(void);//写禁止

void I2CStart(void)  //SCL高，SDA由高变低
{
        I2C_SDA_1;
				nrf_delay_us(4);	
        I2C_SCL_1;
        nrf_delay_us(4);			
        I2C_SDA_0;
        nrf_delay_us(4);		
}

void I2CStop(void)   //SCL高，SDA由低变高
{
        I2C_SDA_0;
				nrf_delay_us(4);
				I2C_SCL_1;
				nrf_delay_us(4);
				I2C_SDA_1;
				nrf_delay_us(4);
}

void I2CAck(void)
{        
        I2C_SDA_0;
        I2C_SCL_0;
        nrf_delay_us(4);
        I2C_SCL_1;
        nrf_delay_us(4);
        I2C_SCL_0;
}

void I2CNoAck(void)
{        
        I2C_SDA_1;
        I2C_SCL_0;
        nrf_delay_us(4);
        I2C_SCL_1;
        nrf_delay_us(4);
        I2C_SCL_0;
}

bool I2CWaitAck(void)     //SCL由低变高，读取SDA是低电平，确认Ack    
{
				uchar i = 0;
        I2C_SCL_0;              
        nrf_delay_us(4);
        I2C_SCL_1;
				I2C_SDA_IN;
        nrf_delay_us(4);
	
        while(I2C_SDA_READ && (i < 250)){
						 i++;
        }
				//SEGGER_RTT_printf(0, "I2C_SDA_READ = %d,i = %d \r\n",I2C_SDA_READ,i);	
				if(i == 250)  
					   SEGGER_RTT_printf(0, "I2CWaitAck error \r\n");	
				
        I2C_SCL_0;
				I2C_SDA_OUT;  
        return true;
}

void I2CSendByte(uchar demand) 
{
        uchar i=8;                       
                                         
        while(i--)
        {
						I2C_SCL_0;
						nrf_delay_us(4);
						if(demand&0x80){
							I2C_SDA_1; 
						}else{
							I2C_SDA_0; 
						}
						demand<<=1;
						nrf_delay_us(4);
						I2C_SCL_1;
						nrf_delay_us(4);
        }
        I2C_SCL_0;
}

uchar I2CReceiveByte(void)      
{
        uchar i=8;
        uchar ddata=0;
				I2C_SDA_IN;                    
        while(i--)
        {
						ddata<<=1;      
						I2C_SCL_0;
						nrf_delay_us(4);
						I2C_SCL_1;
						nrf_delay_us(4);
						if(I2C_SDA_READ)
						{
								ddata|=0x01;
						}
        }
        I2C_SCL_0;
				I2C_SDA_OUT;    
				//SEGGER_RTT_printf(0, "ddata = %d\r\n",ddata);	
        return ddata;
}

void WakeRTC(){
				I2CStart();	
        I2CSendByte(RTC_Address);
}

void I2CWriteOneByte(uchar DeviceAddress,uchar add, uchar date)
{                
        I2CStart();	
        I2CSendByte(DeviceAddress);      
        I2CWaitAck();   
        I2CSendByte(add);                   
        I2CWaitAck();        
        I2CSendByte(date);               
        I2CWaitAck();        
        I2CStop(); 
}

uchar I2CReadOneByte(uchar DeviceAddress,uchar add)
{                
        uchar dat;
        I2CStart();
	
        I2CSendByte(DeviceAddress);      
        I2CWaitAck();
        I2CSendByte(add);            
        I2CWaitAck();
        I2CStart();        
        I2CSendByte(DeviceAddress+1);        
        I2CWaitAck();        
        dat=I2CReceiveByte();        
        I2CNoAck();
	
        I2CStop(); 
        return  dat;
}

void WriteTimeOn(void)
{                
        I2CWriteOneByte(RTC_Address,0x10,0x80);
        I2CWriteOneByte(RTC_Address,0x0f,0xff);
}

void WriteTimeOff(void)
{                
        I2CWriteOneByte(RTC_Address,0x0f,0x7b);
        I2CWriteOneByte(RTC_Address,0x10,0);
}

void I2CReadDate(S_Time   *psRTC)
{
        
        I2CStart();
				
        I2CSendByte(RTC_Address+1); 
        I2CWaitAck();
				
        psRTC->second=I2CReceiveByte();
        I2CAck();
        psRTC->minute=I2CReceiveByte();
        I2CAck();
        psRTC->hour=I2CReceiveByte();
        I2CAck();
        psRTC->week=I2CReceiveByte();
        I2CAck();
        psRTC->day=I2CReceiveByte();
        I2CAck();
        psRTC->month=I2CReceiveByte();
        I2CAck();
        psRTC->year=I2CReceiveByte();
        I2CNoAck();           
        I2CStop();
				
				SEGGER_RTT_printf(0, "second = 0x%x,minute = 0x%x,hour = 0x%x,week = 0x%x,day = 0x%x,month = 0x%x,year = 0x%x\r\n",
														psRTC->second,psRTC->minute, psRTC->hour,
														psRTC->week,psRTC->day,psRTC->month,psRTC->year);	

}

void I2CWriteDate(S_Time  SetRTC)       //设置时间，需要一次性全部写入年、月、日、时、分、秒、星期
{ 
        S_Time   *psRTC;
        psRTC=&SetRTC;
        WakeRTC();  	
				WriteTimeOn();   
	
				SEGGER_RTT_printf(0, "write RTC second = 0x%x,minute = 0x%x,hour = 0x%x,week = 0x%x,day = 0x%x,month = 0x%x,year = 0x%x\r\n",
														psRTC->second,psRTC->minute, psRTC->hour,
														psRTC->week,psRTC->day,psRTC->month,psRTC->year);	
	
        I2CStart();
        I2CSendByte(RTC_Address); 
        I2CWaitAck();
        I2CSendByte(0x00);    		
        I2CWaitAck();        
        I2CSendByte(psRTC->second);     	
        I2CWaitAck();        
        I2CSendByte(psRTC->minute);   				
        I2CWaitAck();        
        //I2CSendByte(psRTC->hour|0x80);          //同时设置小时寄存器最高位，0位12小时制，1位24小时制      
				I2CSendByte(psRTC->hour); 	          //12小时制
				I2CWaitAck();        
        I2CSendByte(psRTC->week);                 
				I2CWaitAck();        
        I2CSendByte(psRTC->day);  			
        I2CWaitAck();        
        I2CSendByte(psRTC->month);   				
        I2CWaitAck();        
        I2CSendByte(psRTC->year);      				
        I2CWaitAck();  
        I2CStop();
        
        WriteTimeOff();    					
}

//设置报警时间
void WriteALARM(void)                               
{                                               
        WriteTimeOn();
        I2CWriteOneByte(RTC_Address,0x09,0x08);      //8时
        I2CWriteOneByte(RTC_Address,0x0b,0x14);      //14日
        I2CWriteOneByte(RTC_Address,0x0c,0x02);      //2月  
        I2CWriteOneByte(RTC_Address,0x0d,0x15);      //15年  
        I2CWriteOneByte(RTC_Address,0x0e,0x74);      //设置报警允许 
        I2CWriteOneByte(RTC_Address,0x10,0x92);      //INT中断选通 
        WriteTimeOff();
}

//关闭中断报警
void ClrALARM(void)                              
{
        WriteTimeOn();
        I2CWriteOneByte(RTC_Address,0x10,0x90);
        WriteTimeOff();
}

//设置倒计时中断程序
void SetDjs(void)                               
{
        WriteTimeOn();
        I2CWriteOneByte(RTC_Address,0x10,0x0f);  //清倒计时中断总允许位
        I2CWriteOneByte(RTC_Address,0x10,0xf4);  //(IM=1) INT(INTS1,INTS0),(INTDE)
        I2CWriteOneByte(RTC_Address,0x11,0x30);  //1/60HZ
        I2CWriteOneByte(RTC_Address,0x13,0x05);  //(5min)
        WriteTimeOff();
}

//关闭倒计时中断程序
void ClrDjs(void)          
{
        WriteTimeOn();
        I2CWriteOneByte(RTC_Address,0x10,0xf0);
        WriteTimeOff();
}

void SetFrq(void)                                        
{
        WriteTimeOn();
        I2CWriteOneByte(RTC_Address,0x10,0xa1);        //(INTS1,INTS0),(INTFE)
        I2CWriteOneByte(RTC_Address,0x11,0x09);        //2Hz
        WriteTimeOff();
}

void ClrFrq(void)         
{
        WriteTimeOn();
        I2CWriteOneByte(RTC_Address,0x10,0xa0);
        WriteTimeOff();
}

//连续读多个字节
void I2CReadSerial(uchar DeviceAddress, uchar Address, uchar length,uchar *ps)
{
        uchar    i;
        I2CStart();
				
        I2CSendByte(DeviceAddress);      
        I2CWaitAck();
				
        I2CSendByte(Address);                       
        I2CWaitAck();
        I2CStart();        
        I2CSendByte(DeviceAddress+1);
        I2CWaitAck();
        for(i=0;i<length-1;i++,ps++)
        {
            *ps=I2CReceiveByte();                
            I2CAck();
        }
        *ps=I2CReceiveByte();        
        I2CNoAck();
        I2CStop(); 
}

//连续写多个字节
void I2CWriteSerial(uchar DeviceAddress, uchar Address, uchar length,uchar *ps)
{
        uchar   i;
        WriteTimeOn();
				
        I2CStart();
				
        I2CSendByte(DeviceAddress);     
        I2CWaitAck();
				
        I2CSendByte(Address);                
        I2CWaitAck();
        for(i=0;i<length;i++)
        {
             I2CSendByte(*(ps++));                
             I2CAck();                                        
        }
        I2CStop(); 
        WriteTimeOff();
				return;
}

void GPIO_RTC_Init(void)
{
				I2C_SDA_OUT; 
				I2C_SCL_OUT;
}

void test_rtc_init()
{
				GPIO_RTC_Init();
        I2CWriteDate(RTC);        
//      WriteALARM();            
//      SetDjs();                        
        //SetFrq();                        
        
        //I2CReadSerial(RTC_Address,IDcode,8,Sram);                
        //I2CWriteSerial(RTC_Address,0x30,8,Sram);                
        
        //I2CReadSerial(RTC_Address,0x30,8,data1);                
        //Batbit8=I2CReadOneByte(RTC_Address,Bat_bit8);    //电量             
        //Batlow7=I2CReadOneByte(RTC_Address,Bat_Low8);              
        //Bat=(Batbit8>>7)*255+Batlow7;  
				//SEGGER_RTT_printf(0, "test_rtc_init\r\n");			
}

void test_rtc()
{       
			 SEGGER_RTT_printf(0, "test_rtc\r\n");		
			 I2CReadDate(&RTC);          
			 nrf_delay_ms(10000);                           
}
