/******************** (C) COPYRIGHT 2012 BOOLESION.NET ***************************
* ��Ʒ����: BNOS 2012
* �ļ�����: en.c
* ��������: BOOLESION.NET ������(BOOLESION)���ӿƼ� - NETC (�½���)
* ����汾: V1.2
* ��������: 2012/03/20
* ��������: ϵͳ����: English.
**********************************************************************************/

/* Includes ---------------------------------------------------------------------*/
#include "includes.h"



/*********************************************************************************
** ��������: void SelectTitle(INT8U menutitle,INT8U action).
** ��������: ����ѡ����ʾ״̬.
** �������: INT8U menutitle ������,INT8U action ѡ��״̬ 0 δѡ�� 1 ѡ��.         
** �������: None.
** ���ز���: None.
**********************************************************************************/
void ENSelectTitle(INT8U menutitle,INT8U action)
{

	if(action == 1)	 /* ѡ��״̬ */
	{ 
		switch(menutitle)
		{
			case 1:	LCD_Write_String(52,85,"Music",WALLCOLOR,MENUCOLOR,1);
			break;
			case 2: LCD_Write_String(138,85,"Photos",WALLCOLOR,MENUCOLOR,1);
			break;
			case 3: LCD_Write_String(222,85,"Radio",WALLCOLOR,MENUCOLOR,1);
			break;
			case 4:	LCD_Write_String(292,85,"Calendar",WALLCOLOR,MENUCOLOR,1);
			break;
			case 5:	LCD_Write_String(52,175,"Ebook",WALLCOLOR,MENUCOLOR,1);
			break;
			case 6: LCD_Write_String(126,175,"Calculator",WALLCOLOR,MENUCOLOR,1);
			break;
			case 7: LCD_Write_String(232,175,"App",WALLCOLOR,MENUCOLOR,1);
			break;
			case 8: LCD_Write_String(292,175,"Settings",WALLCOLOR,MENUCOLOR,1);
			break;
		}
	}
	else if(action == 0)	 /* δѡ��״̬ */
	{
		switch(menutitle)
		{
		
			case 1:	LCD_Write_String(52,85,"Music",MENUCOLOR,WALLCOLOR,1);
			break;
			case 2: LCD_Write_String(138,85,"Photos",MENUCOLOR,WALLCOLOR,1);
			break;
			case 3: LCD_Write_String(222,85,"Radio",MENUCOLOR,WALLCOLOR,1);
			break;
			case 4:	LCD_Write_String(292,85,"Calendar",MENUCOLOR,WALLCOLOR,1);
			break;
			case 5:	LCD_Write_String(52,175,"Ebook",MENUCOLOR,WALLCOLOR,1);
			break;
			case 6: LCD_Write_String(126,175,"Calculator",MENUCOLOR,WALLCOLOR,1);
			break;
			case 7: LCD_Write_String(232,175,"App",MENUCOLOR,WALLCOLOR,1);
			break;
			case 8: LCD_Write_String(292,175,"Settings",MENUCOLOR,WALLCOLOR,1);
			break;	
		}
	}		
}
