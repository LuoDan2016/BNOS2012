/******************** (C) COPYRIGHT 2012 BOOLESION.NET ***************************
* 产品名称: BNOS 2012
* 文件名称: devicesinit.c
* 程序作者: BOOLESION.NET 布尔创(BOOLESION)电子科技 - NETC (陈建长)
* 程序版本: V1.2
* 编制日期: 2012/03/20
* 功能描述: BNOS 设备初始化.
**********************************************************************************/

/* Includes ------------------------------------------------------------------*/
#include "includes.h"

/* 变量声明 ------------------------------------------------------------------*/
/* 文件系统相关全局变量声明 */
extern FRESULT res;
extern FATFS fs;
extern volatile BYTE buff[256];
extern volatile INT16U br;  
/* SD卡检测计数 初始化标识 */	
INT8U sdcheck = 0;
/*  汉字字库检查标识 1为正确 其他不存在 */
INT8U CHNCHEK = 0;
/* 
**系统文件路径(包含GB2312字库、GUI界面文件) 
**GB2312 地址 0- 261695 字节
**SLOGO 图像文件 100 x 66 24bit 不含头文件 开始 261696 -  281496 字节
*/
INT8U *SYSDATA = "System/system.bin";
/* 布尔创LOGO路径 */

void DeviceInit(void)
{
	/* 时钟初始化 */
	Init_Timer0();
	/* 设置P4口为普通I/O模式 */
	P4SW=0XFF;
	/* SPI端口初始化 */
    SPI_Init();
	/* 串口初始化 */
	UartInit();    
	OSMSG_STAR;/* 串口打印 BNOS启动信息 */
	/* LCD初始化 */
	LCD_Init();
	COMNLANG_BNOSINF;  /* LCD显示语言信息 */
	OSMSG_LCDINIT;
	/* 启动进度 */	
	GUIProgressBar(0,LCD_YSIZE_TFT - 6,400,6,0);
	/* 启动进度 */	
	GUIProgressBar(0,LCD_YSIZE_TFT - 6,400,6,5);
	/* SPI FLASH 初始化 */
	OSMSG_FLASHINIT;
	COMNLANG_FLASHINIT;
	M25P16_Init();	
	/* 启动进度 */	
	GUIProgressBar(0,LCD_YSIZE_TFT - 6,400,6,15);
	/* SD TF卡初始化/FatFs文件系统挂载 */
	OSMSG_SDINIT;
	COMNLANG_SDCARDINIT;
	disk_initialize();		/* SD TF卡初始化 */	                 	
	res = pf_mount(&fs);                  /* FatFs文件系统挂载 */
	if(res == 0)
	{
		OSMSG_MOUNTOK;
		COMNLANG_SDOK;
		sdcheck = 0;
	}	
	while(res)
	{
		sdcheck++;
		if(sdcheck >= SDCHECK)            /* SD卡检测次数 */
		{
			OSMSG_SDERROR;				  /* 初始化失败 */
			COMNLANG_SDERROR;
			break;
		}
		if(disk_initialize() == FR_OK);  /* SD TF卡重新初始化 */
		{
			res = pf_mount(&fs);         /* FatFs文件系统重新挂载 */
			if(res == FR_OK)			 /* 初始化成功 */
			{
				OSMSG_MOUNTOK;
				COMNLANG_SDOK;
				sdcheck = 0;
			}		
		}		
	}
		/* 启动进度 */	
	GUIProgressBar(0,LCD_YSIZE_TFT - 6,400,6,25);
	/* VS1003音频解码初始化*/
	OSMSG_VSINIT;
	COMNLANG_VSINIT;
	/* 清除SPI数据 */
	SPI_Init();
	VS_Init();
	VS_SinTest(1000);                   /* 正弦测试 听到 “嘟” 一声则说明VS1003初始化成功 */
	FCLK_FAST(); /* SPI设置为高速模式 */
	/* 启动进度 */	
	GUIProgressBar(0,LCD_YSIZE_TFT - 6,400,6,35);
}

void FontGUILoad(void)
{
	INT32U i = 0,j = 0,count=0;
	/* GB2312编码表存放于0 - 282752 字节 判断GB2312 52 - 57字节是否为:0x20, 0x00, 0x18, 0x00, 
	0x0C 是则说明字库表存在*/
//	M25P16_Bulk_Erase();  /* 强制擦除并下载系统文件 */	 	
	M25P16_Fast_Read_Data(52,5,buff);
		/* 启动进度 */	
	GUIProgressBar(0,LCD_YSIZE_TFT - 6,400,6,45);
	if(buff[0] == 0x20 && buff[2] == 0x18 && buff[4] == 0x0C)
	{
		OSMSG_GBFONTOK;
		COMNLANG_FONTOK;
		COMNLANG_BGKTEST;
		CHNCHEK = 1;  	/*  汉字字库检查标识 1为正确 其他不存在 */
				/* 启动进度 */	
		GUIProgressBar(0,LCD_YSIZE_TFT - 6,400,6,60);
	
	}
	else
	{
	 	OSMSG_GBFONTERROR;
	 	COMNLANG_FONTERROR;
	 	CHNCHEK = 0;
		/* 启动进度 */	
		GUIProgressBar(0,LCD_YSIZE_TFT - 6,400,6,50);
		M25P16_Bulk_Erase();  /* 擦除 Flash */	
#if 1 
       /* 系统文件写入 */
		COMNLANG_BGKLOAD; 
		OSMSG_GBFONTLOAD;
		res = pf_open(SYSDATA);
		if(res == 0)
		{
			OSMSG_OPENFONTOK;
			/* 写入信息 */
			OSMSG_WRITEFONTINF;
			COMNLANG_BGKWRITEINF;
			/* 启动进度 */	
			GUIProgressBar(0,LCD_YSIZE_TFT - 6,400,6,55);
			for(i=0;;i++)
			{
				res = pf_read(buff,256,&br);
				if(res || br==0)
					break; 						     
				M25P16_Page_Program(i*256,256,buff);   /* 将内容写到FLASH */	
			}	
		}
		else
		{
			OSMSG_OPENFONTERROR;
			OSMSG_OPENFONTERRORTIP;
			COMNLANG_BGKLOADERROR;
		}
#endif /* WRITTEN GB2312 TO SPI FLASH */

		/* GB2312编码表存放于0 - 282752 字节 判断GB2312 52 - 57字节是否为:0x20, 0x00, 0x18, 0x00, 
		0x0C 是则说明字库表存在*/ 	
		M25P16_Fast_Read_Data(52,5,buff);
		if(buff[0] == 0x20 && buff[2] == 0x18 && buff[4] == 0x0C)
		{
			OSMSG_GBFONTOK;
			COMNLANG_FONTOK;
			COMNLANG_BGKTEST;
			CHNCHEK = 1;  	/*  汉字字库检查标识 1为正确 其他不存在 */
					/* 启动进度 */	
			GUIProgressBar(0,LCD_YSIZE_TFT - 6,400,6,60);
		
		}
	}			

	
} 