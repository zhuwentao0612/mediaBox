/**
---------------------------------------------------------------------
**
**  This device driver was created by 
**  8-Bit Single-Chip Microcontrollers
**
**  Copyright(C) visionox display Corporation 2002 - 2009
**  All rights reserved by Kunshan visionox display Corporation.
**
**  This program should be used on your own responsibility.
**
**  Filename :	Display_Mode.c
**  Abstract :	This file implements device driver for Display_Mode function.
**
**  Device :	STC89LE516RD
**
**  Compiler :	KEIL uVision2 
**
**  Module:  M01120
**
**  Dot Matrix: 96*32
**
**  Display Color: White
**
**  Driver IC: SH1106G
**
**  Edit : 
**
**  Creation date:	2012-08-16
---------------------------------------------------------------------
**/

#include "oled_display.h"
#include "oled.h"

//
//

extern uint8_t ROW[3][4];

/******************************************************
//
//清屏显示模式
//
******************************************************/
//
//

void Clear_Screen_Display()
{
   uint8_t page_number,column_number;
   for(page_number=MIN;page_number<PAGE_TOTAL/2;page_number++)
   {
     Write_Command(START_PAGE+page_number);
     Write_Command(START_HIGH_BIT);
     Write_Command(START_LOW_BIT);
     for(column_number=MIN;column_number<COLUMN_MAX;column_number++)
     {
        Write_Data(STATE_MIN);
     }
   }
}

/******************************************************
//
//全屏显示模式
//
******************************************************/
//
//

void All_Screen_Display()
{
   uint8_t page_number,column_number;
   for(page_number=MIN;page_number<PAGE_TOTAL/2;page_number++)
   {
     Write_Command(START_PAGE+page_number);
     Write_Command(START_HIGH_BIT);
     Write_Command(START_LOW_BIT);
//	 Delay_s(50);
     for(column_number=MIN;column_number<COLUMN_MAX;column_number++)
     {	   
        Write_Data(STATE_MAX);
     }
   }
}

/******************************************************
//
//隔行135显示模式
//
******************************************************/
//
//

void Row_Show135()
{
   uint8_t page_number,column_number;
   for(page_number=MIN;page_number<PAGE_TOTAL/2;page_number++)
   {
     Write_Command(START_PAGE+page_number);
     Write_Command(START_HIGH_BIT);
     Write_Command(START_LOW_BIT);

     for(column_number=MIN;column_number<COLUMN_MAX;column_number++)
     {
        Write_Data(STATE_55);
     }
   }
}

/******************************************************
//
//隔行246显示模式
//
******************************************************/
//
//

void Row_Show246()
{
   uint8_t page_number,column_number;
   for(page_number=MIN;page_number<PAGE_TOTAL/2;page_number++)
   {
     Write_Command(START_PAGE+page_number);
     Write_Command(START_HIGH_BIT);
     Write_Command(START_LOW_BIT);
     for(column_number=MIN;column_number<COLUMN_MAX;column_number++)
     {
        Write_Data(STATE_AA);
     }
   }
}


/******************************************************
//
//隔列135显示模式
//
******************************************************/
//
//

void Column_Show135()
{
   uint8_t page_number,column_number;
   for(page_number=MIN;page_number<PAGE_TOTAL/2;page_number++)
   {
     Write_Command(START_PAGE+page_number);
     Write_Command(START_HIGH_BIT);
     Write_Command(START_LOW_BIT);
     for(column_number=MIN;column_number<(COLUMN_MAX/2);column_number++)
     {
        Write_Data(STATE_MAX);
        Write_Data(STATE_MIN);
     }
   }
}

/******************************************************
//
//隔列246显示模式
//
******************************************************/
//
//

void Column_Show246()
{
   uint8_t page_number,column_number;
   for(page_number=MIN;page_number<PAGE_TOTAL/2;page_number++)
   {
     Write_Command(START_PAGE+page_number);
     Write_Command(START_HIGH_BIT);
     Write_Command(START_LOW_BIT);
     for(column_number=MIN;column_number<(COLUMN_MAX/2);column_number++)
     {
        Write_Data(STATE_MIN);
        Write_Data(STATE_MAX);
     }
   }
}
 /******************************************************
//
//隔列147显示模式
//
******************************************************/
//
//

