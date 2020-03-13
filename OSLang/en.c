/******************** (C) COPYRIGHT 2012 BOOLESION.NET ***************************
* 产品名称: BNOS 2012
* 文件名称: en.c
* 程序作者: BOOLESION.NET 布尔创(BOOLESION)电子科技 - NETC (陈建长)
* 程序版本: V1.2
* 编制日期: 2012/03/20
* 功能描述: 系统语言: English.
**********************************************************************************/

/* Includes ---------------------------------------------------------------------*/
#include "includes.h"



/*********************************************************************************
** 函数名称: void SelectTitle(INT8U menutitle,INT8U action).
** 功能描述: 标题选择显示状态.
** 输入参数: INT8U menutitle 标题数,INT8U action 选中状态 0 未选中 1 选中.         
** 输出参数: None.
** 返回参数: None.
**********************************************************************************/
void ENSelectTitle(INT8U menutitle,INT8U action)
{

	if(action == 1)	 /* 选中状态 */
	{ 
		switch(menutitle)
		{
			case 1:	LCD_Write_String(52,85,"Music",WALLCOLOR,MENUCOLOR,1);
			break;
			case 2: LCD_Write_String(138,85,"Photos",WALLCOLOR,MENUCOLOR,1);
			break;
			case 3: LCD_Write_String(222,85,"Radio",WALLCOLOR,MENUCOLOR,1);
			break;
			case 4:	LCD_Write_String(292,85,"Calendar",WALLCOLOR,MENUCOLOR,1);
			break;
			case 5:	LCD_Write_String(52,175,"Ebook",WALLCOLOR,MENUCOLOR,1);
			break;
			case 6: LCD_Write_String(126,175,"Calculator",WALLCOLOR,MENUCOLOR,1);
			break;
			case 7: LCD_Write_String(232,175,"App",WALLCOLOR,MENUCOLOR,1);
			break;
			case 8: LCD_Write_String(292,175,"Settings",WALLCOLOR,MENUCOLOR,1);
			break;
		}
	}
	else if(action == 0)	 /* 未选中状态 */
	{
		switch(menutitle)
		{
		
			case 1:	LCD_Write_String(52,85,"Music",MENUCOLOR,WALLCOLOR,1);
			break;
			case 2: LCD_Write_String(138,85,"Photos",MENUCOLOR,WALLCOLOR,1);
			break;
			case 3: LCD_Write_String(222,85,"Radio",MENUCOLOR,WALLCOLOR,1);
			break;
			case 4:	LCD_Write_String(292,85,"Calendar",MENUCOLOR,WALLCOLOR,1);
			break;
			case 5:	LCD_Write_String(52,175,"Ebook",MENUCOLOR,WALLCOLOR,1);
			break;
			case 6: LCD_Write_String(126,175,"Calculator",MENUCOLOR,WALLCOLOR,1);
			break;
			case 7: LCD_Write_String(232,175,"App",MENUCOLOR,WALLCOLOR,1);
			break;
			case 8: LCD_Write_String(292,175,"Settings",MENUCOLOR,WALLCOLOR,1);
			break;	
		}
	}		
}
