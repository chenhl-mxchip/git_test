
/**************************************************************/
//版 本 号： Ver 1.0
//开 发 者： MingH
//生成日期： 2015-5-20
//其他说明： SD Card/RTC/Beep
//**************************************************************/

#include "stm32f10x.h"
#include "BUZZER.h"
#include "USART.h"
#include "RTC.h"
#include <stdio.h>

/**************************************************************/
//程 序 名： RCC_Config()
//开 发 者： Haichao.Xie
//入口参数： 无
//功能说明： 系统时钟配置
//**************************************************************/
void RCC_Config(void)
{
	ErrorStatus HSEStartUpStatus;	//定义结构体
	/* RCC system reset(for debug purpose)将外设 RCC寄存器重设为缺省值 */
	RCC_DeInit();
	/* Enable HSE 设置外部高速晶振（HSE）*/
	RCC_HSEConfig(RCC_HSE_ON);
	/* Wait till HSE is ready 等待 HSE 起振*/
	HSEStartUpStatus = RCC_WaitForHSEStartUp();

	if (HSEStartUpStatus == SUCCESS)
	{
		/* Enable Prefetch Buffer 预取指缓存使能*/
		FLASH_PrefetchBufferCmd(FLASH_PrefetchBuffer_Enable);

		/* Flash 2 wait state 设置代码延时值*/
		FLASH_SetLatency(FLASH_Latency_2);

		/* HCLK = SYSCLK 设置 AHB 时钟（HCLK）*/
		RCC_HCLKConfig(RCC_SYSCLK_Div1);

		/* PCLK2 = HCLK 设置高速 AHB 时钟（PCLK2）*/
		RCC_PCLK2Config(RCC_HCLK_Div1);

		/* PCLK1 = HCLK/1 设置低速 AHB 时钟（PCLK1）*/
		RCC_PCLK1Config(RCC_HCLK_Div1);

		/* PLLCLK = 12MHz * 6 = 72 MHz 设置 PLL 时钟源及倍频系数*/
		RCC_PLLConfig(RCC_PLLSource_HSE_Div1, RCC_PLLMul_6);

		/* Enable PLL 使能或者失能 PLL*/
		RCC_PLLCmd(ENABLE);

		/* Wait till PLL is ready 等待指定的 RCC 标志位设置成功 等待PLL初始化成功*/
		while(RCC_GetFlagStatus(RCC_FLAG_PLLRDY) == RESET)
		{
		}
		/* Select PLL as system clock source 设置系统时钟（SYSCLK） 设置PLL为系统时钟源*/
		RCC_SYSCLKConfig(RCC_SYSCLKSource_PLLCLK);

		/* Wait till PLL is used as system clock source 等待PLL成功用作于系统时钟的时钟源*/
		while(RCC_GetSYSCLKSource() != 0x08)
		{
		}
	}
}

/**************************************************************/
//程 序 名： main()
//开 发 者： MingH
//入口参数： 无
//功能说明： 主函数
//**************************************************************/
int main(void)
{
	RCC_Config();		// 时钟初始化配置
	Beep_Init();		// 蜂鸣器初始化配置
	USB2Serial_Init(); 	// 串口初始化配置
	
	// 开机等待输入
  
	if (getchar() == 0x20) {
		
	}
	
	
	printf("侯名的测试项目: 1. RTC 2. SDIO 3. BEEP\r\n");
	
	RTC_Init(); 		// RTC 初始化配置
	
	while (1)
	{
		Time_Show();		
	}
}

