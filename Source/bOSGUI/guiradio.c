/******************** (C) COPYRIGHT 2012 BOOLESION.NET ***************************
* ��Ʒ����: ������51������ E1101
* �ļ�����: guiradio.c
* ��������: BOOLESION.NET ������(BOOLESION)���ӿƼ� - NETC (�½���)
* ����汾: V1.2
* ��������: 2012/01/20
* ��������: ������GUI.
**********************************************************************************/

/* Includes ---------------------------------------------------------------------*/
#include "includes.h"

/* �������� ---------------------------------------------------------------------*/

extern volatile INT8U menuflag;     /* �˵���ʶ */ 
extern volatile INT8U mainmenuflag; /* ���˵���ʶ */
extern INT32U frequency; /* FMƵ������ */
/*********************************************************************************
** ��������: void GUIRadio(void).
** ��������: ������GUI.
** �������: None.         
** �������: None.
** ���ز���: None.
**********************************************************************************/
void GUIRadio(void)
{
	menuflag = MAINMENU_RADIO;                      /* �˵���ʶ 2 */
    CreateWindow("FM Radio",30,30,330,165,Black);	/* �������� */

	GUIPlay(170,150,Green);    /* ����ͼ�� */
	GUIPause(200,150,White);   /* ��ͣ��ť */ 
	/* ��һ�� */
	GUIUpSong(90,150,White);
	/* ��һ�� */
	GUIDownSong(295,150,White);
	LCD_FilledRectangle(70,145,250,2,White);	    /* width : 250  high : 6 */


	/* Ƶ����ʾ */
	LCD_Write_String(68+50,90,"FM FREQ:",White,Back_Color,0);
	LCD_Write_String(70,128,"87.5 MHz",White,Back_Color,0);
	LCD_Write_String(270,128,"108 MHz",White,Back_Color,0);
	LCD_Write_String(178+50,90,"MHz",White,Back_Color,0);				      /* MHz */
	FreqShow(frequency);						
	GUIProgressBar2(70,120,250,6,100 * ((FP32)((frequency/100) - 870) / (FP32)(1080 - 870)) );	  /* Ƶ�ʽ����� */

}