/******************** (C) COPYRIGHT 2012 BOOLESION.NET ***************************
* 产品名称: 布尔创51开发板 E1101
* 文件名称: guiebook.c
* 程序作者: BOOLESION.NET 布尔创(BOOLESION)电子科技 - NETC (陈建长)
* 程序版本: V1.2
* 编制日期: 2012/01/20
* 功能描述: 电子书GUI.
**********************************************************************************/

/* Includes ---------------------------------------------------------------------*/
#include "includes.h"

/* 变量声明 ---------------------------------------------------------------------*/
extern volatile INT8U menuflag; /* 菜单标识 */ 

/*********************************************************************************
** 函数名称: void GUIRadio(void).
** 功能描述: 电子书GUI.
** 输入参数: None.         
** 输出参数: None.
** 返回参数: None.
**********************************************************************************/
void GUIEbook(void)
{
	menuflag = MAINMENU_EBOOK;                  /* 菜单标识 2 */

	CreateWindow("Ebook",30,30,330,165,White);	/* 创建窗口 */

	GUIUp(70,170,Black);     /* 上一页 */
	GUIDown(320,170,Black);	 /* 下一页 */
}