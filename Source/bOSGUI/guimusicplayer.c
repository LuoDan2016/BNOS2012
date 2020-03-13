/******************** (C) COPYRIGHT 2012 BOOLESION.NET ***************************
* 产品名称: 布尔创51开发板 E1101
* 文件名称: guimusicplayer.c
* 程序作者: BOOLESION.NET 布尔创(BOOLESION)电子科技 - NETC (陈建长)
* 程序版本: V1.2
* 编制日期: 2012/01/20
* 功能描述: 音乐播放器GUI程序.
**********************************************************************************/

/* Includes ---------------------------------------------------------------------*/
#include "includes.h"

/* 变量声明 ---------------------------------------------------------------------*/
extern volatile INT8U menuflag; /* 菜单标识 */ 

/*********************************************************************************
** 函数名称: void GuiMusicPlayer(void).
** 功能描述: 音乐播放器GUI.
** 输入参数: None.         
** 输出参数: None.
** 返回参数: None.
**********************************************************************************/
void GuiMusicPlayer(void)
{
	INT8U i;
	menuflag = MAINMENU_MUSIC; /* 菜单标识 1 */
	CreateWindow("Music Player",30,30,330,165,Black);	/* 创建窗口 */
	GUIProgressBar(70,180,250,6,0);						/* 进度条 */
	GUIPlay(170,150,White);    /* 播放图标 */
	GUIPause(200,150,White);   /* 暂停按钮 */ 
	/* 上一首 */
	GUIUpSong(90,150,White);
	/* 下一首 */
	GUIDownSong(295,150,White);
	LCD_FilledRectangle(70,145,250,2,White);	    /* width : 250  high : 6 */
	/* 音量显示 */	                                         
	LCD_Write_String(68,68,"VOL",White,Back_Color,0);
	GUIVolumeico(95,80,38);
	/* 歌曲标题 */
	LCD_Write_String(128,68,"  Title",String_Color,Back_Color,1);
	/* 播放时间 */
	Lcd_WriteNumlen(2,0,230,68,White,Back_Color,1);	      	     /* 播放时间  分 */
	LCD_Write_String(247,68,":",White,Back_Color,1);	         /* 播放时间  ":" */
	Lcd_WriteNumlen(2,0,256,68,White,Back_Color,1);              /* 播放时间  秒 */
	LCD_Write_String(273,68,"/",White,Back_Color,1);	         /* 播放时间  "/" */
	/* 总时长 */
	Lcd_WriteNumlen(2,0,281,68,White,Back_Color,1);     	     /* 总时长  分 */
	LCD_Write_String(297,68,":",White,Back_Color,1);	     /* 总时长  ":" */
	Lcd_WriteNumlen(2,0,305,68,White,Back_Color,1);	             /* 总时长  秒 */
	/* 频谱显示 */
	for(i=0;i<28;i++)
    {
        if(i < 14)
			LCD_FilledRectangle(110 + (i*6),145-i*2,5,i*2,Green);	        /* 方块 width : *  high :  */
		if(i == 4 )
			LCD_FilledRectangle(110 + (i*6),145-34,5,34,Green);	        /* 方块 width : *  high :  */
		if(i == 8 )
			LCD_FilledRectangle(110 + (i*6),145-38,5,38,Green);	        /* 方块 width : *  high :  */
		if(i == 12 )
			LCD_FilledRectangle(110 + (i*6),145-30,5,30,Green);	        /* 方块 width : *  high :  */
		if(i >= 14 && i < 22)
			LCD_FilledRectangle(110 + (i*6),145-(28 - i)*2,5,(28 - i)*2,Green);	        /* 方块 width : *  high :  */
		if(i == 20)
			LCD_FilledRectangle(110 + (i*6),145-50,5,50,Green);	        /* 方块 width : *  high :  */
		if(i >= 22)
			LCD_FilledRectangle(110 + (i*6),145-i,5,i,Green);	        /* 方块 width : *  high :  */					
    }
	
}

