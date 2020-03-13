/******************** (C) COPYRIGHT 2012 BOOLESION.NET ***************************
* ��Ʒ����: ������51������ E1101
* �ļ�����: guimusicplayer.c
* ��������: BOOLESION.NET ������(BOOLESION)���ӿƼ� - NETC (�½���)
* ����汾: V1.2
* ��������: 2012/01/20
* ��������: ���ֲ�����GUI����.
**********************************************************************************/

/* Includes ---------------------------------------------------------------------*/
#include "includes.h"

/* �������� ---------------------------------------------------------------------*/
extern volatile INT8U menuflag; /* �˵���ʶ */ 

/*********************************************************************************
** ��������: void GuiMusicPlayer(void).
** ��������: ���ֲ�����GUI.
** �������: None.         
** �������: None.
** ���ز���: None.
**********************************************************************************/
void GuiMusicPlayer(void)
{
	INT8U i;
	menuflag = MAINMENU_MUSIC; /* �˵���ʶ 1 */
	CreateWindow("Music Player",30,30,330,165,Black);	/* �������� */
	GUIProgressBar(70,180,250,6,0);						/* ������ */
	GUIPlay(170,150,White);    /* ����ͼ�� */
	GUIPause(200,150,White);   /* ��ͣ��ť */ 
	/* ��һ�� */
	GUIUpSong(90,150,White);
	/* ��һ�� */
	GUIDownSong(295,150,White);
	LCD_FilledRectangle(70,145,250,2,White);	    /* width : 250  high : 6 */
	/* ������ʾ */	                                         
	LCD_Write_String(68,68,"VOL",White,Back_Color,0);
	GUIVolumeico(95,80,38);
	/* �������� */
	LCD_Write_String(128,68,"  Title",String_Color,Back_Color,1);
	/* ����ʱ�� */
	Lcd_WriteNumlen(2,0,230,68,White,Back_Color,1);	      	     /* ����ʱ��  �� */
	LCD_Write_String(247,68,":",White,Back_Color,1);	         /* ����ʱ��  ":" */
	Lcd_WriteNumlen(2,0,256,68,White,Back_Color,1);              /* ����ʱ��  �� */
	LCD_Write_String(273,68,"/",White,Back_Color,1);	         /* ����ʱ��  "/" */
	/* ��ʱ�� */
	Lcd_WriteNumlen(2,0,281,68,White,Back_Color,1);     	     /* ��ʱ��  �� */
	LCD_Write_String(297,68,":",White,Back_Color,1);	     /* ��ʱ��  ":" */
	Lcd_WriteNumlen(2,0,305,68,White,Back_Color,1);	             /* ��ʱ��  �� */
	/* Ƶ����ʾ */
	for(i=0;i<28;i++)
    {
        if(i < 14)
			LCD_FilledRectangle(110 + (i*6),145-i*2,5,i*2,Green);	        /* ���� width : *  high :  */
		if(i == 4 )
			LCD_FilledRectangle(110 + (i*6),145-34,5,34,Green);	        /* ���� width : *  high :  */
		if(i == 8 )
			LCD_FilledRectangle(110 + (i*6),145-38,5,38,Green);	        /* ���� width : *  high :  */
		if(i == 12 )
			LCD_FilledRectangle(110 + (i*6),145-30,5,30,Green);	        /* ���� width : *  high :  */
		if(i >= 14 && i < 22)
			LCD_FilledRectangle(110 + (i*6),145-(28 - i)*2,5,(28 - i)*2,Green);	        /* ���� width : *  high :  */
		if(i == 20)
			LCD_FilledRectangle(110 + (i*6),145-50,5,50,Green);	        /* ���� width : *  high :  */
		if(i >= 22)
			LCD_FilledRectangle(110 + (i*6),145-i,5,i,Green);	        /* ���� width : *  high :  */					
    }
	
}

