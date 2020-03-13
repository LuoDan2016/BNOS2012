/******************** (C) COPYRIGHT 2012 BOOLESION.NET *************************
* ��Ʒ����: ������51������ E1101
* �ļ�����: main.c
* ��������: BOOLESION.NET ������(BOOLESION)���ӿƼ� - NETC (�½���)
* ����汾: V1.2
* ��������: 2012/03/20
* ��������: BNOS 2012 ���񴴽����������������� RAM > 300 Byte �ں�CPU.
********************************************************************************
* CPU : 8051
* ʱ��: 22.1184Mhz
* ����������,�㷨Ϊ(BOOLESION.NET)NETCԭ����ת����ע������.
*******************************************************************************/

/* Includes ------------------------------------------------------------------*/
#include "includes.h"

/* ����������Ϊ�����ջ ------------------------------------------------------*/
OS_STK OSMainTaskStk   [MaxStkSize + 1];
OS_STK MenuAppTaskStk  [MaxStkSize*2 + 1]; 
OS_STK OSTimeTaskStkc  [MaxStkSize + 1]; 
OS_STK SDCheckTaskStkd [MaxStkSize + 1]; 

/* �������� ------------------------------------------------------------------*/
/* ���������� ----------------------------------------------------------------*/

/******************************************************************************
** ��������: main.
** ��������: ����������.
** �������: None.         
** �������: None
** ���ز���: None
*******************************************************************************/
void main(void)
{	
	/* �豸��ʼ�� */
	DeviceInit();
	/* ϵͳ�ֿ⼰GUI���ݴ��� */
	FontGUILoad();
	/* ������LOGO��Ϣ */
	GUI_BRCLOGO();
	COMNLANG_COPYRIGHT;
	/* �������� */	
	GUIProgressBar(0,LCD_YSIZE_TFT - 6,400,6,100);
	/* OS Start */		
	OSInit();
	OSTaskCreate(OSMainTask,(void*)0,&OSMainTaskStk[0],OSMAINTASK); 
	OSTaskCreate(MenuApp,(void*)0,&MenuAppTaskStk[0],MENUAPP);
	OSTaskCreate(OSTimeTask,(void*)0,&OSTimeTaskStkc[0],OSTIMETASK);
	OSStart(); 
}

