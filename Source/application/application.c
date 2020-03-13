/******************** (C) COPYRIGHT 2012 BOOLESION.NET ***************************
* ��Ʒ����: ������51������ E1101
* �ļ�����: application.c
* ��������: BOOLESION.NET ������(BOOLESION)���ӿƼ� - NETC (�½���)
* ����汾: V1.2
* ��������: 2012/01/20
* ��������: BNOS �����壬�������������� RAM > 300 Byte �ں�CPU.
**********************************************************************************/

/* Includes ---------------------------------------------------------------------*/
#include "includes.h"

extern OS_STK SDCheckTaskStkd[MaxStkSize + 1]; 

/* �������� ---------------------------------------------------------------------*/
                                     /* �ļ�ϵͳ���ȫ�ֱ������� */
volatile FRESULT res;
volatile FATFS fs;	
volatile INT16U br,i,j;
volatile BYTE buff[256];             /* ����ռ� BMP���� ��Ƶ���� */
volatile INT16U LcdBLTime = 0;       /* LCD����ʱ�� */
extern volatile INT16U LcdBLsettime; /* LCD ����Ƚ�ֵ */
extern volatile INT16U menuflag;     /* �˵���ʶΪ */
extern volatile INT8U mainmenuflag;  /* ���˵���ʶ   */
extern SYS_TIME datetime;	         /* ϵͳʱ�� */
extern INT8U sdcheck;                /* SD�������� */

/* ������ ---------------------------------------------------------------------*/
/*********************************************************************************
** ��������: void OSMainTask(void *pdat).
** ��������: ����ϵͳ��ʼ������.
** �������: void *pdat.         
** �������: None
** ���ز���: None
**********************************************************************************/
void OSMainTask(void *pdat)
{
	ET0 = 1;		                 /* �ڵ�һ������(������ȼ�)��ʼִ��ʱ�ſ�ʱ���ж� */
	pdat = pdat;                        
	OSTimeDlyHMSM(0,0,0,100);
	GUI_MainMenu();                   /* ������GUI */
	OSTaskResume(MENUAPP); 
	/* ���ڳ�ʼ�� */
	if(datetime.year == 0)
	{
		datetime.year = 0x2012;		 /* ���ڳ�ʼ�� */
		datetime.mon  = 0x01;
		datetime.day  = 0x01;
	}
	/* �������� */
	OS_ENTER_CRITICAL();  
	OSTaskCreate(SDCheckTask,(void*)0,&SDCheckTaskStkd[0],SDCHECKTASK);
	OS_EXIT_CRITICAL();                      
  	/* ����ѭ�� */
	for(; ; )
	{
		/* һ�г���ʵ��STC���ϵ��Զ�����(���ͷ�ļ�δ����IAP_CONTR�Ĵ���,��while�����м���if(P3==(P3&0xFE))IAP_CONTR=0x60;
		** �趨����#include<reg52.h>�м���sfr IAP_CONTR = 0xC7; )ԭ��BOOLESION.NET  -NETC */
		if(P3==(P3&0xFE))IAP_CONTR=0x60;
		OSTimeDlyHMSM(0,0,0,20);	/*delay 0h 0i 50ms */	
		/* ���¼���SD/TF�� */
		if( sdcheck != 0 )
		{
			OSTaskResume(SDCHECKTASK);	
		}
	}
}

/*********************************************************************************
** ��������: void MenuApp(void *pdat).
** ��������: ��꼰��̬�˵���ʾ����.
** �������: void *pdat.         
** �������: None
** ���ز���: None
**********************************************************************************/
void MenuApp(void *pdat)
{
	pdat = pdat;
	OSTaskSuspend(MENUAPP);
    /* ����ʼ��,�趨��ʼ���� */
	MouseInit(10,40);
	for(; ;)
	{ 		   
	    /* ������ */
	   MouseScan();
		/* ����̬�˵� ��Ӧ�ó��� */
	   MovMenu();		
	   OSTimeDlyHMSM(0,0,0,10);
	}
}

/*********************************************************************************
** ��������: void OSTimeTask(void *pdat).
** ��������: ϵͳʱ�䴦������.
** �������: void *pdat.         
** �������: None
** ���ز���: None
**********************************************************************************/
void OSTimeTask(void *pdat)
{   
	volatile  INT32U  OSTimebk;
	OSTime = OSTimebk;	          /* ��ȡϵͳ����ʱ�� */
	pdat = pdat;
	OSTaskSuspend(OSTIMETASK);
	for(; ; )
	{	
		if(	OSTime - OSTimebk > 60)
		{
			if(datetime.sec <= 60)
			{
				datetime.sec++;	   /* ϵͳʱ��s */
				if(LcdBLTime <= LcdBLsettime)  /* LCD����ʱ����� */
					LcdBLTime++;
			}
			else
			{
				datetime.sec = 0;
			}				
		    OSTime = OSTimebk;
		}	
		if(LcdBLTime > LcdBLsettime) /* LCD����ʱ�������ֵ�Ƚ� */
		{
			LCD_Backlight = 0;		 /* �ر�LCD���� */
		}
		if(!KEY_ENTER || !KEY_NEXT || !KEY_PRE || !KEY_UP_VOL || !KEY_DOWN_EXIT) /* �а�����������LCD����ʱ��Ϊ0 */
		{
			LcdBLTime = 0;
				LCD_Backlight = 1;	   /* ����LCD���� */
		}			 
		OSTimeDlyHMSM(0,0,0,50);
	}
}

/*********************************************************************************
** ��������: void SDCheckTask(void *pdat).
** ��������: SD/TF���ؼ������.
** �������: void *pdat.         
** �������: None
** ���ز���: None
**********************************************************************************/
void SDCheckTask(void *pdat)
{	

	pdat = pdat;
	OSTaskSuspend(SDCHECKTASK); 
	disk_initialize();	                    /* SD TF����ʼ�� */			
	res = pf_mount(&fs);                    /* FatFs�ļ�ϵͳ���� */             
	for(; ;)
	{ 
		while(res)
		{
			if(disk_initialize() == FR_OK);  /* SD TF�����³�ʼ�� */
			{
				res = pf_mount(&fs);         /* FatFs�ļ�ϵͳ���¹��� */
				if(res == FR_OK)
				{
					OSMSG("SD/TF And FATFS Initialize OK. \r\n");
					sdcheck = 0;
					OSTaskSuspend(SDCHECKTASK); 
				}		
			}	
		 }

	}		
}