void Column_Show147()
{
   uint8_t page_number,column_number;
   for(page_number=MIN;page_number<PAGE_TOTAL/2;page_number++)
   {
     Write_Command(START_PAGE+page_number);
     Write_Command(START_HIGH_BIT);
     Write_Command(START_LOW_BIT);
     for(column_number=MIN;column_number<42;column_number++)
     {
        Write_Data(STATE_MAX);
        Write_Data(STATE_MIN);
		Write_Data(STATE_MIN);
     }
	    Write_Data(STATE_MAX);
        Write_Data(STATE_MIN);
   }
}
/******************************************************
//
//隔列258显示模式
//
******************************************************/
//
//

void Column_Show258()
{
   uint8_t page_number,column_number;
   for(page_number=MIN;page_number<PAGE_TOTAL/2;page_number++)
   {
     Write_Command(START_PAGE+page_number);
     Write_Command(START_HIGH_BIT);
     Write_Command(START_LOW_BIT);
     for(column_number=MIN;column_number<42;column_number++)
     {
	    Write_Data(STATE_MIN);
        Write_Data(STATE_MAX);
        Write_Data(STATE_MIN);
	
     }
	   Write_Data(STATE_MIN);
        Write_Data(STATE_MAX);
   }
}
/******************************************************
//
//隔列369显示模式
//
******************************************************/
//
//

void Column_Show369()
{
   uint8_t page_number,column_number;
   for(page_number=MIN;page_number<PAGE_TOTAL/2;page_number++)
   {
     Write_Command(START_PAGE+page_number);
     Write_Command(START_HIGH_BIT);
     Write_Command(START_LOW_BIT);
     for(column_number=MIN;column_number<42;column_number++)
     {
	    Write_Data(STATE_MIN);
	    Write_Data(STATE_MIN);
        Write_Data(STATE_MAX);
       
	
     }
	 Write_Data(STATE_MIN);
	 Write_Data(STATE_MIN);
   }
}
/******************************************************
//
//边框显示模式128*36
//
******************************************************/
//
//
uint8_t tab_jian[2][16] = {
{0x00,0x00,0x1F,0xFF,0x80,0x00,0x60,0x00,0x00,0x00,0x0F,0xF8,0x48,0x88,0x48,0x88},
{0x48,0x88,0x4F,0xF8,0x40,0x00,0x40,0x02,0x40,0x01,0x7F,0xFE,0x00,0x00,0x00,0x00}/*"间",0*/
};

uint8_t tab_shi[2][16] = {
{0x00,0x08,0x00,0x08,0x7C,0x08,0x44,0x08,0x45,0xFE,0x44,0x08,0x44,0x08,0x7C,0x08},
{0x44,0x88,0x44,0x48,0x44,0x48,0x44,0x08,0x7C,0x08,0x44,0x08,0x00,0x28,0x00,0x10}/*"时",1*/
};

uint8_t tab_22[16] = {0x00,0x00,0x00,0x3C,0x66,0x66,0x06,0x0C,0x18,0x30,0x60,0x7E,0x00,0x00,0x00,0x00};/*"2",0*/

uint8_t tab_44[16] = {0x00,0x00,0x00,0x30,0x30,0x36,0x36,0x36,0x66,0x7F,0x06,0x06,0x00,0x00,0x00,0x00};/*"4",1*/

uint8_t tab_22_1[16] = {0x00,0x00,0x0C,0x30,0x0E,0x38,0x0B,0x08,0x09,0x88,0x08,0xF8,0x08,0x70,0x00,0x00};/*"2",0*/

uint8_t tab_44_1[16] = {0x00,0x00,0x1F,0x1F,0x00,0x07,0x07,0x00, 0x00,0xC0,0xC0,0x40,0x40,0xF0,0xF0,0x40};/*"4",1*/

void show_24_1(){
	  uint8_t page_number,column_number;
		Write_Command(START_PAGE);
		Write_Command(START_HIGH_BIT);
		Write_Command(START_LOW_BIT);
		for(column_number = MIN;column_number<COLUMN_MAX;column_number++)
		{
				if(column_number<8)
				{
					Write_Data(tab_22_1[column_number]);
				}else if(column_number<36 && column_number>=20 ){
					Write_Data(tab_44_1[column_number-20]);
				}else{
					Write_Data(STATE_MIN);
				}
		}
		
		Write_Command(START_PAGE+1);
		Write_Command(START_HIGH_BIT);
		Write_Command(START_LOW_BIT);
		for(column_number = MIN;column_number<COLUMN_MAX;column_number++)
		{
				if(column_number<8)
				{
					Write_Data(tab_22_1[column_number+8]);
				}else if(column_number<36 && column_number>=20 ){
					Write_Data(tab_44_1[column_number-20+8]);
				}else{
					Write_Data(STATE_MIN);
				}
		}
		
		for(page_number=MIN+2;page_number<PAGE_TOTAL/2;page_number++)
		{
				Write_Command(START_PAGE+page_number);
				Write_Command(START_HIGH_BIT);
				Write_Command(START_LOW_BIT);
				//Write_Data(STATE_MAX);
				for(column_number=MIN;column_number<(COLUMN_MAX-2);column_number++)
				{
						Write_Data(STATE_MIN);
				}
				//Write_Data(STATE_MAX);
		}
}

