/******************** (C) COPYRIGHT 2012 BOOLESION.NET ***************************
* 产品名称: 布尔创51开发板 E1101
* 文件名称: guiradio.c
* 程序作者: BOOLESION.NET 布尔创(BOOLESION)电子科技 - NETC (陈建长)
* 程序版本: V1.2
* 编制日期: 2012/01/20
* 功能描述: 收音机GUI.
**********************************************************************************/

/* Includes ---------------------------------------------------------------------*/
#include "includes.h"

/* 变量声明 ---------------------------------------------------------------------*/

extern volatile INT8U menuflag;     /* 菜单标识 */ 
extern volatile INT8U mainmenuflag; /* 主菜单标识 */
extern INT32U frequency; /* FM频率声明 */
/*********************************************************************************
** 函数名称: void GUIRadio(void).
** 功能描述: 收音机GUI.
** 输入参数: None.         
** 输出参数: None.
** 返回参数: None.
**********************************************************************************/
void GUIRadio(void)
{
	menuflag = MAINMENU_RADIO;                      /* 菜单标识 2 */
    CreateWindow("FM Radio",30,30,330,165,Black);	/* 创建窗口 */

	GUIPlay(170,150,Green);    /* 播放图标 */
	GUIPause(200,150,White);   /* 暂停按钮 */ 
	/* 上一首 */
	GUIUpSong(90,150,White);
	/* 下一首 */
	GUIDownSong(295,150,White);
	LCD_FilledRectangle(70,145,250,2,White);	    /* width : 250  high : 6 */


	/* 频率显示 */
	LCD_Write_String(68+50,90,"FM FREQ:",White,Back_Color,0);
	LCD_Write_String(70,128,"87.5 MHz",White,Back_Color,0);
	LCD_Write_String(270,128,"108 MHz",White,Back_Color,0);
	LCD_Write_String(178+50,90,"MHz",White,Back_Color,0);				      /* MHz */
	FreqShow(frequency);						
	GUIProgressBar2(70,120,250,6,100 * ((FP32)((frequency/100) - 870) / (FP32)(1080 - 870)) );	  /* 频率进度条 */

}