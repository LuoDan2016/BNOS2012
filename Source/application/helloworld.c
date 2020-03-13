/******************** (C) COPYRIGHT 2012 BOOLESION.NET ***************************
* 产品名称: 布尔创51开发板 E1101
* 文件名称: helloworld.c
* 程序作者: BOOLESION.NET 布尔创(BOOLESION)电子科技 - NETC (陈建长)
* 程序版本: V1.2
* 编制日期: 2012/01/20
* 功能描述: 应用程序例子.
**********************************************************************************/

/* Includes ---------------------------------------------------------------------*/
#include "includes.h"

/* 变量声明 ---------------------------------------------------------------------*/
extern volatile INT8U menuflag;     /* 菜单标识为 */
extern volatile INT8U mainmenuflag; /* 主菜单标识 */

/*********************************************************************************
** 函数名称: void HelloWorld(void).
** 功能描述: 应用程序例子.
** 输入参数: None.         
** 输出参数: None.
** 返回参数: None.
**********************************************************************************/
void HelloWorld(void)
{
	INT8U menucount = 2;
	LCD_Write_String(150,100,"Hello World!",Black,White,0);	  /* "Hello World!" */
	GUIButton(" CLOSE",220,150,70,25,RGB(220,220,220));	      /* 未选中 CLOSE */	
	GUIButton("  OK",100,150,70,25,RGB(220,220,220));	      /* 未选中 OK */
	while(1)
	{
		/* 按键 KEY_DOWN_EXIT 退出并返回主菜单 */
		if(!KEY_DOWN_EXIT)
		{
		 	menuflag     = 0;
		    mainmenuflag = 0;
		 	break;			
		}
	    if(!KEY_PRE)
	    {
		   menucount = 0;
		   GUIButton("  OK",100,150,70,25,RGB(110,110,110));	 /* 选中 OK */
		   GUIButton(" CLOSE",220,150,70,25,RGB(220,220,220));	 /* 未选中 CLOSE */		
		}
		if(!KEY_NEXT)
	    {
		   menucount = 1;
		   GUIButton("  OK",100,150,70,25,RGB(220,220,220));	 /* 未选中 OK */
		   GUIButton(" CLOSE",220,150,70,25,RGB(110,110,110));	 /* 选中 CLOSE */		
		}
		if(!KEY_ENTER)
		{
			if(menucount == 1)
			{
				 menuflag      = 0;
		   		 mainmenuflag = 0;
		 		 break;	
			}
			if(menucount  == 0)
			{
				CreateWindow("Hello World",95,60,200,80,White);	          /* 创建窗口 */
				LCD_Write_String(150,100,"Hello World!",Black,White,0);	  /* "Hello World!" */	
			}
		}

	}
}		