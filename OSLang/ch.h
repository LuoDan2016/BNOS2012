/******************** (C) COPYRIGHT 2012 BOOLESION.NET ***************************
* ��Ʒ����: BNOS 2012
* �ļ�����: chn.h
* ��������: BOOLESION.NET ������(BOOLESION)���ӿƼ� - NETC (�½���)
* ����汾: V1.2
* ��������: 2012/03/20
* ��������: ϵͳ����:����.
**********************************************************************************/

/* Includes ---------------------------------------------------------------------*/
#include "includes.h"
/* �������� */
void CHSelectTitle(INT8U menutitle,INT8U action);
#define CH_BNOSSTARTING	LCD_Write_String(2,LCD_YSIZE_TFT - 42,"BNOS 2012 ������...",Green,Blue,1)

/* ���˵����� */
/* ��һ�в˵�ͼ�� */
/* ���ֲ˵����� */
/* ���˵����� */
/* �����˵������ */
/* �����˵����� */
/* �ڶ��в˵�ͼ�� */
/* ������˵����� */
/* �������˵����� */
/* Ӧ�ó���˵����� */
/* ϵͳ���ò˵����� */	
#define CH_MAINMENUTITLE	;\
	LCD_Write_String(49,85,"������",MENUCOLOR,WALLCOLOR,1);\		        
	LCD_Write_String(147,85,"���",MENUCOLOR,WALLCOLOR,1);\		
	LCD_Write_String(219,85,"������",MENUCOLOR,WALLCOLOR,1);\		
	LCD_Write_String(299,85,"������",MENUCOLOR,WALLCOLOR,1);\		  
	LCD_Write_String(49,175,"������",MENUCOLOR,WALLCOLOR,1);\			
	LCD_Write_String(139,175,"������",MENUCOLOR,WALLCOLOR,1);\	   
	LCD_Write_String(229,175,"����",MENUCOLOR,WALLCOLOR,1);\				
	LCD_Write_String(308,175,"����",MENUCOLOR,WALLCOLOR,1);\
/*  ѡ�б��� */
#define CH_MAINMENUSEL(menutitle,action) CHSelectTitle(menutitle,action)
