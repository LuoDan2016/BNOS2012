/******************** (C) COPYRIGHT 2012 BOOLESION.NET ***************************
* ��Ʒ����: ������51������ E1101
* �ļ�����: calculator.c
* ��������: BOOLESION.NET ������(BOOLESION)���ӿƼ� - NETC (�½���)
* ����汾: V1.2
* ��������: 2012/01/20
* ��������: ������Ӧ�ó���.
**********************************************************************************/

/* Includes ---------------------------------------------------------------------*/
#include "includes.h"

/* �������� ---------------------------------------------------------------------*/
extern volatile INT8U menuflag;     /* �˵���ʶΪ */
extern volatile INT8U mainmenuflag; /* ���˵���ʶ */
extern INT8U*  code btndata[4][4];

/*********************************************************************************
** ��������: void Calculator(void).
** ��������: ������������.
** �������: None.         
** �������: None.
** ���ز���: None.
**********************************************************************************/
void Calculator(void)
{
	INT8U selflag=0,calflag=0,datalen=0,i,j,caltype = 0; /* ���㶨�� */
	INT32U iuputdata = 0,iuputdata1 = 0,iuputdata2 = 0,calres = 0,temp = 0;
	while(1)
	{	/* ���� KEY_DOWN_EXIT �˳����������˵� */
		if(!KEY_DOWN_EXIT)
		{
		 	menuflag     = 0;
		    mainmenuflag = 0;
		 	break;			
		}
		
		if(selflag == 0 && calflag == 0)
		{
			selflag = 1;
			/* ���������ʾ */
			for(j=0;j<4;j++)
			{
				for(i=0;i<4;i++)
				{
					if(j==0 && i==0)
						GUIButton(btndata[j][i],42 + 12 * i + 20 * i,56+ 12 * j + 20 * j,30,30,RGB(110,110,110));/* ѡ�а�ť */
					else			
						GUIButton(btndata[j][i],42 + 12 * i + 20 * i,56+ 12 * j + 20 * j,30,30,RGB(220,220,220));/* ��ť */	
				}
			}
		}
		/* ��һ������ */
		if(!KEY_NEXT && calflag < 15)
		{
			if(calflag < 4)
				GUIButton(btndata[0][calflag],42 + 12 * calflag + 20 * calflag,56+ 12 * 0 + 20 * 0,30,30,RGB(220,220,220));/* ѡ�а�ť */	
			if(calflag >= 4  && calflag <= 7)
				GUIButton(btndata[1][calflag - 4],42 + 12 * (calflag - 4) + 20 * (calflag - 4),56+ 12 * 1 + 20 * 1,30,30,RGB(220,220,220));/* ѡ�а�ť */	
			if(calflag >= 8  && calflag <= 11)
				GUIButton(btndata[2][calflag - 8],42 + 12 * (calflag - 8) + 20 * (calflag - 8),56+ 12 * 2 + 20 * 2,30,30,RGB(220,220,220));/* ѡ�а�ť */	
			if(calflag >= 12 && calflag <= 15)
				GUIButton(btndata[3][calflag - 12],42 + 12 * (calflag - 12) + 20 * (calflag - 12),56+ 12 * 3 + 20 * 3,30,30,RGB(220,220,220));/* ѡ�а�ť */
			calflag++;
			if(calflag < 4)											 
				GUIButton(btndata[0][calflag],42 + 12 * calflag + 20 * calflag,56+ 12 * 0 + 20 * 0,30,30,RGB(110,110,110));/* ѡ�а�ť */	
			if(calflag >= 4  && calflag <= 7)
				GUIButton(btndata[1][calflag - 4],42 + 12 * (calflag - 4) + 20 * (calflag - 4),56 + 12 * 1 + 20 * 1,30,30,RGB(110,110,110));/* ѡ�а�ť */	
			if(calflag >= 8  && calflag <= 11)
				GUIButton(btndata[2][calflag - 8],42 + 12 * (calflag - 8) + 20 * (calflag - 8),56 + 12 * 2 + 20 * 2,30,30,RGB(110,110,110));/* ѡ�а�ť */	
			if(calflag >= 12 && calflag <= 15)
				GUIButton(btndata[3][calflag - 12],42 + 12 * (calflag - 12) + 20 * (calflag - 12),56 + 12 * 3 + 20 * 3,30,30,RGB(110,110,110));/* ѡ�а�ť */		
			OSTimeDly(10);  /* ��ʱ */
		}
		/* ��һ������ */
		if(!KEY_PRE && calflag > 0)
		{
			if(calflag < 4)
				GUIButton(btndata[0][calflag],42 + 12 * calflag + 20 * calflag,56+ 12 * 0 + 20 * 0,30,30,RGB(220,220,220));/* ѡ�а�ť */	
			if(calflag >= 4  && calflag <= 7)
				GUIButton(btndata[1][calflag - 4],42 + 12 * (calflag - 4) + 20 * (calflag - 4),56+ 12 * 1 + 20 * 1,30,30,RGB(220,220,220));/* ѡ�а�ť */	
			if(calflag >= 8  && calflag <= 11)
				GUIButton(btndata[2][calflag - 8],42 + 12 * (calflag - 8) + 20 * (calflag - 8),56+ 12 * 2 + 20 * 2,30,30,RGB(220,220,220));/* ѡ�а�ť */	
			if(calflag >= 12 && calflag <= 15)
				GUIButton(btndata[3][calflag - 12],42 + 12 * (calflag - 12) + 20 * (calflag - 12),56+ 12 * 3 + 20 * 3,30,30,RGB(220,220,220));/* ѡ�а�ť */
			calflag--;
			if(calflag < 4)
				GUIButton(btndata[0][calflag],42 + 12 * calflag + 20 * calflag,56+ 12 * 0 + 20 * 0,30,30,RGB(110,110,110));/* ѡ�а�ť */	
			if(calflag >= 4  && calflag <= 7)
				GUIButton(btndata[1][calflag - 4],42 + 12 * (calflag - 4) + 20 * (calflag - 4),56+ 12 * 1 + 20 * 1,30,30,RGB(110,110,110));/* ѡ�а�ť */	
			if(calflag >= 8  && calflag <= 11)
				GUIButton(btndata[2][calflag - 8],42 + 12 * (calflag - 8) + 20 * (calflag - 8),56+ 12 * 2 + 20 * 2,30,30,RGB(110,110,110));/* ѡ�а�ť */	
			if(calflag >= 12 && calflag <= 15)
				GUIButton(btndata[3][calflag - 12],42 + 12 * (calflag - 12) + 20 * (calflag - 12),56+ 12 * 3 + 20 * 3,30,30,RGB(110,110,110));/* ѡ�а�ť */		
			OSTimeDly(10);  /* ��ʱ */
		}
		/* ȷ��ѡ�� */
		if(!KEY_ENTER)
		{
			/* ��� */
			if( calflag == 13)
			{
				LCD_FilledRectangle(180,56,170,127,RGB(230,230,230));	
				LCD_FilledRectangle(182,58,166,123,White);	/* ��ʾ��� */
				LCD_FilledRectangle(186,148,160,1,RGB(230,230,230));
				/* ������ʾ */
				Lcd_WriteNumlen(1,0,185,100,Black,White,1);	/* ��������1 */
				LCD_Write_String(185,149,"=",Black,White,0);
				Lcd_WriteNumlen(1,0,185,165,Black,White,1);	/* ��ʾ��� */
				/* ������� */
//				selflag=0,calflag=0,datalen=0,i,j,caltype = 0;		
//				iuputdata = 0,iuputdata1 = 0,iuputdata2 = 0,calres = 0,temp = 0;
				Calculator();
			}
			if(datalen <= 9)	/* ������� 0 - 9 */
			{	
				if(calflag == 3 || calflag == 7 || calflag == 11 || calflag == 15)
				{
					switch(calflag)
					{
						case 3:
							caltype = 1;   /* "/" */
							LCD_Write_String(185,116,btndata[0][3],Black,White,1);
							break;
						case 7:
							caltype = 2;   /* "*" */
							LCD_Write_String(185,116,btndata[1][3],Black,White,1);
							break;
						case 11:
							caltype = 3;  /* "-" */
							LCD_Write_String(185,116,btndata[2][3],Black,White,1);
							break;
						case 15:
							caltype = 4;  /* "+" */
							LCD_Write_String(185,116,btndata[3][3],Black,White,1);
							break;				
					}
					datalen   = 0;	/* �������� */
					iuputdata = 0;
			
				}
							 /* ����������� */
				if(calflag != 3 && calflag != 7 && calflag != 11 && calflag != 13 && calflag != 14 && calflag != 15)
				{
					
					if(!(datalen == 0 && calflag == 12))  /* ��һλ��Ϊ0 */
					{
						/* �������� */
						if(datalen == 0)
						{
							if(calflag < 4)	   /* ���� 1 2 3 */
								iuputdata = (calflag + 1);
							if(calflag >= 4  && calflag <= 6)  /* ���� 4 5 6 */
								iuputdata = (calflag);
							if(calflag >= 8  && calflag <= 10)	/* ���� 7 8 9 */
								iuputdata = (calflag - 1);			
						}
						else
						{	
							
							if(calflag == 12)	  /* ���� 0 */
								iuputdata = iuputdata * 10;	
							if(calflag < 4)		  /* ���� 1 2 3 */
								iuputdata = iuputdata * 10 + (calflag + 1); 
							if(calflag >= 4  && calflag <= 6)
							 	iuputdata = iuputdata * 10 + (calflag);	   /* ���� 4 5 6 */
							if(calflag >= 8  && calflag <= 10)
								iuputdata = iuputdata * 10 + (calflag - 1);	/* ���� 7 8 9 */
						}
						datalen++;	
						if(caltype == 0)
						{
							/* ������ʾ */
							if(calflag < 4)
								LCD_Write_String(177 + datalen * 8,100,btndata[0][calflag],Black,White,1);
							if(calflag >= 4  && calflag <= 7)
								LCD_Write_String(177 + datalen * 8,100,btndata[1][calflag - 4],Black,White,1);
							if(calflag >= 8  && calflag <= 11)
								LCD_Write_String(177 + datalen * 8,100,btndata[2][calflag - 8],Black,White,1);
							if(calflag >= 12 && calflag <= 15)
								LCD_Write_String(177 + datalen * 8,100,btndata[3][calflag - 12],Black,White,1);	
							iuputdata1 = iuputdata;
						}
						else
						{
							/* ������ʾ */
							if(calflag < 4)
								LCD_Write_String(177 + datalen * 8,132,btndata[0][calflag],Black,White,1);
							if(calflag >= 4  && calflag <= 7)
								LCD_Write_String(177 + datalen * 8,132,btndata[1][calflag - 4],Black,White,1);
							if(calflag >= 8  && calflag <= 11)
								LCD_Write_String(177 + datalen * 8,132,btndata[2][calflag - 8],Black,White,1);
							if(calflag >= 12 && calflag <= 15)
								LCD_Write_String(177 + datalen * 8,132,btndata[3][calflag - 12],Black,White,1);	
							iuputdata2 = iuputdata;	
						}
					//	Lcd_WriteNumlen(datalen,iuputdata,185,165,Black,White,1);
					}
				 }
				 /* �� ��=�������� */
				 if(calflag == 14)
				 {
				 		switch(caltype)
						{
							case 1:
								calres = iuputdata1 / iuputdata2;
								break;
							case 2:
								calres = iuputdata1 * iuputdata2;
								break;
							case 3:
								calres = iuputdata1 - iuputdata2;
								break;
							case 4:
								calres = iuputdata1 + iuputdata2;
								break;			
						}
						datalen = 0;
						temp = calres;
						while(temp != 0)	 /* �������ݳ��� */
						{
							temp = temp / 10;
							datalen++;
						}
						if(datalen <= 9)
							Lcd_WriteNumlen(datalen,calres,185,165,Black,White,1);	/* ��ʾ��� */
						else
							LCD_Write_String(185,165,"ERROR        ",Black,White,1);
						iuputdata1 =  calres;
						datalen = 0;
				 }
				OSTimeDly(15);  /* ��ʱ */
			 }
		}
	
			
	}
					
}											  	