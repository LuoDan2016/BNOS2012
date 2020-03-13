#include "includes.h"

extern volatile INT8U menuflag;     /* �˵���ʶΪ */
extern volatile INT8U mainmenuflag; /*���˵���ʶ  */
extern INT32U frequency; /* FMƵ������ */

 /* ͼ�궯�� Ƶ�ʼ�С */
void GUIFreqDown(void)
{
	GUIUpSong(90,150,Green);	        
	OSTimeDly(10);
	GUIUpSong(90,150,White);
}

/* ͼ�궯�� Ƶ������ */
void GUIFreqUp(void)
{
	GUIDownSong(295,150,Green);	       
	OSTimeDly(10);
	GUIDownSong(295,150,White);
}

void FMRadio(void)
{
	INT8U fmmode = 0;
	FM_SW=1;             /* FMʹ����� */
	VS_RST = 0;          /* VS1003 ����� */
	
   radio_write();        /* д��TEA5767����,��ʼ��*/

   while(1)
   {
		/* һ�г���ʵ��STC���ϵ��Զ�����(���ͷ�ļ�δ����IAP_CONTR�Ĵ���,��while�����м���if(P3==(P3&0xFE))IAP_CONTR=0x60;
		** �趨����#include<reg52.h>�м���sfr IAP_CONTR = 0xC7; )ԭ��BOOLESION.NET  -NETC */
		if(P3==(P3&0xFE))IAP_CONTR=0x60;

		/* ���� KEY_DOWN_EXIT �˳����������˵� */
		if(!KEY_DOWN_EXIT)					
		{
			radio_close();	 /* �ر�FM */
		 	menuflag     = 0;
		    mainmenuflag = 0;
			break;			
		}
		/* �ֶ���̨ */
		if(KEY_PRE == 0)     /* ����KEY_NEXTƵ�ʼ�С */
		{ 
			/* Ƶ����ʾ */
			FreqShow(frequency);
			GUIFreqDown();   /* ͼ���ɫ����ʱ���� */
			search(0);
			radio_read();
			OSTimeDly(10); /* ��ʱ */
		}
		
		if(KEY_NEXT == 0)     /* ����KEY_BACKƵ������ */
		{
			/* Ƶ����ʾ */
			FreqShow(frequency);
			GUIFreqUp();   /* ͼ���ɫ����ʱ���� */
			search(1);
			radio_read();
			OSTimeDly(10); /* ��ʱ */
		}
		if(KEY_ENTER==0)     /* ����KEY_ENTER��ͣ */
		{
			if(fmmode == 0)	  /* ��ͣ */
			{
				radio_close();
				fmmode = 1;	
				GUIPlay(170,150,White);    /* ����ͼ�� */
				GUIPause(200,150,Green);   /* ��ͣ��ť */ 
			}
			else			 /* ���� */
			{
				radio_write(); 
				fmmode = 0;
				GUIPlay(170,150,Green);    /* ����ͼ�� */
				GUIPause(200,150,White);   /* ��ͣ��ť */ 		
			}
			OSTimeDly(20); /* ��ʱ */
		}
	}
}