void show_24(){
	  uint8_t page_number,column_number;
		Write_Command(START_PAGE);
		Write_Command(START_HIGH_BIT);
		Write_Command(START_LOW_BIT);
		for(column_number = MIN;column_number<COLUMN_MAX;column_number++)
		{
				if(column_number<16)
				{
					Write_Data(tab_22[column_number]);
				}else if(column_number<36 && column_number>=20 ){
					Write_Data(tab_44[column_number-20]);
				}else{
					Write_Data(STATE_MIN);
				}
		}
		
		Write_Command(START_PAGE+1);
		Write_Command(START_HIGH_BIT);
		Write_Command(START_LOW_BIT);
		for(column_number = MIN;column_number<COLUMN_MAX;column_number++)
		{
				if(column_number<16)
				{
					Write_Data(tab_22[column_number]);
				}else if(column_number<36 && column_number>=20 ){
					Write_Data(tab_44[column_number-20]);
				}else{
					Write_Data(STATE_MIN);
				}
		}
		
		for(page_number=MIN+2;page_number<PAGE_TOTAL/2;page_number++)
		{
				Write_Command(START_PAGE+page_number);
				Write_Command(START_HIGH_BIT);
				Write_Command(START_LOW_BIT);
				//Write_Data(STATE_MAX);
				for(column_number=MIN;column_number<COLUMN_MAX;column_number++)
				{
						Write_Data(STATE_MIN);
				}
				//Write_Data(STATE_MAX);
		}
}

void show_shijian(){
	  uint8_t page_number,column_number;
		Write_Command(START_PAGE);
		Write_Command(START_HIGH_BIT);
		Write_Command(START_LOW_BIT);
		for(column_number = MIN;column_number<COLUMN_MAX;column_number++)
		{
				if(column_number<16)
				{
					Write_Data(tab_shi[0][column_number]);
				}else if(column_number<36 && column_number>=20 ){
					Write_Data(tab_jian[0][column_number-20]);
				}else{
					Write_Data(STATE_MIN);
				}
		}
		
		Write_Command(START_PAGE+1);
		Write_Command(START_HIGH_BIT);
		Write_Command(START_LOW_BIT);
		for(column_number = MIN;column_number<COLUMN_MAX;column_number++)
		{
				if(column_number<16)
				{
					Write_Data(tab_shi[1][column_number]);
				}else if(column_number<36 && column_number>=20 ){
					Write_Data(tab_jian[1][column_number-20]);
				}else{
					Write_Data(STATE_MIN);
				}
		}
		
		for(page_number=MIN+2;page_number<PAGE_TOTAL/2;page_number++)
		{
				Write_Command(START_PAGE+page_number);
				Write_Command(START_HIGH_BIT);
				Write_Command(START_LOW_BIT);
				//Write_Data(STATE_MAX);
				for(column_number=MIN;column_number<(COLUMN_MAX-2);column_number++)
				{
						Write_Data(STATE_MIN);
				}
				//Write_Data(STATE_MAX);
		}
}

void Frame_Show()
{
   uint8_t page_number,column_number;
   Write_Command(START_PAGE);
   Write_Command(START_HIGH_BIT);
   Write_Command(START_LOW_BIT);
   Write_Data(STATE_MAX);
   for(column_number=MIN;column_number<(COLUMN_MAX-2);column_number++)
   {
      Write_Data(FRAME_HIGH_ROW);
   }
   Write_Data(STATE_MAX);
  
	 for(page_number=MIN+1;page_number<PAGE_TOTAL/2;page_number++)
   {
     Write_Command(START_PAGE+page_number);
     Write_Command(START_HIGH_BIT);
     Write_Command(START_LOW_BIT);
     Write_Data(STATE_MAX);
     for(column_number=MIN;column_number<(COLUMN_MAX-2);column_number++)
     {
        Write_Data(STATE_MIN);
     }
     Write_Data(STATE_MAX);
   }
  
	 Write_Command(START_PAGE+3);
   Write_Command(START_HIGH_BIT);
   Write_Command(START_LOW_BIT);
   Write_Data(STATE_MAX);
   for(column_number=MIN;column_number<(COLUMN_MAX-2);column_number++)
   {
      Write_Data(FRAME_LOW_ROW);
   }
   Write_Data(STATE_MAX);
}

