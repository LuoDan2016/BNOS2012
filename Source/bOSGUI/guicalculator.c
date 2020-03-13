/******************** (C) COPYRIGHT 2012 BOOLESION.NET ***************************
* 产品名称: 布尔创51开发板 E1101
* 文件名称: guicalculator.c
* 程序作者: BOOLESION.NET 布尔创(BOOLESION)电子科技 - NETC (陈建长)
* 程序版本: V1.2
* 编制日期: 2012/01/20
* 功能描述: 计算器GUI.
**********************************************************************************/

/* Includes ---------------------------------------------------------------------*/
#include "includes.h"

/* 变量声明 ---------------------------------------------------------------------*/
extern volatile INT8U menuflag;     /* 菜单标识为 */
extern volatile INT8U mainmenuflag; /*主菜单标识   */
INT8U*  code btndata[4][4] = 
{
	{"1","2","3","/"},
	{"4","5","6","*"},
	{"7","8","9","-"},
	{"0","C","=","+"}
}; 

/*********************************************************************************
** 函数名称: void GUIRadio(void).
** 功能描述: 计算器GUI.
** 输入参数: None.         
** 输出参数: None.
** 返回参数: None.
**********************************************************************************/
void GUICalculator(void)
{ 	
	INT8U i,j;
	menuflag = MAINMENU_CALCULATOR;                     /* 菜单标识 */

	CreateWindow("Calculator",30,30,330,165,White);	    /* 创建窗口 */
	/* 输入面板显示 */
	for(j=0;j<4;j++)
	{
		for(i=0;i<4;i++)
		{
			GUIButton(btndata[j][i],42 + 12 * i + 20 * i,56+ 12 * j + 20 * j,30,30,RGB(220,220,220));	 /* 按钮 */	
		}
	}
	/* 显示面板*/
	LCD_FilledRectangle(180,56,170,127,RGB(230,230,230));	
	LCD_FilledRectangle(182,58,166,123,White);	/* 显示面板 */
	LCD_FilledRectangle(186,148,160,1,RGB(230,230,230));
	/* 操作显示 */
	Lcd_WriteNumlen(1,0,185,100,Black,White,1);	/* 输入数据1 */
//	Lcd_WriteNumlen(1,0,185,116,Black,White,1);	/* 符号 */
//	Lcd_WriteNumlen(1,0,185,132,Black,White,1);	/* 输入数据2 */

	LCD_Write_String(185,149,"=",Black,White,0);
	Lcd_WriteNumlen(1,0,185,165,Black,White,1);	/* 显示结果 */
					
}