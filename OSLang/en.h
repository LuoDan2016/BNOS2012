/******************** (C) COPYRIGHT 2012 BOOLESION.NET ***************************
* 产品名称: BNOS 2012
* 文件名称: en.h
* 程序作者: BOOLESION.NET 布尔创(BOOLESION)电子科技 - NETC (陈建长)
* 程序版本: V1.2
* 编制日期: 2012/03/20
* 功能描述: 系统语言:English.
**********************************************************************************/

/* Includes ---------------------------------------------------------------------*/
#include "includes.h"
/* 函数声明 */
void ENSelectTitle(INT8U menutitle,INT8U action);
#define EN_BNOSSTARTING LCD_Write_String(2,LCD_YSIZE_TFT - 42,"BNOS 2012 LOADING...",Green,Blue,1)

/* 主菜单标题 */
/* 第一行菜单图标 */
/* 音乐菜单标题 */
/* 相册菜单标题 */
/* 收音菜单标标题 */
/* 日历菜单标题 */
/* 第二行菜单图标 */
/* 电子书菜单标题 */
/* 计算器菜单标题 */
/* 应用程序菜单标题 */
/* 系统设置菜单标题 */	
#define EN_MAINMENUTITLE  ;\
	LCD_Write_String(52,85,"Music",MENUCOLOR,WALLCOLOR,0);\		        
	LCD_Write_String(138,85,"Photos",MENUCOLOR,WALLCOLOR,0);\		
	LCD_Write_String(222,85,"Radio",MENUCOLOR,WALLCOLOR,0);\		
	LCD_Write_String(292,85,"Calendar",MENUCOLOR,WALLCOLOR,0);\		  
	LCD_Write_String(52,175,"Ebook",MENUCOLOR,WALLCOLOR,0);\			
	LCD_Write_String(126,175,"Calculator",MENUCOLOR,WALLCOLOR,0);\	   
	LCD_Write_String(232,175,"App",MENUCOLOR,WALLCOLOR,0);\				
	LCD_Write_String(292,175,"Settings",MENUCOLOR,WALLCOLOR,0);\		  	
/*  选中标题 */
#define EN_MAINMENUSEL(menutitle,action) ENSelectTitle(menutitle,action);