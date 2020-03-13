/******************** (C) COPYRIGHT 2012 BOOLESION.NET ***************************
* 产品名称: BNOS 2012
* 文件名称: chn.c
* 程序作者: BOOLESION.NET 布尔创(BOOLESION)电子科技 - NETC (陈建长)
* 程序版本: V1.2
* 编制日期: 2012/03/20
* 功能描述: 系统语言:中文.
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
void CHSelectTitle(INT8U menutitle,INT8U action)
{

	if(action == 1)	 /* 选中状态 */
	{ 
		switch(menutitle)
		{
			case 1:	LCD_Write_String(49,85,"播放器",WALLCOLOR,MENUCOLOR,1);
			break;
			case 2: LCD_Write_String(147,85,"相册",WALLCOLOR,MENUCOLOR,1);
			break;
			case 3: LCD_Write_String(219,85,"收音机",WALLCOLOR,MENUCOLOR,1);
			break;
			case 4:	LCD_Write_String(299,85,"万年历",WALLCOLOR,MENUCOLOR,1);
			break;
			case 5:	LCD_Write_String(49,175,"电子书",WALLCOLOR,MENUCOLOR,1);
			break;
			case 6: LCD_Write_String(139,175,"计算器",WALLCOLOR,MENUCOLOR,1);
			break;
			case 7: LCD_Write_String(229,175,"程序",WALLCOLOR,MENUCOLOR,1);
			break;
			case 8: LCD_Write_String(308,175,"设置",WALLCOLOR,MENUCOLOR,1);
			break;
		}
	}
	else if(action == 0)	 /* 未选中状态 */
	{
		switch(menutitle)
		{
		
			case 1:	LCD_Write_String(49,85,"播放器",MENUCOLOR,WALLCOLOR,1);
			break;
			case 2: LCD_Write_String(147,85,"相册",MENUCOLOR,WALLCOLOR,1);
			break;
			case 3: LCD_Write_String(219,85,"收音机",MENUCOLOR,WALLCOLOR,1);
			break;
			case 4:	LCD_Write_String(299,85,"万年历",MENUCOLOR,WALLCOLOR,1);
			break;
			case 5:	LCD_Write_String(49,175,"电子书",MENUCOLOR,WALLCOLOR,1);
			break;
			case 6: LCD_Write_String(139,175,"计算器",MENUCOLOR,WALLCOLOR,1);
			break;
			case 7: LCD_Write_String(229,175,"程序",MENUCOLOR,WALLCOLOR,1);
			break;
			case 8: LCD_Write_String(308,175,"设置",MENUCOLOR,WALLCOLOR,1);
			break;	
		}
	}		
}
