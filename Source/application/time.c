/******************** (C) COPYRIGHT 2012 BOOLESION.NET ***************************
* ��Ʒ����: ������51������ E1101
* �ļ�����: time.c
* ��������: BOOLESION.NET ������(BOOLESION)���ӿƼ� - NETC (�½���)
* ����汾: V1.2
* ��������: 2012/01/20
* ��������: ʱ�估�����������.
**********************************************************************************/

/* Includes ---------------------------------------------------------------------*/
#include "includes.h"

/* �������� ---------------------------------------------------------------------*/
extern volatile INT8U menuflag; /* �˵���ʶΪ */
extern volatile INT8U mainmenuflag; /*���˵���ʶ   */
SYS_TIME datetime;	 /* ϵͳʱ�� */

/* �����ַ��� */
INT8U code *WEEKS[7] = 
{
	"Sunday",
	"Monday",
	"Tuesday",
	"Wednesday",
	"Thursday",
	"Friday",
	"Saturday"
};

/* ���������ڱ� */
code INT8U WeekTab[] = {
  (3 << 5) + 31,	//1�� 
  (6 << 5) + 29,	//2�� 
  (0 << 5) + 31,	//3�� 
  (3 << 5) + 30,	//4�� 
  (5 << 5) + 31,	//5�� 
  (1 << 5) + 30,	//6�� 
  (3 << 5) + 31,	//7�� 
  (6 << 5) + 31,	//8�� 
  (1 << 5) + 30,	//9�� 
  (4 << 5) + 31,	//10�� 
  (0 << 5) + 30,	//11�� 
  (2 << 5) + 31 	//12�� 
};  

/*********************************************************************************
** ��������: INT8U WeekDay(INT8U c,INT8U y,INT8U m,INT8U d).
** ��������: 0000��~9999�������㷨.
** �������: INT8U c,INT8U y,INT8U char m,INT8U d.         
** �������: None.
** ���ز���: (week << 5) | day �������ں�������.
**********************************************************************************/
INT8U WeekDay(INT8U c,INT8U y,INT8U m,INT8U d) 
{ 
  unsigned char week, day; 
  c &= 0x03;                           /* ����%4 */
  c = c | (c << 2);                    /* ����%4*5 */
  day = WeekTab[m - 1];                /* �±� */
  week = day >> 5;                     /*�������� */
  day &= 0x1f;                         /*������ */
  if ((m < 3) && !((c == 0) | (y & ((y & 0x03) == 0)))){/*ƽ�� */
    if (m == 2) day--;                 /*ƽ�������� */
    week++;                            /*ƽ���±�+1 */
  } 
  y = y + (y >> 2);                    /*��+��/4 */
  week = (week + c + y + d + 2) % 7;   /*(����=����%4*5+��+��/4+�±�+��+2)%7  */
  return (week << 5) | day;            /*�������ں������� */
} 

/*********************************************************************************
** ��������: INT8U GetWeekMaxDay(INT16U year,INT8U m,INT8U d).
** ��������: ������������.
** �������: INT16U year,INT8U m,INT8U d.         
** �������: None.
** ���ز���: WDay Week = WDay >> 5 �õ�����,Day  = WDay & 0x1f�õ����������.
**********************************************************************************/
INT8U GetWeekMaxDay(INT16U year,INT8U m,INT8U d) 
{ 
	unsigned char c, y; 	           /* ������� */
	unsigned char cx, yx, mx, dx;   
	unsigned char WDay; 

	c    = year >> 8;
	y    = year & 0xff;
	cx   = BcdToBin(c);                /* ���� */ 
	yx   = BcdToBin(y);                /* �� */ 
	mx   = BcdToBin(m);                /* �� */ 
	dx   = BcdToBin(d);                /* �� */ 
	WDay = WeekDay(cx, yx, mx, dx);    /* ȡ���ں������� */ 
	return WDay;       /* Week = WDay >> 5 �õ�����,Day  = WDay & 0x1f�õ���������� */
} 

