/******************** (C) COPYRIGHT 2012 BOOLESION.NET ***************************
* ��Ʒ����: BNOS 2012
* �ļ�����: en.h
* ��������: BOOLESION.NET ������(BOOLESION)���ӿƼ� - NETC (�½���)
* ����汾: V1.2
* ��������: 2012/03/20
* ��������: ϵͳ����:English.
**********************************************************************************/

/* Includes ---------------------------------------------------------------------*/
#include "includes.h"
/* �������� */
void ENSelectTitle(INT8U menutitle,INT8U action);
#define EN_BNOSSTARTING LCD_Write_String(2,LCD_YSIZE_TFT - 42,"BNOS 2012 LOADING...",Green,Blue,1)

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
#define EN_MAINMENUTITLE  ;\
	LCD_Write_String(52,85,"Music",MENUCOLOR,WALLCOLOR,0);\		        
	LCD_Write_String(138,85,"Photos",MENUCOLOR,WALLCOLOR,0);\		
	LCD_Write_String(222,85,"Radio",MENUCOLOR,WALLCOLOR,0);\		
	LCD_Write_String(292,85,"Calendar",MENUCOLOR,WALLCOLOR,0);\		  
	LCD_Write_String(52,175,"Ebook",MENUCOLOR,WALLCOLOR,0);\			
	LCD_Write_String(126,175,"Calculator",MENUCOLOR,WALLCOLOR,0);\	   
	LCD_Write_String(232,175,"App",MENUCOLOR,WALLCOLOR,0);\				
	LCD_Write_String(292,175,"Settings",MENUCOLOR,WALLCOLOR,0);\		  	
/*  ѡ�б��� */
#define EN_MAINMENUSEL(menutitle,action) ENSelectTitle(menutitle,action);