//
//

/******************************************************
//
//棋盘格1
//
******************************************************/
//
//

void Chess_Board1()
{
   uint8_t page_number,column_number_1,column_number_2,board;
   board=0xFF;
   for(page_number=MIN;page_number<PAGE_TOTAL/2;page_number++)
   {
	  Write_Command(START_PAGE+page_number);
      Write_Command(START_HIGH_BIT);
      Write_Command(START_LOW_BIT);
	  for(column_number_1=MIN;column_number_1<COLUMN_MAX/8;column_number_1++)
	  {
		 for(column_number_2=MIN;column_number_2<COLUMN_MAX/16;column_number_2++)
	     {
	   	    Write_Data(board);
		 }
         board=~board;
	  }
	  board=~board;
   }
}	

/******************************************************
//
//棋盘格2
//
******************************************************/
//
//

void Chess_Board2()
{
   uint8_t page_number,column_number_1,column_number_2,board;
   board=0x00;
   for(page_number=MIN;page_number<PAGE_TOTAL/2;page_number++)
   {
	  Write_Command(START_PAGE+page_number);
      Write_Command(START_HIGH_BIT);
      Write_Command(START_LOW_BIT);
	  for(column_number_1=MIN;column_number_1<COLUMN_MAX/8;column_number_1++)
	  {
		 for(column_number_2=MIN;column_number_2<COLUMN_MAX/16;column_number_2++)
	     {
	   	    Write_Data(board);
		 }
         board=~board;
	  }
	  board=~board;
   }
}

/******************************************************
//
//列扫描显示模式
//
******************************************************/
//
//

void Column_Scan()
{
   uint8_t page_number,column_number_1,column_number_2;
   for(column_number_1=MIN;column_number_1<COLUMN_MAX;column_number_1++)
   {
      for(page_number=MIN;page_number<PAGE_TOTAL/2;page_number++)
      {
         Write_Command(START_PAGE+page_number);
         Write_Command(START_HIGH_BIT);
         Write_Command(START_LOW_BIT);
         for(column_number_2=MIN;column_number_2<COLUMN_MAX;column_number_2++)
         {
		    if(column_number_2==column_number_1)
		    Write_Data(STATE_MAX);
		    else Write_Data(STATE_MIN);
		 }
      } 
      nrf_delay_ms(60);
   }
}

//
//
/******************************************************
//
//程序版本信息
//
******************************************************/
//
//

void Program_Edit()
{
   uint8_t page_number,column_number;
   int piexl=MIN;
   for(page_number=MIN;page_number<PAGE_TOTAL/2;page_number++)
   {
      Write_Command(START_PAGE+page_number);
      Write_Command(START_HIGH_BIT);
      Write_Command(START_LOW_BIT);
      for(column_number=MIN;column_number<COLUMN_MAX;column_number++)
      {
		 Write_Data(tab_1[piexl]);
		 piexl++;
	  }
  }
} 
//
//
/******************************************************
//
//图片检测函数
//
******************************************************/
//
//
void Photo_Show1()
{
   uint8_t page_number,column_number;
   int piexl=MIN;
   for(page_number=MIN;page_number<PAGE_TOTAL/2;page_number++)
   {
      Write_Command(START_PAGE+page_number);
      Write_Command(START_HIGH_BIT);
      Write_Command(START_LOW_BIT);
      for(column_number=MIN;column_number<COLUMN_MAX;column_number++)
      {
		 Write_Data(tab_1[piexl]);
		 piexl++;
	  }
  }
}
void Photo_Show2()
{
   uint8_t page_number,column_number;
   int piexl=MIN;
   for(page_number=MIN;page_number<PAGE_TOTAL/2;page_number++)
   {
      Write_Command(START_PAGE+page_number);
      Write_Command(START_HIGH_BIT);
      Write_Command(START_LOW_BIT);
      for(column_number=MIN;column_number<COLUMN_MAX;column_number++)
      {
		 Write_Data(tab_2[piexl]);
		 piexl++;
	  }
  }
}

