/******************** (C) COPYRIGHT 2012 BOOLESION.NET ***************************
* 产品名称: BNOS 2012
* 文件名称: osmsg.h
* 程序作者: BOOLESION.NET 布尔创(BOOLESION)电子科技 - NETC (陈建长)
* 程序版本: V1.2
* 编制日期: 2012/03/20
* 功能描述: BNOS 系统打印信息.
**********************************************************************************/
#ifndef __OSMSG_H__
#define __OSMSG_H__

/* 串口函数转换 */
#define OSMSG TransmitString
/* BNOS启动信息 */
#define	OSMSG_STAR 	;\
    OSMSG("\r\nBNOS 2012 Start ... \r\n");\
	OSMSG("******************** (C) COPYRIGHT 2012 BOOLESION.NET ************************\r\n");\
	OSMSG("** Product Name  : BNOS 2012(BNOS For 8051)\r\n");\
	OSMSG("** Program Author: BOOLESION - BOOLESION.NET -陈建长 NETC	\r\n");\
	OSMSG("** Version       : V1.2	   \r\n");\
	OSMSG("** Date          : 2012/03/20	\r\n");\
	OSMSG("------------------------------------------------------------------------------\r\n");\
	OSMSG("******************************************************************************\r\n");\
/* LCD TFT初始化 */
#define OSMSG_LCDINIT OSMSG("\r\nLCD Initialize OK...LCD ID:OTM4001.")
/* SPI Flash 初始化 */
#define	OSMSG_FLASHINIT OSMSG("\r\nSPI Flash Initialize.")
/* SD/TF卡初始化 */
#define	OSMSG_SDINIT OSMSG("\r\nSD/TF Card Initialize...")

#define OSMSG_SDERROR OSMSG("\r\TF/SD Crad Initialize ERROR!\r\n")
#define OSMSG_MOUNTOK OSMSG("\r\nFatFs MOUNT OK!\r\n")
/* VS1003初始化信息 */
#define OSMSG_VSINIT OSMSG("VS1003 Initialize...\r\n")
/* 字库表 */
#define OSMSG_GBFONTOK OSMSG("\r\n\GB2312 Font Table OK.\r\n")
#define OSMSG_GBFONTERROR OSMSG("\r\n\GB2312 Font Table Error!\r\n")
#define OSMSG_GBFONTLOAD OSMSG("\r\n\Loading GB2312 Font...\r\n")
#define OSMSG_OPENFONTOK OSMSG("\r\n\Open Font File OK!\r\n")
#define OSMSG_OPENFONTERROR OSMSG("\r\n\Open Font File ERROR!\r\n")
#define OSMSG_OPENFONTERRORTIP OSMSG("\r\n\Set the font file is stored in the SD card!\r\n")


#define	OSMSG_WRITEFONTINF 	OSMSG("Is being written to GB2312 font, please wait...\r\n")


 

/* 任务函数声明 */
extern void OSMainTask(void *pdat);
extern void MenuApp(void *pdat);
extern void OSTimeTask(void *pdat);
extern void SDCheckTask(void *pdat);

#endif /* __OSMSG_H__ */
