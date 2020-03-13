/******************** (C) COPYRIGHT 2012 BOOLESION.NET ***************************
* ��Ʒ����: ������51������ E1101
* �ļ�����: guimainmenu.c
* ��������: BOOLESION.NET ������(BOOLESION)���ӿƼ� - NETC (�½���)
* ����汾: V1.2
* ��������: 2012/01/20
* ��������: �����洰��GUI����.
**********************************************************************************/

/* Includes ---------------------------------------------------------------------*/
#include "includes.h"

/* �������� ---------------------------------------------------------------------*/
extern SYS_TIME datetime;	    /* ϵͳʱ�� */
extern volatile INT8U menuflag; /* �˵���ʶΪ */ 
/*  �����ֿ����ʶ 1Ϊ��ȷ ���������� */
extern INT8U CHNCHEK;

/*********************************************************************************
** ��������: void GuiMainMenu(void).
** ��������: ��������GUI.
** �������: None.         
** �������: None.
** ���ز���: None.
**********************************************************************************/
void GUI_MainMenu(void)
{
	INT8U *DISLANG;
	INT8U res;
	switch(USELANG)	     /* ����ѡ�� */
		{
			case 0:			 /* English  */
				DISLANG = "EN";
			case 1:			 /* �������� */
				DISLANG = "CH";
			case 2:			 /* Ĭ������ */
			 	if(CHNCHEK)
					DISLANG = "CH";
				else
					DISLANG = "EN";	
		}	
	/* �����洰�� */
	/* ������ */	
	LCD_FilledRectangle(LCD_XSIZE_TFT - LCD_XSIZE_TFT,LCD_YSIZE_TFT - 24,LCD_XSIZE_TFT,1,RGB(127,127,127));
	LCD_FilledRectangle(LCD_XSIZE_TFT - LCD_XSIZE_TFT,LCD_YSIZE_TFT - 23,LCD_XSIZE_TFT,23,TASKBARCOLOR);/* ������ */
	Lcd_WriteNumlen(2,datetime.hour,LCD_XSIZE_TFT - 44,LCD_YSIZE_TFT - 16,White,TASKBARCOLOR,1);	    /* ʱ����ʾ */
	LCD_Write_String(LCD_XSIZE_TFT - 28,LCD_YSIZE_TFT - 16,":",White,TASKBARCOLOR,1);
	Lcd_WriteNumlen(2,datetime.min,LCD_XSIZE_TFT - 20,LCD_YSIZE_TFT - 16,White,TASKBARCOLOR,1);	
	GUIToolICOPower(340,220,8);	                                        /* ������ʾ */

	LCD_Write_String(310,LCD_YSIZE_TFT - 16,DISLANG,White,TASKBARCOLOR,1);	/* ϵͳ���� */
	LCD_FilledRectangle(4,LCD_YSIZE_TFT - 20,20,4,Magenta);	            /* ��ʼ�˵� */
	LCD_FilledRectangle(4,LCD_YSIZE_TFT - 14,20,4,Green);
	LCD_FilledRectangle(4,LCD_YSIZE_TFT - 8,20,4,Blue2);
}

/*********************************************************************************
** ��������: void MainIco(void).
** ��������: ������˵�ICO.
** �������: None.         
** �������: None.
** ���ز���: None.
**********************************************************************************/
void MainIco(void)
{
	/* ���˵���ʶΪMAINMENU 0 */
	menuflag = MAINMENU;      
	/* ��һ�в˵�ͼ�� */
	LCD_Write_String(44 ,98,"Music",NotselColor,Back_Color,0);		        /* ���ֲ˵����� */
   	LCD_Write_String(128,98,"Photos",NotselColor,Back_Color,0);				/* ���˵����� */
	LCD_Write_String(218,98,"Radio",NotselColor,Back_Color,0);				/* �����˵������ */
	LCD_Write_String(294,98,"Calendar",NotselColor,Back_Color,0);		    /* �����˵����� */
	/* �ڶ��в˵�ͼ�� */
	LCD_Write_String(48 ,179,"Ebook",NotselColor,Back_Color,0);			    /* ������˵����� */
   	LCD_Write_String(110,179,"Calculator",NotselColor,Back_Color,0);	    /* �������˵����� */
	LCD_Write_String(228,179,"App",NotselColor,Back_Color,0);				/* Ӧ�ó���˵����� */
	LCD_Write_String(296,179,"Settings",NotselColor,Back_Color,0);		    /* ϵͳ���ò˵����� */	
}
