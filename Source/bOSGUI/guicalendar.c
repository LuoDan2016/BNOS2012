/******************** (C) COPYRIGHT 2012 BOOLESION.NET ***************************
* 产品名称: 布尔创51开发板 E1101
* 文件名称: guicalendar.c
* 程序作者: BOOLESION.NET 布尔创(BOOLESION)电子科技 - NETC (陈建长)
* 程序版本: V1.2
* 编制日期: 2012/01/20
* 功能描述: 万年历GUI.
**********************************************************************************/

/* Includes ---------------------------------------------------------------------*/
#include "includes.h"

/* 变量声明 ---------------------------------------------------------------------*/
extern volatile INT8U menuflag; /* 菜单标识 */ 
extern SYS_TIME datetime;	    /* 系统时间 */
extern INT8U code *WEEKS[7];

/*********************************************************************************
** 函数名称: void GUICalendar(void).
** 功能描述: 万年历GUI.
** 输入参数: None.         
** 输出参数: None.
** 返回参数: None.
**********************************************************************************/
void GUICalendar(void)
{
	menuflag = MAINMENU_CALENDAR;        /* 菜单标识 2 */
	datetime.week = GetWeekMaxDay(datetime.year,datetime.mon,datetime.day) >> 5; /* 获得星期 */
	CreateWindow("Calendar",30,30,330,165,White);	/* 创建窗口 */
	LCD_FilledRectangle(132,50,2,140,Gray);         /* 分隔线 width : 2  high : 120 */
	LCD_Write_String(60,60,"TODAY",Black,White,0);
 	Lcd_WriteNumlen(4,BcdToBin(datetime.year >> 8)*0x64 +  BcdToBin(datetime.year&0xff),40,80,Blue,White,1);  /* 年 */
	LCD_Write_String(73,80,"/",Blue,White,0);
	Lcd_WriteNumlen(2,BcdToBin(datetime.mon),82,80,Blue,White,1);	          /* 月 */
	LCD_Write_String(99,80,"/",Blue,White,0);
	Lcd_WriteNumlen(2,BcdToBin(datetime.day),108,80,Blue,White,1);            /* 日 */
	LCD_Write_String(60,110,WEEKS[datetime.week],Red,White,0);                /* 星期 */

	GUIUp(180,50,Black);   /* 上一月 */
	GUIDown(320,50,Black);	/* 下一月 */

	Lcd_WriteNumlen(4,BcdToBin(datetime.year >> 8)*0x64 +  BcdToBin(datetime.year&0xff),40+178,54,Blue,White,1);	          /* 年 */
	LCD_Write_String(73+178,54,"/",Blue,White,0);
	Lcd_WriteNumlen(2,BcdToBin(datetime.mon),82+178,54,Blue,White,1);	          /* 月 */

	/* 星期 */
	LCD_FilledRectangle(138,80,218,1,Gray);         /*  width : 204  high : 1 */
	LCD_Write_String(140,84,"SUN MON TUE WED THU FRI SAT",Black,White,0);
	LCD_FilledRectangle(138,102,218,1,Gray);        /*  width : 204  high : 1 */
}
