/******************** (C) COPYRIGHT 2012 BOOLESION.NET ***************************
* 产品名称: 布尔创51开发板 E1101
* 文件名称: guimainmenu.c
* 程序作者: BOOLESION.NET 布尔创(BOOLESION)电子科技 - NETC (陈建长)
* 程序版本: V1.2
* 编制日期: 2012/01/20
* 功能描述: 主界面窗口GUI程序.
**********************************************************************************/

/* Includes ---------------------------------------------------------------------*/
#include "includes.h"

/* 变量声明 ---------------------------------------------------------------------*/
extern SYS_TIME datetime;	    /* 系统时间 */
extern volatile INT8U menuflag; /* 菜单标识为 */ 
/*  汉字字库检查标识 1为正确 其他不存在 */
extern INT8U CHNCHEK;

/*********************************************************************************
** 函数名称: void GuiMainMenu(void).
** 功能描述: 启动界面GUI.
** 输入参数: None.         
** 输出参数: None.
** 返回参数: None.
**********************************************************************************/
void GUI_MainMenu(void)
{
	INT8U *DISLANG;
	INT8U res;
	switch(USELANG)	     /* 语言选择 */
		{
			case 0:			 /* English  */
				DISLANG = "EN";
			case 1:			 /* 简体中文 */
				DISLANG = "CH";
			case 2:			 /* 默认语言 */
			 	if(CHNCHEK)
					DISLANG = "CH";
				else
					DISLANG = "EN";	
		}	
	/* 主界面窗口 */
	/* 任务栏 */	
	LCD_FilledRectangle(LCD_XSIZE_TFT - LCD_XSIZE_TFT,LCD_YSIZE_TFT - 24,LCD_XSIZE_TFT,1,RGB(127,127,127));
	LCD_FilledRectangle(LCD_XSIZE_TFT - LCD_XSIZE_TFT,LCD_YSIZE_TFT - 23,LCD_XSIZE_TFT,23,TASKBARCOLOR);/* 任务栏 */
	Lcd_WriteNumlen(2,datetime.hour,LCD_XSIZE_TFT - 44,LCD_YSIZE_TFT - 16,White,TASKBARCOLOR,1);	    /* 时间显示 */
	LCD_Write_String(LCD_XSIZE_TFT - 28,LCD_YSIZE_TFT - 16,":",White,TASKBARCOLOR,1);
	Lcd_WriteNumlen(2,datetime.min,LCD_XSIZE_TFT - 20,LCD_YSIZE_TFT - 16,White,TASKBARCOLOR,1);	
	GUIToolICOPower(340,220,8);	                                        /* 电量显示 */

	LCD_Write_String(310,LCD_YSIZE_TFT - 16,DISLANG,White,TASKBARCOLOR,1);	/* 系统语言 */
	LCD_FilledRectangle(4,LCD_YSIZE_TFT - 20,20,4,Magenta);	            /* 开始菜单 */
	LCD_FilledRectangle(4,LCD_YSIZE_TFT - 14,20,4,Green);
	LCD_FilledRectangle(4,LCD_YSIZE_TFT - 8,20,4,Blue2);
}

/*********************************************************************************
** 函数名称: void MainIco(void).
** 功能描述: 主界面菜单ICO.
** 输入参数: None.         
** 输出参数: None.
** 返回参数: None.
**********************************************************************************/
void MainIco(void)
{
	/* 主菜单标识为MAINMENU 0 */
	menuflag = MAINMENU;      
	/* 第一行菜单图标 */
	LCD_Write_String(44 ,98,"Music",NotselColor,Back_Color,0);		        /* 音乐菜单标题 */
   	LCD_Write_String(128,98,"Photos",NotselColor,Back_Color,0);				/* 相册菜单标题 */
	LCD_Write_String(218,98,"Radio",NotselColor,Back_Color,0);				/* 收音菜单标标题 */
	LCD_Write_String(294,98,"Calendar",NotselColor,Back_Color,0);		    /* 日历菜单标题 */
	/* 第二行菜单图标 */
	LCD_Write_String(48 ,179,"Ebook",NotselColor,Back_Color,0);			    /* 电子书菜单标题 */
   	LCD_Write_String(110,179,"Calculator",NotselColor,Back_Color,0);	    /* 计算器菜单标题 */
	LCD_Write_String(228,179,"App",NotselColor,Back_Color,0);				/* 应用程序菜单标题 */
	LCD_Write_String(296,179,"Settings",NotselColor,Back_Color,0);		    /* 系统设置菜单标题 */	
}
