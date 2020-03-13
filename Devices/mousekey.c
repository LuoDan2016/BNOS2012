/******************** (C) COPYRIGHT 2012 BOOLESION.NET ***************************
* 产品名称: 布尔创51开发板 E1101
* 文件名称: mousekey.c.c
* 程序作者: BOOLESION.NET 布尔创(BOOLESION)电子科技 - NETC (陈建长)
* 程序版本: V1.1
* 编制日期: 2012/01/20
* 功能描述: 鼠标驱动程序.
**********************************************************************************/

/* Includes ---------------------------------------------------------------------*/
#include "includes.h"

/* 变量声明 ---------------------------------------------------------------------*/
/* 光标全局变量及光标坐标初始化 */
volatile INT16U getcolor[12],xcoordinate=20,ycoordinate=50;

/*********************************************************************************
** 函数名称: void MouseInit(INT16U x,INT16U y).
** 功能描述: 鼠标初始化.
** 输入参数: INT16U x,INT16U y.         
** 输出参数: None.
** 返回参数: None.
**********************************************************************************/
void MouseInit(INT16U x,INT16U y)
{
	INT8U i;
	xcoordinate = x;
	ycoordinate = y;
	for(i=0;i<12;i++)
	{
		getcolor[i]  =	LCD_GetPoint(xcoordinate + i,ycoordinate);
		if(i >5 )
			LCD_DrawPoint(xcoordinate + i,ycoordinate,Red);
		else
			LCD_DrawPoint(xcoordinate + i,ycoordinate,White);			
	}	
}

/*********************************************************************************
** 函数名称: void MouseScan(void).
** 功能描述: 鼠标扫描程序.
** 输入参数: None.         
** 输出参数: None.
** 返回参数: None.
**********************************************************************************/
void MouseScan(void)
{
	INT8U i;

	/* 右移 */   
	if(!KEY_NEXT && (xcoordinate < 399))  /* 光标移动条件 */
	{
		for(i=0;i<12;i++)	              /* 填充原区域颜色 */
		{
			LCD_DrawPoint(xcoordinate+i,ycoordinate,getcolor[i]);	
		}	
		xcoordinate++;		              /* 坐标值增加*/
		for(i=0;i<12;i++)	              /* 获取当前区域颜色 */
		{
			getcolor[i]  =	LCD_GetPoint(xcoordinate + i,ycoordinate);	
		}
		for(i=0;i<12;i++)	              /* 移动光标 */
		{
			if(i >5 )
			LCD_DrawPoint(xcoordinate + i,ycoordinate,Red);
			else
			LCD_DrawPoint(xcoordinate + i,ycoordinate,White);			
		}
	}
	/* 左移 */
	if(!KEY_PRE && (xcoordinate > 0))
	{
		for(i=0;i<12;i++)	   /* 填充原区域颜色 */
		{
		LCD_DrawPoint(xcoordinate+i,ycoordinate,getcolor[i]);	
		}
			xcoordinate--;
		for(i=0;i<12;i++)	   /* 获取当前区域颜色 */
		{
			getcolor[i]  =	LCD_GetPoint(xcoordinate + i,ycoordinate);	
		}
		for(i=0;i<12;i++)
		{
			if(i >5 )
			LCD_DrawPoint(xcoordinate + i,ycoordinate,Red);
			else
			LCD_DrawPoint(xcoordinate + i,ycoordinate,White);			
		}
	}
	/* 下移 */
	if(!KEY_DOWN_EXIT && (ycoordinate < 239))
	{
		for(i=0;i<12;i++)	   /* 填充原区域颜色 */
		{
			LCD_DrawPoint(xcoordinate+i,ycoordinate,getcolor[i]);	
		}
		ycoordinate++;
		for(i=0;i<12;i++)	   /* 获取当前区域颜色 */
		{
			getcolor[i]  =	LCD_GetPoint(xcoordinate + i,ycoordinate);	
		}
		for(i=0;i<12;i++)
		{
			if(i >5 )
			LCD_DrawPoint(xcoordinate + i,ycoordinate,Red);
			else
			LCD_DrawPoint(xcoordinate + i,ycoordinate,White);			
		}
		/* 
		** 屏幕像是坐标,用于寻找坐标
		** Lcd_WriteNumlen(3,xcoordinate,50,2,White,Black,1);
		** Lcd_WriteNumlen(3,ycoordinate,80,2,White,Black,1);
		 */

	}
	/* 上移 */
	if(!KEY_UP_VOL && (ycoordinate > 0))
	{
		for(i=0;i<12;i++)	   /* 填充原区域颜色 */
		{
			LCD_DrawPoint(xcoordinate+i,ycoordinate,getcolor[i]);	
		}	
		ycoordinate--;
		for(i=0;i<12;i++)	   /* 获取当前区域颜色 */
		{
			getcolor[i]  =	LCD_GetPoint(xcoordinate + i,ycoordinate);	
		}
		for(i=0;i<12;i++)
		{
			if(i >5 )
			LCD_DrawPoint(xcoordinate + i,ycoordinate,Red);
			else
			LCD_DrawPoint(xcoordinate + i,ycoordinate,White);			
		}
	}
}