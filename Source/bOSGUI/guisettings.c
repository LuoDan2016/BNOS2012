/******************** (C) COPYRIGHT 2012 BOOLESION.NET ***************************
* 产品名称: 布尔创51开发板 E1101
* 文件名称: guisettings.c
* 程序作者: BOOLESION.NET 布尔创(BOOLESION)电子科技 - NETC (陈建长)
* 程序版本: V1.2
* 编制日期: 2012/01/20
* 功能描述: 系统设置GUI.
**********************************************************************************/

/* Includes ---------------------------------------------------------------------*/
#include "includes.h"

/* 变量声明 ---------------------------------------------------------------------*/
extern volatile INT8U menuflag; /* 菜单标识 */ 
extern volatile INT16U LcdBLsettime; /* LCD 背光比较值 */
extern SYS_TIME datetime;	 /* 系统时间 */

/*********************************************************************************
** 函数名称: void GUISettings(void).
** 功能描述: 系统设置GUI.
** 输入参数: None.         
** 输出参数: None.
** 返回参数: None.
**********************************************************************************/
void GUISettings(void)
{
	menuflag = MAINMENU_SETTINGS;                   /* 菜单标识 */
	CreateWindow("Settings",30,30,330,165,White);	/* 创建窗口 */
    GUIButton(" EXIT",220,150,70,25,RGB(220,220,220));	 /* 未选中 EXIT */	
	GUIButton("  OK",100,150,70,25,RGB(220,220,220));	 /* 未选中 OK */
	/* 背光时间设置 */
	LCD_Write_String(50,54,"Backlight Time(s):",Black,White,0);	  /* "Backlight Time" */
	/* 减少背光时间 */
	GUIUp(210,52,Black);   
	Lcd_WriteNumlen(3,LcdBLsettime,232,54,String_Color,White,1);	/* 显示 时间 second */
	/* 增加背光时间 */
	GUIDown(280,52,Black);	
	/* 系统时间设置 */
	LCD_Write_String(50,80,"System year:",Black,White,0);	  /* "System year" */
	/* 设置时间 年 减 */
	GUIUp(210,78,Black);   
	Lcd_WriteNumlen(4,BcdToBin(datetime.year >> 8)*0x64 +  BcdToBin(datetime.year & 0xff),232,80,String_Color,White,1);	/* 显示 时间 年 */
	/* 设置时间 年 增 */
	GUIDown(280,78,Black);
	LCD_Write_String(50,106,"System mon:",Black,White,0);	  /* "System mon" */
	/* 设置时间 月 减 */
	GUIUp(210,104,Black);   
	Lcd_WriteNumlen(2,BcdToBin(datetime.mon),232,106,String_Color,White,1);	/* 显示 时间 月 */
	/* 设置时间 月 增 */
	GUIDown(280,104,Black);
	LCD_Write_String(50,132,"System day:",Black,White,0);	  /* "System day" */
	/* 设置时间 日 减 */
	GUIUp(210,130,Black);   
	Lcd_WriteNumlen(2,BcdToBin(datetime.day),232,132,String_Color,White,1);	/* 显示 时间 日 */
	/* 设置时间 日 增 */
	GUIDown(280,130,Black);

}

