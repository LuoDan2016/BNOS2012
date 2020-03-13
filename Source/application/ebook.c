/******************** (C) COPYRIGHT 2012 BOOLESION.NET ***************************
* ��Ʒ����: ������51������ E1101
* �ļ�����: ebook.c
* ��������: BOOLESION.NET ������(BOOLESION)���ӿƼ� - NETC (�½���)
* ����汾: V1.2
* ��������: 2012/01/20
* ��������: ������Ӧ�ó���.
**********************************************************************************/

/* Includes ---------------------------------------------------------------------*/
#include "includes.h"

/* �������� ---------------------------------------------------------------------*/ 
extern volatile INT8U menuflag;     /* �˵���ʶΪ */
extern volatile INT8U mainmenuflag; /* ���˵���ʶ   */
extern unsigned char filecount;     /* �ļ����� */

/* �ļ�ϵͳ���ȫ�ֱ������� */
extern volatile FRESULT res;
extern volatile FATFS fs;	
extern volatile INT16U br,i,j;
volatile BYTE   ebuff[38];    /* �ļ����� */

/*********************************************************************************
** ��������: void EbookView(void).
** ��������: �����鴦��.
** �������: None.         
** �������: None.
** ���ز���: None.
**********************************************************************************/
void EbookView(void)
{
	INT16U row = 0 ,page = 0;	       /* row�� pageҳ */
	res = pf_open("ebook/vs1003.txt"); /* ���ļ� */
	while(1)
	{
		/* ���� KEY_DOWN_EXIT �˳����������˵� */
		if(!KEY_DOWN_EXIT)
		{
		 	menuflag     = 0;
		    mainmenuflag = 0;
			break;			
		}

		if(row == 0)                             /* ��ʾ��һҳ */
		{
			for(i=0;i<7;i++)
			{
				pf_lseek(row * 38);
				res = pf_read(ebuff,38,&br);	  /*���ļ�TXT�ļ�*/ 		 
				LCD_Write_String(40,50 + (i * 16),ebuff,Black,White,1);
				if(i > 0)
					if(ebuff[0] != 32)
						LCD_Write_String(40 + 38 * 8,50 + ((i-1) * 16),"-",Black,White,1);
				row++;				
			}
		}
		if(KEY_NEXT == 0 && (!(res || br == 0)))          /* ��һҳ */
		{
			GUIDown(320,170,Green);	                      /* ��һҳ��ť */
			LCD_FilledRectangle(40,50,316,118,White);     /* ������ʾ���� */
			for(i=0;i<7;i++)
			{
				
				row++;
				pf_lseek(row * 38);
				res = pf_read(ebuff,38,&br);	              /* ���ļ�TXT�ļ� */ 
				if(res || br == 0) break;	              /* ���ļ����� */		 
				LCD_Write_String(40,50 + (i * 16),ebuff,Black,White,1);
				if(i > 0)
					if(ebuff[0] != 32)
						LCD_Write_String(40 + 38 * 8,50 + ((i-1) * 16),"-",Black,White,1);		
			}
			GUIDown(320,170,Black);	                      /* ��һҳ��ť */	
		}
		if(KEY_PRE == 0 && (row > 7))                    /* ��һҳ */
		{
			GUIUp(70,170,Green);	                      /* ��һҳ��ť */
			LCD_FilledRectangle(40,50,316,118,White);     /* ������ʾ���� */
			row -= 14;
			for(i=0;i<7;i++)
			{
				pf_lseek(row * 38);
				res = pf_read(ebuff,38,&br);	              /*���ļ�TXT�ļ�*/ 
				if(res || br == 0) break;	              /*���ļ�����*/		 
				LCD_Write_String(40,50 + (i * 16),ebuff,Black,White,1);
				if(i > 0)
					if(ebuff[0] != 32)
						LCD_Write_String(40 + 38 * 8,50 + ((i-1) * 16),"-",Black,White,1);		
				row++;
			}
			GUIUp(70,170,Black);	                      /* ��һҳ��ť */	
		}



	}	

}