/******************** (C) COPYRIGHT 2012 BOOLESION.NET ***************************
* ��Ʒ����: ������51������ E1101
* �ļ�����: helloworld.c
* ��������: BOOLESION.NET ������(BOOLESION)���ӿƼ� - NETC (�½���)
* ����汾: V1.2
* ��������: 2012/01/20
* ��������: Ӧ�ó�������.
**********************************************************************************/

/* Includes ---------------------------------------------------------------------*/
#include "includes.h"

/* �������� ---------------------------------------------------------------------*/
extern volatile INT8U menuflag;     /* �˵���ʶΪ */
extern volatile INT8U mainmenuflag; /* ���˵���ʶ */

/*********************************************************************************
** ��������: void HelloWorld(void).
** ��������: Ӧ�ó�������.
** �������: None.         
** �������: None.
** ���ز���: None.
**********************************************************************************/
void HelloWorld(void)
{
	INT8U menucount = 2;
	LCD_Write_String(150,100,"Hello World!",Black,White,0);	  /* "Hello World!" */
	GUIButton(" CLOSE",220,150,70,25,RGB(220,220,220));	      /* δѡ�� CLOSE */	
	GUIButton("  OK",100,150,70,25,RGB(220,220,220));	      /* δѡ�� OK */
	while(1)
	{
		/* ���� KEY_DOWN_EXIT �˳����������˵� */
		if(!KEY_DOWN_EXIT)
		{
		 	menuflag     = 0;
		    mainmenuflag = 0;
		 	break;			
		}
	    if(!KEY_PRE)
	    {
		   menucount = 0;
		   GUIButton("  OK",100,150,70,25,RGB(110,110,110));	 /* ѡ�� OK */
		   GUIButton(" CLOSE",220,150,70,25,RGB(220,220,220));	 /* δѡ�� CLOSE */		
		}
		if(!KEY_NEXT)
	    {
		   menucount = 1;
		   GUIButton("  OK",100,150,70,25,RGB(220,220,220));	 /* δѡ�� OK */
		   GUIButton(" CLOSE",220,150,70,25,RGB(110,110,110));	 /* ѡ�� CLOSE */		
		}
		if(!KEY_ENTER)
		{
			if(menucount == 1)
			{
				 menuflag      = 0;
		   		 mainmenuflag = 0;
		 		 break;	
			}
			if(menucount  == 0)
			{
				CreateWindow("Hello World",95,60,200,80,White);	          /* �������� */
				LCD_Write_String(150,100,"Hello World!",Black,White,0);	  /* "Hello World!" */	
			}
		}

	}
}		