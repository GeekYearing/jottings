/////////////////////////////////////////////////////////////////////////////////////
//  深圳市沃乐康科技有限公司  WWW.WLKLCD.COM  0755-32882855   专业液晶显示供应商   //
//  主程序 （4线SPI GC9A01A+1.09ips圆屏-240*240 SPI1 @STM32F103C8T6 MDK5.14）      //
//  触摸芯片 CST816D GPIO 模拟IIC                                                  //
//  https://wlklcd.1688.com/     https://shop341012592.taobao.com/                //
//  例程仅供学习参考，不做量产使用，不得用于商业用途                              //
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
#include "CST816.h"
#include "delay.h"
#include "sys.h"
#include "usart.h"
#include "bsp_i2c_gpio.h"
#include "delay.h"
#include "sys.h"
#include "lcd.h"

int main(void)
{
	
	u8 lx=0,ly=0;
	
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2); // 设置中断优先级分组2
	delay_init();									//延时函数初始化
	uart_init(115200);								//串口1初始化,波特率为115200
	i2c_CfgGpio();
	CST816_Init(); // CST816初始化
	Lcd_Init();	   //初始化
	LCD_Clear(WHITE);
	BACK_COLOR = WHITE;
	LCD_Clear(RED);
	
	
	//	CST816_Scan();						//读取触摸坐标
	//	CST816_RD_Reg(0xA7, &sta, 1); //读取触摸点的状态
	//	LCD_ShowNum(10,10,sta,4,BLACK);
	
	
	while (1)
	{
		
	//	LCD_Clear(WHITE);
	//	LCD_Fill(0,0,10,10,BLUE);
	//	LCD_Fill(230,230,240,240,GREEN);
	// LCD_Fill(115,115,125,125,RED);
	//		while(1)
	//		{
				CST816_Scan();
	//		if(TPR_Structure.x[0]!=0)lx=TPR_Structure.x[0];
	//		if(TPR_Structure.y[0]!=0)ly=TPR_Structure.y[0];
	//		if(TPR_Structure.x[0]>0||TPR_Structure.y[0]>0)
	//		printf("%d   %d\r\n",lx,ly);
	//		LCD_ShowNum(82,80,lx,3,BLACK);
	//		LCD_ShowNum(82,100,ly,3,BLACK);
	//		}
		
		
		if (TPR_Structure.TouchSta == TP_PRES_DOWN) //触摸有按下
		{
			printf("X:  %d  Y:  %d\r\n", TPR_Structure.x[0], TPR_Structure.y[0]);
			LCD_DrawPoint_big(TPR_Structure.x[0], TPR_Structure.y[0], WHITE);
			LCD_ShowString(100, 120, "X:", BLACK);
			LCD_ShowString(100, 138, "Y:", BLACK);
				LCD_ShowNum(120, 120,TPR_Structure.x[0],3,BLACK);
			  LCD_ShowNum(120, 138,TPR_Structure.y[0],3,BLACK);
		}
	}
}




















/////////////////////////////////////////////////////////////////////////////////////
//  深圳市沃乐康科技有限公司  WWW.WLKLCD.COM  0755-32882855   专业液晶显示供应商   //
//  主程序 （4线SPI ST7789+154-240*240 SPI1 @STM32F103C8T6 MDK5.14）               //
//  https://wlklcd.1688.com/     https://shop341012592.taobao.com/                 //
//  例程仅供学习参考，不做量产使用，不得用于商业用途                              //
//*********************************************************************************/
// --------------接口连线-----------------------------------
//     --        GND     电源地
//     显        VCC     3.3v电源
//               SCK     PA5  SPI时钟信号
//     示        SDA     PA7  SPI数据信号
//               RES     PA0  复位脚
//     接        DC      PA1
//     口        CS      PA2
//		 --			   BLC     PB3  控制背光
//     ------------------------------------------------------
//     触        INT     PA5  触摸中断
//     摸        SCL     PA6  触摸IIC 时钟线
//     接        SDA     PA7  触摸IIC 数据线
//     口        RST     PA8  触摸复位脚
// ----------------------------------------------------------------
//******************************************************************************/