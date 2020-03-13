/******************** (C) COPYRIGHT 2012 BOOLESION.NET ***************************
* 产品名称: BNOS 2012
* 文件名称: chn.h
* 程序作者: BOOLESION.NET 布尔创(BOOLESION)电子科技 - NETC (陈建长)
* 程序版本: V1.2
* 编制日期: 2012/03/20
* 功能描述: 系统语言:中文.
**********************************************************************************/

/* Includes ---------------------------------------------------------------------*/
#include "includes.h"
/* 函数声明 */
void CHSelectTitle(INT8U menutitle,INT8U action);
#define CH_BNOSSTARTING	LCD_Write_String(2,LCD_YSIZE_TFT - 42,"BNOS 2012 启动中...",Green,Blue,1)

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
#define CH_MAINMENUTITLE	;\
	LCD_Write_String(49,85,"播放器",MENUCOLOR,WALLCOLOR,1);\		        
	LCD_Write_String(147,85,"相册",MENUCOLOR,WALLCOLOR,1);\		
	LCD_Write_String(219,85,"收音机",MENUCOLOR,WALLCOLOR,1);\		
	LCD_Write_String(299,85,"万年历",MENUCOLOR,WALLCOLOR,1);\		  
	LCD_Write_String(49,175,"电子书",MENUCOLOR,WALLCOLOR,1);\			
	LCD_Write_String(139,175,"计算器",MENUCOLOR,WALLCOLOR,1);\	   
	LCD_Write_String(229,175,"程序",MENUCOLOR,WALLCOLOR,1);\				
	LCD_Write_String(308,175,"设置",MENUCOLOR,WALLCOLOR,1);\
/*  选中标题 */
#define CH_MAINMENUSEL(menutitle,action) CHSelectTitle(menutitle,action)
