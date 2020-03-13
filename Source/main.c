/******************** (C) COPYRIGHT 2012 BOOLESION.NET *************************
* 产品名称: 布尔创51开发板 E1101
* 文件名称: main.c
* 程序作者: BOOLESION.NET 布尔创(BOOLESION)电子科技 - NETC (陈建长)
* 程序版本: V1.2
* 编制日期: 2012/03/20
* 功能描述: BNOS 2012 任务创建，此例程运行于内 RAM > 300 Byte 内核CPU.
********************************************************************************
* CPU : 8051
* 时钟: 22.1184Mhz
* 声明：程序,算法为(BOOLESION.NET)NETC原创，转载请注明出处.
*******************************************************************************/

/* Includes ------------------------------------------------------------------*/
#include "includes.h"

/* 定义数组作为任务堆栈 ------------------------------------------------------*/
OS_STK OSMainTaskStk   [MaxStkSize + 1];
OS_STK MenuAppTaskStk  [MaxStkSize*2 + 1]; 
OS_STK OSTimeTaskStkc  [MaxStkSize + 1]; 
OS_STK SDCheckTaskStkd [MaxStkSize + 1]; 

/* 变量声明 ------------------------------------------------------------------*/
/* 主函数声明 ----------------------------------------------------------------*/

/******************************************************************************
** 函数名称: main.
** 功能描述: 程序主函数.
** 输入参数: None.         
** 输出参数: None
** 返回参数: None
*******************************************************************************/
void main(void)
{	
	/* 设备初始化 */
	DeviceInit();
	/* 系统字库及GUI数据处理 */
	FontGUILoad();
	/* 布尔创LOGO信息 */
	GUI_BRCLOGO();
	COMNLANG_COPYRIGHT;
	/* 启动进度 */	
	GUIProgressBar(0,LCD_YSIZE_TFT - 6,400,6,100);
	/* OS Start */		
	OSInit();
	OSTaskCreate(OSMainTask,(void*)0,&OSMainTaskStk[0],OSMAINTASK); 
	OSTaskCreate(MenuApp,(void*)0,&MenuAppTaskStk[0],MENUAPP);
	OSTaskCreate(OSTimeTask,(void*)0,&OSTimeTaskStkc[0],OSTIMETASK);
	OSStart(); 
}

