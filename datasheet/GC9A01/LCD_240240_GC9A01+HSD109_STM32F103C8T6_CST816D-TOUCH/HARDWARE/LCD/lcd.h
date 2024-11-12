//******************************************************************************/
/////////////////////////////////////////////////////////////////////////////////////
//  深圳市沃乐康科技有限公司  WWW.WLKLCD.COM  0755-32882855   专业液晶显示供应商   //
//  LCD显示头文件 （定义用户配置参数）                                           //
//  触摸芯片 CST816D GPIO 模拟IIC                                                  //
//  https://wlklcd.1688.com/     https://shop341012592.taobao.com/                //
//  例程仅供学习参考，不做量产使用，不得用于商业用途                                 //
//*********************************************************************************/
// --------------接口连线-----------------------------------
//     --        GND     电源地
//     显        VCC     3.3v电源
//               SCK     PA5  SPI时钟信号
//     示        SDA     PA7  SPI数据信号
//               RES     PA0  复位脚
//     接        DC      PA1  数据指令选择脚
//     口        CS      PA2  片选
//		 --			   BLC     PA3  控制背光
//     ------------------------------------------------------
//     触        SDA     PB6  触摸IIC 数据线
//     摸        SCL     PB7  触摸IIC 时钟线
//     接        RST     PB4  触摸复位脚
//     口        INT     PB5  触摸中断
// ----------------------------------------------------------------
//******************************************************************************/


#ifndef __LCD_H
#define __LCD_H

#include "sys.h"
#include "stdlib.h"

#define USE_HORIZONTAL 0 //设置横屏或者竖屏显示 0或1为竖屏 2或3为横屏

#if USE_HORIZONTAL == 0 || USE_HORIZONTAL == 1
#define LCD_W 240
#define LCD_H 240

#else
#define LCD_W 240
#define LCD_H 240
#endif

#define u8 unsigned char
#define u16 unsigned int
#define u32 unsigned long

//-----------------测试LED端口定义----------------

#define LED_ON GPIO_ResetBits(GPIOD, GPIO_Pin_2)
#define LED_OFF GPIO_SetBits(GPIOD, GPIO_Pin_2)

//-----------------TFT端口定义----------------
#define LCD_SCLK_Clr() GPIO_ResetBits(GPIOA,GPIO_Pin_5)//SCL
#define LCD_SCLK_Set() GPIO_SetBits(GPIOA,GPIO_Pin_5)

#define LCD_SDIN_Clr() GPIO_ResetBits(GPIOA,GPIO_Pin_7)//DIN
#define LCD_SDIN_Set() GPIO_SetBits(GPIOA,GPIO_Pin_7)

#define LCD_RST_Clr() GPIO_ResetBits(GPIOA,GPIO_Pin_0)//RES
#define LCD_RST_Set() GPIO_SetBits(GPIOA,GPIO_Pin_0)

#define LCD_DC_Clr() GPIO_ResetBits(GPIOA,GPIO_Pin_1)//DC     
#define LCD_DC_Set() GPIO_SetBits(GPIOA,GPIO_Pin_1)
 		     
#define LCD_CS_Clr()  GPIO_ResetBits(GPIOA,GPIO_Pin_2)//CS
#define LCD_CS_Set()  GPIO_SetBits(GPIOA,GPIO_Pin_2)

#define LCD_BLK_Clr()  GPIO_ResetBits(GPIOA,GPIO_Pin_3)//BLK    
#define LCD_BLK_Set()  GPIO_SetBits(GPIOA,GPIO_Pin_3)


#define LCD_CMD 0  //写命令
#define LCD_DATA 1 //写数据

extern u16 BACK_COLOR; //背景色

void LCD_Writ_Bus(u8 dat);
void LCD_WR_DATA8(u8 dat);
void LCD_WR_DATA(u16 dat);
void LCD_WR_REG(u8 dat);
void LCD_Address_Set(u16 x1, u16 y1, u16 x2, u16 y2);
void Hardware_SPI_Init(void);
void STM_Port_Init(void);
void Lcd_Init(void);
void LCD_Clear(u16 Color);
void LCD_ShowChinese(u16 x, u16 y, u8 index, u8 size, u16 color);
void LCD_DrawPoint(u16 x, u16 y, u16 color);
void LCD_DrawPoint_big(u16 x, u16 y, u16 color);
void LCD_Fill(u16 xsta, u16 ysta, u16 xend, u16 yend, u16 color);
void LCD_DrawLine(u16 x1, u16 y1, u16 x2, u16 y2, u16 color);
void LCD_DrawRectangle(u16 x1, u16 y1, u16 x2, u16 y2, u16 color);
void Draw_Circle(u16 x0, u16 y0, u8 r, u16 color);
// void LCD_ShowChar(u16 x,u16 y,u8 num,u8 mode,u16 color);
void LCD_ShowString(u16 x, u16 y, const u8 *p, u16 color);
u32 mypow(u8 m, u8 n);
void LCD_ShowNum(u16 x, u16 y, u16 num, u8 len, u16 color);
void LCD_ShowNum1(u16 x, u16 y, float num, u8 len, u16 color);
void LCD_ShowPicture(u16 x1, u16 y1, u16 x2, u16 y2);

//画笔颜色
#define WHITE 0xFFFF
#define BLACK 0x0000
#define BLUE 0x001F
#define BRED 0XF81F
#define GRED 0XFFE0
#define GBLUE 0X07FF
#define RED 0xF800
#define MAGENTA 0xF81F
#define GREEN 0x07E0
#define CYAN 0x7FFF
#define YELLOW 0xFFE0
#define BROWN 0XBC40 //棕色
#define BRRED 0XFC07 //棕红色
#define GRAY 0X8430  //灰色
// GUI颜色

#define DARKBLUE 0X01CF  //深蓝色
#define LIGHTBLUE 0X7D7C //浅蓝色
#define GRAYBLUE 0X5458  //灰蓝色
//以上三色为PANEL的颜色

#define LIGHTGREEN 0X841F //浅绿色
#define LGRAY 0XC618      //浅灰色(PANNEL),窗体背景色

#define LGRAYBLUE 0XA651 //浅灰蓝色(中间层颜色)
#define LBBLUE 0X2B12    //浅棕蓝色(选择条目的反色)

#endif
