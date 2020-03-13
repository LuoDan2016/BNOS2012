/******************** (C) COPYRIGHT 2012 BOOLESION.NET ***************************
* ��Ʒ����: BNOS 2012
* �ļ�����: devicesinit.c
* ��������: BOOLESION.NET ������(BOOLESION)���ӿƼ� - NETC (�½���)
* ����汾: V1.2
* ��������: 2012/03/20
* ��������: BNOS �豸��ʼ��.
**********************************************************************************/

/* Includes ------------------------------------------------------------------*/
#include "includes.h"

/* �������� ------------------------------------------------------------------*/
/* �ļ�ϵͳ���ȫ�ֱ������� */
extern FRESULT res;
extern FATFS fs;
extern volatile BYTE buff[256];
extern volatile INT16U br;  
/* SD�������� ��ʼ����ʶ */	
INT8U sdcheck = 0;
/*  �����ֿ����ʶ 1Ϊ��ȷ ���������� */
INT8U CHNCHEK = 0;
/* 
**ϵͳ�ļ�·��(����GB2312�ֿ⡢GUI�����ļ�) 
**GB2312 ��ַ 0- 261695 �ֽ�
**SLOGO ͼ���ļ� 100 x 66 24bit ����ͷ�ļ� ��ʼ 261696 -  281496 �ֽ�
*/
INT8U *SYSDATA = "System/system.bin";
/* ������LOGO·�� */

void DeviceInit(void)
{
	/* ʱ�ӳ�ʼ�� */
	Init_Timer0();
	/* ����P4��Ϊ��ͨI/Oģʽ */
	P4SW=0XFF;
	/* SPI�˿ڳ�ʼ�� */
    SPI_Init();
	/* ���ڳ�ʼ�� */
	UartInit();    
	OSMSG_STAR;/* ���ڴ�ӡ BNOS������Ϣ */
	/* LCD��ʼ�� */
	LCD_Init();
	COMNLANG_BNOSINF;  /* LCD��ʾ������Ϣ */
	OSMSG_LCDINIT;
	/* �������� */	
	GUIProgressBar(0,LCD_YSIZE_TFT - 6,400,6,0);
	/* �������� */	
	GUIProgressBar(0,LCD_YSIZE_TFT - 6,400,6,5);
	/* SPI FLASH ��ʼ�� */
	OSMSG_FLASHINIT;
	COMNLANG_FLASHINIT;
	M25P16_Init();	
	/* �������� */	
	GUIProgressBar(0,LCD_YSIZE_TFT - 6,400,6,15);
	/* SD TF����ʼ��/FatFs�ļ�ϵͳ���� */
	OSMSG_SDINIT;
	COMNLANG_SDCARDINIT;
	disk_initialize();		/* SD TF����ʼ�� */	                 	
	res = pf_mount(&fs);                  /* FatFs�ļ�ϵͳ���� */
	if(res == 0)
	{
		OSMSG_MOUNTOK;
		COMNLANG_SDOK;
		sdcheck = 0;
	}	
	while(res)
	{
		sdcheck++;
		if(sdcheck >= SDCHECK)            /* SD�������� */
		{
			OSMSG_SDERROR;				  /* ��ʼ��ʧ�� */
			COMNLANG_SDERROR;
			break;
		}
		if(disk_initialize() == FR_OK);  /* SD TF�����³�ʼ�� */
		{
			res = pf_mount(&fs);         /* FatFs�ļ�ϵͳ���¹��� */
			if(res == FR_OK)			 /* ��ʼ���ɹ� */
			{
				OSMSG_MOUNTOK;
				COMNLANG_SDOK;
				sdcheck = 0;
			}		
		}		
	}
		/* �������� */	
	GUIProgressBar(0,LCD_YSIZE_TFT - 6,400,6,25);
	/* VS1003��Ƶ�����ʼ��*/
	OSMSG_VSINIT;
	COMNLANG_VSINIT;
	/* ���SPI���� */
	SPI_Init();
	VS_Init();
	VS_SinTest(1000);                   /* ���Ҳ��� ���� ��ཡ� һ����˵��VS1003��ʼ���ɹ� */
	FCLK_FAST(); /* SPI����Ϊ����ģʽ */
	/* �������� */	
	GUIProgressBar(0,LCD_YSIZE_TFT - 6,400,6,35);
}

void FontGUILoad(void)
{
	INT32U i = 0,j = 0,count=0;
	/* GB2312���������0 - 282752 �ֽ� �ж�GB2312 52 - 57�ֽ��Ƿ�Ϊ:0x20, 0x00, 0x18, 0x00, 
	0x0C ����˵���ֿ�����*/
//	M25P16_Bulk_Erase();  /* ǿ�Ʋ���������ϵͳ�ļ� */	 	
	M25P16_Fast_Read_Data(52,5,buff);
		/* �������� */	
	GUIProgressBar(0,LCD_YSIZE_TFT - 6,400,6,45);
	if(buff[0] == 0x20 && buff[2] == 0x18 && buff[4] == 0x0C)
	{
		OSMSG_GBFONTOK;
		COMNLANG_FONTOK;
		COMNLANG_BGKTEST;
		CHNCHEK = 1;  	/*  �����ֿ����ʶ 1Ϊ��ȷ ���������� */
				/* �������� */	
		GUIProgressBar(0,LCD_YSIZE_TFT - 6,400,6,60);
	
	}
	else
	{
	 	OSMSG_GBFONTERROR;
	 	COMNLANG_FONTERROR;
	 	CHNCHEK = 0;
		/* �������� */	
		GUIProgressBar(0,LCD_YSIZE_TFT - 6,400,6,50);
		M25P16_Bulk_Erase();  /* ���� Flash */	
#if 1 
       /* ϵͳ�ļ�д�� */
		COMNLANG_BGKLOAD; 
		OSMSG_GBFONTLOAD;
		res = pf_open(SYSDATA);
		if(res == 0)
		{
			OSMSG_OPENFONTOK;
			/* д����Ϣ */
			OSMSG_WRITEFONTINF;
			COMNLANG_BGKWRITEINF;
			/* �������� */	
			GUIProgressBar(0,LCD_YSIZE_TFT - 6,400,6,55);
			for(i=0;;i++)
			{
				res = pf_read(buff,256,&br);
				if(res || br==0)
					break; 						     
				M25P16_Page_Program(i*256,256,buff);   /* ������д��FLASH */	
			}	
		}
		else
		{
			OSMSG_OPENFONTERROR;
			OSMSG_OPENFONTERRORTIP;
			COMNLANG_BGKLOADERROR;
		}
#endif /* WRITTEN GB2312 TO SPI FLASH */

		/* GB2312���������0 - 282752 �ֽ� �ж�GB2312 52 - 57�ֽ��Ƿ�Ϊ:0x20, 0x00, 0x18, 0x00, 
		0x0C ����˵���ֿ�����*/ 	
		M25P16_Fast_Read_Data(52,5,buff);
		if(buff[0] == 0x20 && buff[2] == 0x18 && buff[4] == 0x0C)
		{
			OSMSG_GBFONTOK;
			COMNLANG_FONTOK;
			COMNLANG_BGKTEST;
			CHNCHEK = 1;  	/*  �����ֿ����ʶ 1Ϊ��ȷ ���������� */
					/* �������� */	
			GUIProgressBar(0,LCD_YSIZE_TFT - 6,400,6,60);
		
		}
	}			

	
} 