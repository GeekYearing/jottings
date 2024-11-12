/////////////////////////////////////////////////////////////////////////////////////
//  深圳市沃乐康科技有限公司  WWW.WLKLCD.COM  0755-32882855   专业液晶显示供应商      //
//  触摸头文件 （4线SPI GC9A01A+1.09ips圆屏-240*240 SPI1 @STM32F103C8T6 MDK5.14）   //
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
#ifndef __CST816_H_
#define __CST816_H_

#include "sys.h"

#define SDA_IN()                  \
	{                             \
		GPIOB->CRL &= 0X0FFFFFFF; \
		GPIOB->CRL |= 0X40000000; \
	} //输入模式，浮空输入模式
#define SDA_OUT()                 \
	{                             \
		GPIOB->CRL &= 0X0FFFFFFF; \
		GPIOB->CRL |= 0X10000000; \
	} //通用推挽输出，输出速度50MHZ

#define TP_PRES_DOWN 0x81 //触屏被按下
#define TP_COORD_UD 0x40  //触摸坐标更新标记

//触摸点相关数据结构体定义
typedef struct
{
	u8 TouchSta; //触摸情况，b7:按下1/松开0; b6:0没有按键按下/1有按键按下;bit5:保留；bit4-bit0触摸点按下有效标志，有效为1，分别对应触摸点5-1；
	u16 x[5];	 //支持5点触摸，需要使用5组坐标存储触摸点数据
	u16 y[5];

} TouchPointRefTypeDef;
extern TouchPointRefTypeDef TPR_Structure;

/*********************IO操作函数*********************/
#define CST816_RST PBout(4)		//用在输出模式
#define CST816_SCL PBout(7)		//用在输出模式
#define CST816_SDA PBout(6)		//用在输出模式
#define CST816_SDA_Read PBin(6) //用在输入模式
#define CST816_INT PBin(5)		//用在输入模式


// I2C读写命令
#define FT_CMD_WR 0X2A //写命令
#define FT_CMD_RD 0X2B //读命令
// CST816 部分寄存器定义
#define FT_DEVIDE_MODE 0x00	   // CST816模式控制寄存器
#define FT_REG_NUM_FINGER 0x02 //触摸状态寄存器

#define FT_TP1_REG 0X03 //第一个触摸点数据地址
#define FT_TP2_REG 0X09 //第二个触摸点数据地址
#define FT_TP3_REG 0X0F //第三个触摸点数据地址
#define FT_TP4_REG 0X15 //第四个触摸点数据地址
#define FT_TP5_REG 0X1B //第五个触摸点数据地址

#define FT_ID_G_LIB_VERSION 0xA1  //版本
#define FT_ID_G_MODE 0xA4		  // CST816中断模式控制寄存器
#define FT_ID_G_THGROUP 0x80	  //触摸有效值设置寄存器
#define FT_ID_G_PERIODACTIVE 0x88 //激活状态周期设置寄存器
#define Chip_Vendor_ID 0xA7		  //芯片ID(0x36)
#define ID_G_CST816ID 0xA8		  // 0x11

u8 CST816_WR_Reg(u16 reg, u8 *buf, u8 len);
void CST816_RD_Reg(u16 reg, u8 *buf, u8 len);
void CST816_Init(void);
void CST816_Scan(void);

#endif
