/******************** (C) COPYRIGHT 2012 BOOLESION.NET ***************************
* 产品名称: 布尔创51开发板 E1101
* 文件名称: application.c
* 程序作者: BOOLESION.NET 布尔创(BOOLESION)电子科技 - NETC (陈建长)
* 程序版本: V1.2
* 编制日期: 2012/01/20
* 功能描述: BNOS 任务定义，此例程运行于内 RAM > 300 Byte 内核CPU.
**********************************************************************************/

/* Includes ---------------------------------------------------------------------*/
#include "includes.h"

extern OS_STK SDCheckTaskStkd[MaxStkSize + 1]; 

/* 变量声明 ---------------------------------------------------------------------*/
                                     /* 文件系统相关全局变量声明 */
volatile FRESULT res;
volatile FATFS fs;	
volatile INT16U br,i,j;
volatile BYTE buff[256];             /* 缓存空间 BMP解码 音频解码 */
volatile INT16U LcdBLTime = 0;       /* LCD背光时间 */
extern volatile INT16U LcdBLsettime; /* LCD 背光比较值 */
extern volatile INT16U menuflag;     /* 菜单标识为 */
extern volatile INT8U mainmenuflag;  /* 主菜单标识   */
extern SYS_TIME datetime;	         /* 系统时间 */
extern INT8U sdcheck;                /* SD卡检测计数 */

/* 任务定义 ---------------------------------------------------------------------*/
/*********************************************************************************
** 函数名称: void OSMainTask(void *pdat).
** 功能描述: 程序系统初始化任务.
** 输入参数: void *pdat.         
** 输出参数: None
** 返回参数: None
**********************************************************************************/
void OSMainTask(void *pdat)
{
	ET0 = 1;		                 /* 在第一个任务(最高优先级)开始执行时才开时钟中断 */
	pdat = pdat;                        
	OSTimeDlyHMSM(0,0,0,100);
	GUI_MainMenu();                   /* 主界面GUI */
	OSTaskResume(MENUAPP); 
	/* 日期初始化 */
	if(datetime.year == 0)
	{
		datetime.year = 0x2012;		 /* 日期初始化 */
		datetime.mon  = 0x01;
		datetime.day  = 0x01;
	}
	/* 创建任务 */
	OS_ENTER_CRITICAL();  
	OSTaskCreate(SDCheckTask,(void*)0,&SDCheckTaskStkd[0],SDCHECKTASK);
	OS_EXIT_CRITICAL();                      
  	/* 任务循环 */
	for(; ; )
	{
		/* 一行程序实现STC不断电自动下载(如果头文件未定义IAP_CONTR寄存器,在while函数中加入if(P3==(P3&0xFE))IAP_CONTR=0x60;
		** 需定义在#include<reg52.h>中加入sfr IAP_CONTR = 0xC7; )原创BOOLESION.NET  -NETC */
		if(P3==(P3&0xFE))IAP_CONTR=0x60;
		OSTimeDlyHMSM(0,0,0,20);	/*delay 0h 0i 50ms */	
		/* 重新加载SD/TF卡 */
		if( sdcheck != 0 )
		{
			OSTaskResume(SDCHECKTASK);	
		}
	}
}

/*********************************************************************************
** 函数名称: void MenuApp(void *pdat).
** 功能描述: 鼠标及动态菜单显示任务.
** 输入参数: void *pdat.         
** 输出参数: None
** 返回参数: None
**********************************************************************************/
void MenuApp(void *pdat)
{
	pdat = pdat;
	OSTaskSuspend(MENUAPP);
    /* 鼠标初始化,设定初始坐标 */
	MouseInit(10,40);
	for(; ;)
	{ 		   
	    /* 鼠标程序 */
	   MouseScan();
		/* 主动态菜单 及应用程序 */
	   MovMenu();		
	   OSTimeDlyHMSM(0,0,0,10);
	}
}

/*********************************************************************************
** 函数名称: void OSTimeTask(void *pdat).
** 功能描述: 系统时间处理任务.
** 输入参数: void *pdat.         
** 输出参数: None
** 返回参数: None
**********************************************************************************/
void OSTimeTask(void *pdat)
{   
	volatile  INT32U  OSTimebk;
	OSTime = OSTimebk;	          /* 获取系统运行时间 */
	pdat = pdat;
	OSTaskSuspend(OSTIMETASK);
	for(; ; )
	{	
		if(	OSTime - OSTimebk > 60)
		{
			if(datetime.sec <= 60)
			{
				datetime.sec++;	   /* 系统时间s */
				if(LcdBLTime <= LcdBLsettime)  /* LCD背光时间递增 */
					LcdBLTime++;
			}
			else
			{
				datetime.sec = 0;
			}				
		    OSTime = OSTimebk;
		}	
		if(LcdBLTime > LcdBLsettime) /* LCD背光时间和设置值比较 */
		{
			LCD_Backlight = 0;		 /* 关闭LCD背光 */
		}
		if(!KEY_ENTER || !KEY_NEXT || !KEY_PRE || !KEY_UP_VOL || !KEY_DOWN_EXIT) /* 有按键动作重设LCD背光时间为0 */
		{
			LcdBLTime = 0;
				LCD_Backlight = 1;	   /* 开启LCD背光 */
		}			 
		OSTimeDlyHMSM(0,0,0,50);
	}
}

/*********************************************************************************
** 函数名称: void SDCheckTask(void *pdat).
** 功能描述: SD/TF卡重检测任务.
** 输入参数: void *pdat.         
** 输出参数: None
** 返回参数: None
**********************************************************************************/
void SDCheckTask(void *pdat)
{	

	pdat = pdat;
	OSTaskSuspend(SDCHECKTASK); 
	disk_initialize();	                    /* SD TF卡初始化 */			
	res = pf_mount(&fs);                    /* FatFs文件系统挂载 */             
	for(; ;)
	{ 
		while(res)
		{
			if(disk_initialize() == FR_OK);  /* SD TF卡重新初始化 */
			{
				res = pf_mount(&fs);         /* FatFs文件系统重新挂载 */
				if(res == FR_OK)
				{
					OSMSG("SD/TF And FATFS Initialize OK. \r\n");
					sdcheck = 0;
					OSTaskSuspend(SDCHECKTASK); 
				}		
			}	
		 }

	}		
}
