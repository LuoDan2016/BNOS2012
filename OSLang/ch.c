/******************** (C) COPYRIGHT 2012 BOOLESION.NET ***************************
* ��Ʒ����: BNOS 2012
* �ļ�����: chn.c
* ��������: BOOLESION.NET ������(BOOLESION)���ӿƼ� - NETC (�½���)
* ����汾: V1.2
* ��������: 2012/03/20
* ��������: ϵͳ����:����.
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
void CHSelectTitle(INT8U menutitle,INT8U action)
{

	if(action == 1)	 /* ѡ��״̬ */
	{ 
		switch(menutitle)
		{
			case 1:	LCD_Write_String(49,85,"������",WALLCOLOR,MENUCOLOR,1);
			break;
			case 2: LCD_Write_String(147,85,"���",WALLCOLOR,MENUCOLOR,1);
			break;
			case 3: LCD_Write_String(219,85,"������",WALLCOLOR,MENUCOLOR,1);
			break;
			case 4:	LCD_Write_String(299,85,"������",WALLCOLOR,MENUCOLOR,1);
			break;
			case 5:	LCD_Write_String(49,175,"������",WALLCOLOR,MENUCOLOR,1);
			break;
			case 6: LCD_Write_String(139,175,"������",WALLCOLOR,MENUCOLOR,1);
			break;
			case 7: LCD_Write_String(229,175,"����",WALLCOLOR,MENUCOLOR,1);
			break;
			case 8: LCD_Write_String(308,175,"����",WALLCOLOR,MENUCOLOR,1);
			break;
		}
	}
	else if(action == 0)	 /* δѡ��״̬ */
	{
		switch(menutitle)
		{
		
			case 1:	LCD_Write_String(49,85,"������",MENUCOLOR,WALLCOLOR,1);
			break;
			case 2: LCD_Write_String(147,85,"���",MENUCOLOR,WALLCOLOR,1);
			break;
			case 3: LCD_Write_String(219,85,"������",MENUCOLOR,WALLCOLOR,1);
			break;
			case 4:	LCD_Write_String(299,85,"������",MENUCOLOR,WALLCOLOR,1);
			break;
			case 5:	LCD_Write_String(49,175,"������",MENUCOLOR,WALLCOLOR,1);
			break;
			case 6: LCD_Write_String(139,175,"������",MENUCOLOR,WALLCOLOR,1);
			break;
			case 7: LCD_Write_String(229,175,"����",MENUCOLOR,WALLCOLOR,1);
			break;
			case 8: LCD_Write_String(308,175,"����",MENUCOLOR,WALLCOLOR,1);
			break;	
		}
	}		
}
