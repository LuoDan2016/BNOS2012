/******************** (C) COPYRIGHT 2012 BOOLESION.NET ***************************
* ��Ʒ����: ������51������ E1101
* �ļ�����: mousekey.c.c
* ��������: BOOLESION.NET ������(BOOLESION)���ӿƼ� - NETC (�½���)
* ����汾: V1.1
* ��������: 2012/01/20
* ��������: �����������.
**********************************************************************************/

/* Includes ---------------------------------------------------------------------*/
#include "includes.h"

/* �������� ---------------------------------------------------------------------*/
/* ���ȫ�ֱ�������������ʼ�� */
volatile INT16U getcolor[12],xcoordinate=20,ycoordinate=50;

/*********************************************************************************
** ��������: void MouseInit(INT16U x,INT16U y).
** ��������: ����ʼ��.
** �������: INT16U x,INT16U y.         
** �������: None.
** ���ز���: None.
**********************************************************************************/
void MouseInit(INT16U x,INT16U y)
{
	INT8U i;
	xcoordinate = x;
	ycoordinate = y;
	for(i=0;i<12;i++)
	{
		getcolor[i]  =	LCD_GetPoint(xcoordinate + i,ycoordinate);
		if(i >5 )
			LCD_DrawPoint(xcoordinate + i,ycoordinate,Red);
		else
			LCD_DrawPoint(xcoordinate + i,ycoordinate,White);			
	}	
}

/*********************************************************************************
** ��������: void MouseScan(void).
** ��������: ���ɨ�����.
** �������: None.         
** �������: None.
** ���ز���: None.
**********************************************************************************/
void MouseScan(void)
{
	INT8U i;

	/* ���� */   
	if(!KEY_NEXT && (xcoordinate < 399))  /* ����ƶ����� */
	{
		for(i=0;i<12;i++)	              /* ���ԭ������ɫ */
		{
			LCD_DrawPoint(xcoordinate+i,ycoordinate,getcolor[i]);	
		}	
		xcoordinate++;		              /* ����ֵ����*/
		for(i=0;i<12;i++)	              /* ��ȡ��ǰ������ɫ */
		{
			getcolor[i]  =	LCD_GetPoint(xcoordinate + i,ycoordinate);	
		}
		for(i=0;i<12;i++)	              /* �ƶ���� */
		{
			if(i >5 )
			LCD_DrawPoint(xcoordinate + i,ycoordinate,Red);
			else
			LCD_DrawPoint(xcoordinate + i,ycoordinate,White);			
		}
	}
	/* ���� */
	if(!KEY_PRE && (xcoordinate > 0))
	{
		for(i=0;i<12;i++)	   /* ���ԭ������ɫ */
		{
		LCD_DrawPoint(xcoordinate+i,ycoordinate,getcolor[i]);	
		}
			xcoordinate--;
		for(i=0;i<12;i++)	   /* ��ȡ��ǰ������ɫ */
		{
			getcolor[i]  =	LCD_GetPoint(xcoordinate + i,ycoordinate);	
		}
		for(i=0;i<12;i++)
		{
			if(i >5 )
			LCD_DrawPoint(xcoordinate + i,ycoordinate,Red);
			else
			LCD_DrawPoint(xcoordinate + i,ycoordinate,White);			
		}
	}
	/* ���� */
	if(!KEY_DOWN_EXIT && (ycoordinate < 239))
	{
		for(i=0;i<12;i++)	   /* ���ԭ������ɫ */
		{
			LCD_DrawPoint(xcoordinate+i,ycoordinate,getcolor[i]);	
		}
		ycoordinate++;
		for(i=0;i<12;i++)	   /* ��ȡ��ǰ������ɫ */
		{
			getcolor[i]  =	LCD_GetPoint(xcoordinate + i,ycoordinate);	
		}
		for(i=0;i<12;i++)
		{
			if(i >5 )
			LCD_DrawPoint(xcoordinate + i,ycoordinate,Red);
			else
			LCD_DrawPoint(xcoordinate + i,ycoordinate,White);			
		}
		/* 
		** ��Ļ��������,����Ѱ������
		** Lcd_WriteNumlen(3,xcoordinate,50,2,White,Black,1);
		** Lcd_WriteNumlen(3,ycoordinate,80,2,White,Black,1);
		 */

	}
	/* ���� */
	if(!KEY_UP_VOL && (ycoordinate > 0))
	{
		for(i=0;i<12;i++)	   /* ���ԭ������ɫ */
		{
			LCD_DrawPoint(xcoordinate+i,ycoordinate,getcolor[i]);	
		}	
		ycoordinate--;
		for(i=0;i<12;i++)	   /* ��ȡ��ǰ������ɫ */
		{
			getcolor[i]  =	LCD_GetPoint(xcoordinate + i,ycoordinate);	
		}
		for(i=0;i<12;i++)
		{
			if(i >5 )
			LCD_DrawPoint(xcoordinate + i,ycoordinate,Red);
			else
			LCD_DrawPoint(xcoordinate + i,ycoordinate,White);			
		}
	}
}