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
extern SYS_TIME datetime;	        /* ϵͳʱ�� */
volatile INT16U LcdBLsettime = 45;  /* LCD ����Ƚ�ֵ */

/*********************************************************************************
** ��������: void Settings(void).
** ��������: ϵͳ����.
** �������: None.         
** �������: None.
** ���ز���: None.
**********************************************************************************/
void Settings(void)
{
	INT8U menucount = 0;
	INT8U setday;
	setday = datetime.day;
	while(1)
	{
		
			/* ���� KEY_DOWN_EXIT �˳����������˵� */
		if(!KEY_DOWN_EXIT)					
		{
			radio_close();	 /* �ر�FM */
		 	menuflag     = 0;
		    mainmenuflag = 0;
			break;			
		}

		if(!KEY_NEXT)	/* ����ѡ���� */
		{
			if(menucount < 9)
			{
				menucount++;
				GUIButton(" EXIT",220,150,70,25,RGB(220,220,220));	 /* δѡ�� EXIT */	
				GUIButton("  OK",100,150,70,25,RGB(220,220,220));	 /* δѡ�� OK */
				GUIUp(210,52,Black);   	 /* ����ʱ�䰴ť�ָ� */
				GUIDown(280,52,Black);
				GUIUp(210,78,Black);   	 /* ϵͳʱ�� �� ��ť�ָ� */
				GUIDown(280,78,Black);
				GUIUp(210,104,Black);   /* ϵͳʱ�� �� ��ť�ָ� */
				GUIDown(280,104,Black);
				GUIUp(210,130,Black);   /* ϵͳʱ�� �� ��ť�ָ� */
				GUIDown(280,130,Black);
				OSTimeDly(10);  /* ��ʱ */	
			}
		}
		if(!KEY_PRE)  /* ����ѡ�м� */
		{
			if(menucount > 0)
			{
				menucount--;
				GUIButton(" EXIT",220,150,70,25,RGB(220,220,220));	 /* δѡ�� EXIT */	
				GUIButton("  OK",100,150,70,25,RGB(220,220,220));	 /* δѡ�� OK */
				GUIUp(210,52,Black);   	 /* ����ʱ�䰴ť�ָ� */
				GUIDown(280,52,Black);
				GUIUp(210,78,Black);   	 /* ϵͳʱ�� �� ��ť�ָ� */
				GUIDown(280,78,Black);
				GUIUp(210,104,Black);   /* ϵͳʱ�� �� ��ť�ָ� */
				GUIDown(280,104,Black);
				GUIUp(210,130,Black);   /* ϵͳʱ�� �� ��ť�ָ� */
				GUIDown(280,130,Black);
				OSTimeDly(10);  /* ��ʱ */
			}
		}
		if(menucount == 0)	 /* ���� ѡ�� ���� */
		{
			GUIUp(210,52,Green);
			if(!KEY_ENTER)
			{
				if(LcdBLsettime > 1)
					LcdBLsettime -= 1;
				Lcd_WriteNumlen(3,LcdBLsettime,232,54,String_Color,White,1);	/* ��ʾ ʱ�� second */
				OSTimeDly(5);  /* ��ʱ */
			} 
		}
		if(menucount == 1)	 /* ���� ѡ�� ����*/
		{
			GUIDown(280,52,Green);
			if(!KEY_ENTER)
			{
				if(LcdBLsettime < 300)
					LcdBLsettime += 1;
				Lcd_WriteNumlen(3,LcdBLsettime,232,54,String_Color,White,1);	/* ��ʾ ʱ�� second */
				OSTimeDly(5);  /* ��ʱ */
			}  
		}
		if(menucount == 2)	 /* ϵͳʱ���� ѡ������*/
		{
			GUIUp(210,78,Green);  
			if(!KEY_ENTER)
			{
				if(datetime.year < 0x9999)
					datetime.year++;
				Lcd_WriteNumlen(4,BcdToBin(datetime.year >> 8)*0x64 +  BcdToBin(datetime.year & 0xff),232,80,String_Color,White,1);	/* ��ʾ ʱ�� �� */
				OSTimeDly(5);  /* ��ʱ */
			}  
		}
		if(menucount == 3)	 /* ϵͳʱ���� ѡ�м���*/
		{
			GUIDown(280,78,Green);  
			if(!KEY_ENTER)
			{
				if(datetime.year > 0x0)
					datetime.year--;
				Lcd_WriteNumlen(4,BcdToBin(datetime.year >> 8)*0x64 +  BcdToBin(datetime.year & 0xff),232,80,String_Color,White,1);	/* ��ʾ ʱ�� �� */
				OSTimeDly(5);  /* ��ʱ */
			}  
		}
		if(menucount == 4)	 /* ϵͳʱ���� ѡ�м���*/
		{
			GUIUp(210,104,Green);  
			if(!KEY_ENTER)
			{
				if(datetime.mon > 0x1)
					datetime.mon--;
				Lcd_WriteNumlen(2,BcdToBin(datetime.mon),232,106,String_Color,White,1);	/* ��ʾ ʱ�� �� */
			    OSTimeDly(5);  /* ��ʱ */
			}  
		}
		if(menucount == 5)	 /* ϵͳʱ���� ѡ������*/
		{
			GUIDown(280,104,Green);  
			if(!KEY_ENTER)
			{
				if(datetime.mon < 0x12)
					datetime.mon++;
				Lcd_WriteNumlen(2,BcdToBin(datetime.mon),232,106,String_Color,White,1);	/* ��ʾ ʱ�� �� */
			    OSTimeDly(5);  /* ��ʱ */
			}  
		}
			if(menucount == 6)	 /* ϵͳʱ���� ѡ�м���*/
		{
			GUIUp(210,130,Green);  
			if(!KEY_ENTER)
			{
				if(setday > 0x1)
					setday--;
				datetime.day = setday;
				Lcd_WriteNumlen(2,setday,232,132,String_Color,White,1);	/* ��ʾ ʱ�� �� */
			    OSTimeDly(5);  /* ��ʱ */
			}  
		}
		if(menucount == 7)	 /* ϵͳʱ���� ѡ������*/
		{
			GUIDown(280,130,Green);  
			if(!KEY_ENTER)
			{
				
				if( setday < 31 )
					setday++;
				datetime.day = setday;
				Lcd_WriteNumlen(2,setday,232,132,String_Color,White,1);	/* ��ʾ ʱ�� �� */
			    OSTimeDly(5);  /* ��ʱ */
			}  
		}
		if(menucount == 8)	   /* OK */
		{
			GUIButton("  OK",100,150,70,25,RGB(110,110,110));	 /* δѡ�� OK */
			if(!KEY_ENTER)
			{
				 menuflag     = 0;
		   		 mainmenuflag = 0;
		 		 break;		
			}  
		}
		if(menucount == 9)	 /* EXIT */
		{
			GUIButton(" EXIT",220,150,70,25,RGB(110,110,110));	 /* δѡ�� EXIT */
			if(!KEY_ENTER)
			{
				 menuflag     = 0;
		   		 mainmenuflag = 0;
		 		 break;		
			}  
		}
	}		
}