/******************** (C) COPYRIGHT 2012 BOOLESION.NET ***************************
* ��Ʒ����: ������51������ E1101
* �ļ�����: guicalendar.c
* ��������: BOOLESION.NET ������(BOOLESION)���ӿƼ� - NETC (�½���)
* ����汾: V1.2
* ��������: 2012/01/20
* ��������: ������GUI.
**********************************************************************************/

/* Includes ---------------------------------------------------------------------*/
#include "includes.h"

/* �������� ---------------------------------------------------------------------*/
extern volatile INT8U menuflag; /* �˵���ʶ */ 
extern SYS_TIME datetime;	    /* ϵͳʱ�� */
extern INT8U code *WEEKS[7];

/*********************************************************************************
** ��������: void GUICalendar(void).
** ��������: ������GUI.
** �������: None.         
** �������: None.
** ���ز���: None.
**********************************************************************************/
void GUICalendar(void)
{
	menuflag = MAINMENU_CALENDAR;        /* �˵���ʶ 2 */
	datetime.week = GetWeekMaxDay(datetime.year,datetime.mon,datetime.day) >> 5; /* ������� */
	CreateWindow("Calendar",30,30,330,165,White);	/* �������� */
	LCD_FilledRectangle(132,50,2,140,Gray);         /* �ָ��� width : 2  high : 120 */
	LCD_Write_String(60,60,"TODAY",Black,White,0);
 	Lcd_WriteNumlen(4,BcdToBin(datetime.year >> 8)*0x64 +  BcdToBin(datetime.year&0xff),40,80,Blue,White,1);  /* �� */
	LCD_Write_String(73,80,"/",Blue,White,0);
	Lcd_WriteNumlen(2,BcdToBin(datetime.mon),82,80,Blue,White,1);	          /* �� */
	LCD_Write_String(99,80,"/",Blue,White,0);
	Lcd_WriteNumlen(2,BcdToBin(datetime.day),108,80,Blue,White,1);            /* �� */
	LCD_Write_String(60,110,WEEKS[datetime.week],Red,White,0);                /* ���� */

	GUIUp(180,50,Black);   /* ��һ�� */
	GUIDown(320,50,Black);	/* ��һ�� */

	Lcd_WriteNumlen(4,BcdToBin(datetime.year >> 8)*0x64 +  BcdToBin(datetime.year&0xff),40+178,54,Blue,White,1);	          /* �� */
	LCD_Write_String(73+178,54,"/",Blue,White,0);
	Lcd_WriteNumlen(2,BcdToBin(datetime.mon),82+178,54,Blue,White,1);	          /* �� */

	/* ���� */
	LCD_FilledRectangle(138,80,218,1,Gray);         /*  width : 204  high : 1 */
	LCD_Write_String(140,84,"SUN MON TUE WED THU FRI SAT",Black,White,0);
	LCD_FilledRectangle(138,102,218,1,Gray);        /*  width : 204  high : 1 */
}