void Photo_Show3()
{
   uint8_t page_number,column_number;
   int piexl=MIN;
   for(page_number=MIN;page_number<PAGE_TOTAL/2;page_number++)
   {
      Write_Command(START_PAGE+page_number);
      Write_Command(START_HIGH_BIT);
      Write_Command(START_LOW_BIT);
      for(column_number=MIN;column_number<COLUMN_MAX;column_number++)
      {
		 Write_Data(tab_3[piexl]);
		 piexl++;
	  }
  }
}
void Photo_Show4()
{
   uint8_t page_number,column_number;
   int piexl=MIN;
   for(page_number=MIN;page_number<PAGE_TOTAL/2;page_number++)
   {
      Write_Command(START_PAGE+page_number);
      Write_Command(START_HIGH_BIT);
      Write_Command(START_LOW_BIT);
      for(column_number=MIN;column_number<COLUMN_MAX;column_number++)
      {
		 Write_Data(tab_4[piexl]);
		 piexl++;
	  }
  }
}
void Photo_Show5()
{
   uint8_t page_number,column_number;
   int piexl=MIN;
   for(page_number=MIN;page_number<PAGE_TOTAL/2;page_number++)
   {
      Write_Command(START_PAGE+page_number);
      Write_Command(START_HIGH_BIT);
      Write_Command(START_LOW_BIT);
      for(column_number=MIN;column_number<COLUMN_MAX;column_number++)
      {
		 Write_Data(tab_5[piexl]);
		 piexl++;
	  }
  }
}
void Photo_Show6()
{
   uint8_t page_number,column_number;
   int piexl=MIN;
   for(page_number=MIN;page_number<PAGE_TOTAL/2;page_number++)
   {
      Write_Command(START_PAGE+page_number);
      Write_Command(START_HIGH_BIT);
      Write_Command(START_LOW_BIT);
      for(column_number=MIN;column_number<COLUMN_MAX;column_number++)
      {
		 Write_Data(tab_6[piexl]);
		 piexl++;
       }
  }
}
void Photo_Show7()
{
   uint8_t page_number,column_number;
   int piexl=MIN;
   for(page_number=MIN;page_number<PAGE_TOTAL/2;page_number++)
   {
      Write_Command(START_PAGE+page_number);
      Write_Command(START_HIGH_BIT);
      Write_Command(START_LOW_BIT);
      for(column_number=MIN;column_number<COLUMN_MAX;column_number++)
      {
		 Write_Data(tab_7[piexl]);
		 piexl++;
	  }
  }
}
void Photo_Show8()
{
   uint8_t page_number,column_number;
   int piexl=MIN;
   for(page_number=MIN;page_number<PAGE_TOTAL/2;page_number++)
   {
      Write_Command(START_PAGE+page_number);
      Write_Command(START_HIGH_BIT);
      Write_Command(START_LOW_BIT);
      for(column_number=MIN;column_number<COLUMN_MAX;column_number++)
      {
		 Write_Data(tab_8[piexl]);
		 piexl++;
	  }
  }
}
void Photo_Show9()
{
   uint8_t page_number,column_number;
   int piexl=MIN;
   for(page_number=MIN;page_number<PAGE_TOTAL/2;page_number++)
   {
      Write_Command(START_PAGE+page_number);
      Write_Command(START_HIGH_BIT);
      Write_Command(START_LOW_BIT);
      for(column_number=MIN;column_number<COLUMN_MAX;column_number++)
      {
		 Write_Data(tab_9[piexl]);
		 piexl++;
	  }
  }
}
void Photo_Show10()
{
   uint8_t page_number,column_number;
   int piexl=MIN;
   for(page_number=MIN;page_number<PAGE_TOTAL/2;page_number++)
   {
      Write_Command(START_PAGE+page_number);
      Write_Command(START_HIGH_BIT);
      Write_Command(START_LOW_BIT);
      for(column_number=MIN;column_number<COLUMN_MAX;column_number++)
      {
		 Write_Data(tab_10[piexl]);
		 piexl++;
	  }
  }
}
void Photo_Show11()
{
   uint8_t page_number,column_number;
   int piexl=MIN;
   for(page_number=MIN;page_number<PAGE_TOTAL/2;page_number++)
   {
      Write_Command(START_PAGE+page_number);
      Write_Command(START_HIGH_BIT);
      Write_Command(START_LOW_BIT);
      for(column_number=MIN;column_number<COLUMN_MAX;column_number++)
      {
		 Write_Data(tab_11[piexl]);
		 piexl++;
	  }
  }
}
void Photo_Show12()
{
   uint8_t page_number,column_number;
   int piexl=MIN;
   for(page_number=MIN;page_number<PAGE_TOTAL/2;page_number++)
   {
      Write_Command(START_PAGE+page_number);
      Write_Command(START_HIGH_BIT);
      Write_Command(START_LOW_BIT);
      for(column_number=MIN;column_number<COLUMN_MAX;column_number++)
      {
		 Write_Data(tab_12[piexl]);
		 piexl++;
	  }
  }
}



