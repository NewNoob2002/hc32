/******************** (C) COPYRIGHT 2010 KSGIANTLUS ********************
* File Name          : lcd.c
* Author             : JASON
* Version            : V1.0
* Date               : 2010.01.20
*************************************************************************/
/* Includes ------------------------------------------------------------------*/
#include "LCD.h"
#include "main.h"
///#include "fonts.h"
///#include "spi.h"

#define XDP 126
#define YDP 294

void LCD_WR_DATA8(uint8_t data)
{
	LCD_CS_CLR;
	LCD_RS_SET;
  spi_write_byte(data);
	LCD_CS_SET;
}

void LCD_WR_DATA(uint16_t data)
{
	LCD_WR_DATA8(data>>8);
    LCD_WR_DATA8(data);
}

void LCD_WR_REG(uint8_t data)
{
	LCD_CS_CLR;
	LCD_RS_CLR;
    spi_write_byte(data);
	LCD_CS_SET;
}

/**
 * @brief  LCD control initialize.
 * @param  None
 * @retval None
 */
void LCD_Control_Init(void)
{
    stc_gpio_init_t stcGpioInit;

    /* configuration structure initialization */
    (void)GPIO_StructInit(&stcGpioInit);
    stcGpioInit.u16PinDir = PIN_DIR_OUT;
    /* Initialize control pin */
    (void)GPIO_Init(LCD_PORT, LCDPin_RS, &stcGpioInit);
	  (void)GPIO_Init(LCD_PORT, LCDPin_RST, &stcGpioInit);
	  (void)GPIO_Init(LCD_PORT, GPIO_PIN_14, &stcGpioInit);
}

void LED_Init(void)
{
    stc_gpio_init_t stcGpioInit;

    /* configuration structure initialization */
    (void)GPIO_StructInit(&stcGpioInit);
    stcGpioInit.u16PinDir = PIN_DIR_OUT;	
    
	  (void)GPIO_Init(GPIO_PORT_C, GPIO_PIN_13, &stcGpioInit);
}	
	
void LED_ON(void)
{
	  GPIO_ResetPins(GPIO_PORT_C, GPIO_PIN_13);
}
void LED_OFF(void)
{
	  GPIO_SetPins(GPIO_PORT_C, GPIO_PIN_13);
}
/*******************************************************************************
* Function Name  : STM32_SSD1963_Init
* Description    : Initializes the SSD1963.
* Input          : None
* Output         : None
* Return         : None
*******************************************************************************/
void LCD_Simple_inition(void)
{
  /* Configure the LCD Control pins -LCD 相关控制端口初始化----------------------*/
		///SPI_Config();
	  DDL_DelayMS(50);
	  LCD_RST_SET;
	  DDL_DelayMS(50);
	  LCD_RST_CLR;
    LCD_CS_SET;	
    DDL_DelayMS(50);
	  LCD_RST_SET;
	  DDL_DelayMS(150);
	
		LCD_WR_REG(0xfe);			
		LCD_WR_DATA8(0x00);//CMD1 command
				
		LCD_WR_REG(0x2a);			
		LCD_WR_DATA8(0x00);
		LCD_WR_DATA8(0x00);
		LCD_WR_DATA8(0x00);
		LCD_WR_DATA8(0x7d);
				
		LCD_WR_REG(0x2b);			
		LCD_WR_DATA8(0x00);
		LCD_WR_DATA8(0x00);
		LCD_WR_DATA8(0x01);
		LCD_WR_DATA8(0x25);		
				
		LCD_WR_REG(0x35);			
		LCD_WR_DATA8(0x00);
			
		LCD_WR_REG(0x51);			
		LCD_WR_DATA8(0xff);
			
		LCD_WR_REG(0x3A);
		LCD_WR_DATA8(0x05);//默认888格式，看平台送数据格式，如果不是888格式就需要下3Ah

		LCD_WR_REG(0x11);		
		///Delay(150);//时间不能过短，否则刷屏会顿挫
		DDL_DelayMS(1500);
			
		LCD_WR_REG(0x29);			

		///LCD_CS(1);	
    LCD_CS_SET;
}