/*********************************************************************************
** ��������: void CalendarApp(void).
** ��������: �������������.
** �������: None.         
** �������: None.
** ���ز���: None.
**********************************************************************************/
void CalendarApp(void)
{
	INT8U weekmaxday,week,maxday;  /* ���ں���������� */
	INT8U disday = 1,disrow = 0,disres = 0;  /* ��ʾ�� */
	INT16U calyear = datetime.year; /* ���������� �� */
	INT8U calmon = datetime.mon;   /* ���������� �� */
	weekmaxday = GetWeekMaxDay(calyear,calmon,0x01);  /* ��õ���1�յ������� */
	week       = weekmaxday >>5;	 /* ������� */
    maxday     = weekmaxday	& 0x1f;   /* ������������ */
	while(1)
	{
		/* ���� KEY_DOWN_EXIT �˳����������˵� */
		if(!KEY_DOWN_EXIT)
		{
		 	menuflag     = 0;
		    mainmenuflag = 0;
			break;			
		}
		if(disres  == 0)
		{
			GUIDown(320,50,Black);	/* ��һ�� �ָ���ɫ */
			GUIUp(180,50,Black);    /* ��һ��  �ָ���ɫ */
			/* ��������ʾ */
			for(disrow=0;disrow < 6;disrow++)	/* ��ʾ���� ��6�� */
			{
				for(week;week < 7;week++)		 /* ��ʾ����  */
				{
		
				    if(calyear ==datetime.year && calmon == datetime.mon && disday == datetime.day) /* ������ʾ��ɫ */
						Lcd_WriteNumlen(2,disday,145 + (32 * week),104 + (disrow * 14),Red,White,1);
					else		
						Lcd_WriteNumlen(2,disday,145 + (32 * week),104 + (disrow * 14),Blue,White,1);
					if(disday < maxday)
						disday++;
					else
						break;
				}
				if(disday == maxday)
					break;
				else
					week = 0;
			}
			disres = 1;						
		}
		/* ��һ�� */
		if(!KEY_NEXT)
		{
			GUIDown(320,50,Green);	/* ��һ�� ���ɫ */
		 	disday = 1,disrow = 0;  /* ��ʾ���� */
			disres = 0;		        /* ������ʾ */
		  	if(calmon < 12)
		  		calmon++;           /* �µ��� */
			else
			{
				calyear++;
				calmon = 1;
		    }
			weekmaxday = GetWeekMaxDay(calyear,calmon,0x01);  /* ��õ���1�յ������� */
			week       = weekmaxday >>5;	 /* ������� */
			maxday     = weekmaxday	& 0x1f;   /* ������������ */	
			/* ������ʾ */
			Lcd_WriteNumlen(4,BcdToBin(calyear >> 8)*0x64 +  BcdToBin(calyear & 0xff),40+178,54,Blue,White,1);	  /* �� */
			LCD_Write_String(73+178,54,"/",Blue,White,0);
			Lcd_WriteNumlen(2,BcdToBin(calmon),82+178,54,Blue,White,1);	          /* �� */	
			LCD_FilledRectangle(144,104,210,88,White);                            /* ������ʾ���� */	 
		}
		/* ��һ�� */
		if(!KEY_PRE)
		{
			GUIUp(180,50,Green);    /* ��һ�� ���ɫ */
		 	disday = 1,disrow = 0;  /* ��ʾ���� */
			disres = 0;		        /* ������ʾ */
		  	if(calmon > 1)
		  		calmon--;           /* �µ��� */
			else
			{
				calyear--;
				calmon = 12;
		    }
			weekmaxday = GetWeekMaxDay(calyear,calmon,0x01);  /* ��õ���1�յ������� */
			week       = weekmaxday >>5;	 /* ������� */
			maxday     = weekmaxday	& 0x1f;   /* ������������ */	
			/* ������ʾ */
			Lcd_WriteNumlen(4,BcdToBin(calyear >> 8)*0x64 +  BcdToBin(calyear & 0xff),40+178,54,Blue,White,1);	  /* �� */
			LCD_Write_String(73+178,54,"/",Blue,White,0);
			Lcd_WriteNumlen(2,BcdToBin(calmon),82+178,54,Blue,White,1);	          /* �� */	
			LCD_FilledRectangle(144,104,210,88,White);        /* ������ʾ���� */	 
		}
	
	}						
}
