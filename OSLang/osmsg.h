/******************** (C) COPYRIGHT 2012 BOOLESION.NET ***************************
* ��Ʒ����: BNOS 2012
* �ļ�����: osmsg.h
* ��������: BOOLESION.NET ������(BOOLESION)���ӿƼ� - NETC (�½���)
* ����汾: V1.2
* ��������: 2012/03/20
* ��������: BNOS ϵͳ��ӡ��Ϣ.
**********************************************************************************/
#ifndef __OSMSG_H__
#define __OSMSG_H__

/* ���ں���ת�� */
#define OSMSG TransmitString
/* BNOS������Ϣ */
#define	OSMSG_STAR 	;\
    OSMSG("\r\nBNOS 2012 Start ... \r\n");\
	OSMSG("******************** (C) COPYRIGHT 2012 BOOLESION.NET ************************\r\n");\
	OSMSG("** Product Name  : BNOS 2012(BNOS For 8051)\r\n");\
	OSMSG("** Program Author: BOOLESION - BOOLESION.NET -�½��� NETC	\r\n");\
	OSMSG("** Version       : V1.2	   \r\n");\
	OSMSG("** Date          : 2012/03/20	\r\n");\
	OSMSG("------------------------------------------------------------------------------\r\n");\
	OSMSG("******************************************************************************\r\n");\
/* LCD TFT��ʼ�� */
#define OSMSG_LCDINIT OSMSG("\r\nLCD Initialize OK...LCD ID:OTM4001.")
/* SPI Flash ��ʼ�� */
#define	OSMSG_FLASHINIT OSMSG("\r\nSPI Flash Initialize.")
/* SD/TF����ʼ�� */
#define	OSMSG_SDINIT OSMSG("\r\nSD/TF Card Initialize...")

#define OSMSG_SDERROR OSMSG("\r\TF/SD Crad Initialize ERROR!\r\n")
#define OSMSG_MOUNTOK OSMSG("\r\nFatFs MOUNT OK!\r\n")
/* VS1003��ʼ����Ϣ */
#define OSMSG_VSINIT OSMSG("VS1003 Initialize...\r\n")
/* �ֿ�� */
#define OSMSG_GBFONTOK OSMSG("\r\n\GB2312 Font Table OK.\r\n")
#define OSMSG_GBFONTERROR OSMSG("\r\n\GB2312 Font Table Error!\r\n")
#define OSMSG_GBFONTLOAD OSMSG("\r\n\Loading GB2312 Font...\r\n")
#define OSMSG_OPENFONTOK OSMSG("\r\n\Open Font File OK!\r\n")
#define OSMSG_OPENFONTERROR OSMSG("\r\n\Open Font File ERROR!\r\n")
#define OSMSG_OPENFONTERRORTIP OSMSG("\r\n\Set the font file is stored in the SD card!\r\n")


#define	OSMSG_WRITEFONTINF 	OSMSG("Is being written to GB2312 font, please wait...\r\n")


 

/* ���������� */
extern void OSMainTask(void *pdat);
extern void MenuApp(void *pdat);
extern void OSTimeTask(void *pdat);
extern void SDCheckTask(void *pdat);

#endif /* __OSMSG_H__ */