void LCD_SPI_SetDisplayWindow(u16 add_sx, u16 add_ex, u16 add_sy, u16 add_ey)
{            //此函数非常重要
  u16 sx= add_sx;
  u16 ex= add_ex;
  u16 sy= add_sy;
  u16 ey= add_ey;

	///LCD_CS(0);
	LCD_CS_CLR;
	LCD_WR_REG(0x2A); //Column Adress Setting
  LCD_WR_DATA8(sx>>8);
  LCD_WR_DATA8(sx);
  LCD_WR_DATA8(ex>>8);
  LCD_WR_DATA8(ex);// 
	///LCD_CS(1);
	LCD_CS_SET;

  //row start_end
	///LCD_CS(0);
	LCD_CS_CLR;
  LCD_WR_REG(0x2B); //Row Adress Setting 
  LCD_WR_DATA8(sy>>8);
  LCD_WR_DATA8(sy);
  LCD_WR_DATA8(ey>>8);
  LCD_WR_DATA8(ey);// 
	///LCD_CS(1);	
	LCD_CS_SET;
}

void LCD_SPI_WriteRAM_Prepare(void)
{//此函数非常重要
	///LCD_CS(0);
	LCD_CS_CLR;
  LCD_WR_REG(0x2c);
  ///LCD_CS(1);
	LCD_CS_SET;
}

void LCD_disp_frame(void)
{
	int ii,jj;
	
	LCD_SPI_SetDisplayWindow(0,(XDP-1),0,(YDP-1));
	LCD_SPI_WriteRAM_Prepare();
   
	for(ii=0;ii<YDP;ii++)
	{
	 	if(ii==0) 
	 	{
	 		for(jj=0;jj<XDP;jj++)	 LCD_WR_DATA(0xffff); 
	 	}
	 	else if(ii==(YDP-1))
	 	{
	 		for(jj=0;jj<XDP;jj++)	 LCD_WR_DATA(0xffff);	
	 	}
	      else
	      {
	      	for(jj=0;jj<XDP;jj++)	 
	      	{
	      		if(jj==0 )       		LCD_WR_DATA(0xffff);
	      		else if(jj==(XDP-1))  	LCD_WR_DATA(0xffff);    	      		
	      		else             		LCD_WR_DATA(0x0000);	
	      	}	
	      }
	}
   
}

void LCD_All_Color_16(u32 color)
{
  vu32 index =0 ;

  LCD_SPI_SetDisplayWindow(0,(XDP-1),0,(YDP-1));
  LCD_SPI_WriteRAM_Prepare();
 
  for(index = 0; index < (YDP*XDP); index++)
  {	
	   LCD_WR_DATA(color); 
  }
}

void  showpic_a(const u16 *bitmap)
{  
	vu32 index;
	vu32 size = XDP * YDP;
	u16 *bitmap_ptr = (u16 *)bitmap;
	u16 point,point1,point2;
	//	u8 rr,gg,bb;
	u16 color,color1;
	
	LCD_SPI_SetDisplayWindow(0,XDP-1,0,YDP-1);
	LCD_SPI_WriteRAM_Prepare();
	
	for(index = 0; index < size; index++)
	{
		point=*bitmap_ptr++;
		point1=*bitmap_ptr++;
		point2=*bitmap_ptr++;
		color=((point&0xf8)<<8)+((point1&0xe0)<<3);
		color1=((point2&0xf8)>>3)+((point1&0x1c)<<3);
		LCD_WR_DATA(color+color1);		
		//  W_DATA(point); 
	}
}

void LCD_DrawPoint(u32 point)  //向Display RAM 写入1点的数据，此函数与“LCD_WriteRAM_Prepare”配合使用
{ //此函数非常重要
	u8 rr,gg,bb;
	u16 color,color1;
	
  rr=(point>>16);  
  gg=(point>>8);  
  bb=point;
  color=((rr&0xf8)<<8)+((gg&0xe0)<<3);
  color1=((bb&0xf8)>>3)+((gg&0x1c)<<3);
  LCD_WR_DATA(color+color1);
}

void DrawPoint(u16 x, u16 y, u32 color) {
    if (x >= SCREEN_WIDTH || y >= SCREEN_HEIGHT) {
        return; //
    }

    LCD_SPI_SetDisplayWindow(x, x, y, y);

    LCD_SPI_WriteRAM_Prepare();

    LCD_DrawPoint(color);
}
#if 0
void LCD_Write_DisplayWindow(int x, int y, u32 color)
{
   LCD_SPI_SetDisplayWindow(x,x,y,y);
   LCD_SPI_WriteRAM_Prepare();
   LCD_DrawPoint(color);
}

void LCD_Draw_Color_fill(int x1, int y1, int x2, int y2, u32 color)
{
  vu32 index =0 ;
	int x, y;

	x = x2 - x1;
	y = y2 - y1;
	
  LCD_SPI_SetDisplayWindow(x1, x2, y1, y2);
  LCD_SPI_WriteRAM_Prepare();
 
  for(index = 0; index < (x*y); index++)
  {	
	   LCD_WR_DATA(color); 
  }
}
#endif