/******************** (C) COPYRIGHT 2012 BOOLESION.NET ***************************
* ��Ʒ����: ������51������ E1101
* �ļ�����: guisettings.c
* ��������: BOOLESION.NET ������(BOOLESION)���ӿƼ� - NETC (�½���)
* ����汾: V1.2
* ��������: 2012/01/20
* ��������: ϵͳ����GUI.
**********************************************************************************/

/* Includes ---------------------------------------------------------------------*/
#include "includes.h"

/* �������� ---------------------------------------------------------------------*/
extern volatile INT8U menuflag; /* �˵���ʶ */ 
extern volatile INT16U LcdBLsettime; /* LCD ����Ƚ�ֵ */
extern SYS_TIME datetime;	 /* ϵͳʱ�� */

/*********************************************************************************
** ��������: void GUISettings(void).
** ��������: ϵͳ����GUI.
** �������: None.         
** �������: None.
** ���ز���: None.
**********************************************************************************/
void GUISettings(void)
{
	menuflag = MAINMENU_SETTINGS;                   /* �˵���ʶ */
	CreateWindow("Settings",30,30,330,165,White);	/* �������� */
    GUIButton(" EXIT",220,150,70,25,RGB(220,220,220));	 /* δѡ�� EXIT */	
	GUIButton("  OK",100,150,70,25,RGB(220,220,220));	 /* δѡ�� OK */
	/* ����ʱ������ */
	LCD_Write_String(50,54,"Backlight Time(s):",Black,White,0);	  /* "Backlight Time" */
	/* ���ٱ���ʱ�� */
	GUIUp(210,52,Black);   
	Lcd_WriteNumlen(3,LcdBLsettime,232,54,String_Color,White,1);	/* ��ʾ ʱ�� second */
	/* ���ӱ���ʱ�� */
	GUIDown(280,52,Black);	
	/* ϵͳʱ������ */
	LCD_Write_String(50,80,"System year:",Black,White,0);	  /* "System year" */
	/* ����ʱ�� �� �� */
	GUIUp(210,78,Black);   
	Lcd_WriteNumlen(4,BcdToBin(datetime.year >> 8)*0x64 +  BcdToBin(datetime.year & 0xff),232,80,String_Color,White,1);	/* ��ʾ ʱ�� �� */
	/* ����ʱ�� �� �� */
	GUIDown(280,78,Black);
	LCD_Write_String(50,106,"System mon:",Black,White,0);	  /* "System mon" */
	/* ����ʱ�� �� �� */
	GUIUp(210,104,Black);   
	Lcd_WriteNumlen(2,BcdToBin(datetime.mon),232,106,String_Color,White,1);	/* ��ʾ ʱ�� �� */
	/* ����ʱ�� �� �� */
	GUIDown(280,104,Black);
	LCD_Write_String(50,132,"System day:",Black,White,0);	  /* "System day" */
	/* ����ʱ�� �� �� */
	GUIUp(210,130,Black);   
	Lcd_WriteNumlen(2,BcdToBin(datetime.day),232,132,String_Color,White,1);	/* ��ʾ ʱ�� �� */
	/* ����ʱ�� �� �� */
	GUIDown(280,130,Black);

}

