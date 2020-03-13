/******************** (C) COPYRIGHT 2012 BOOLESION.NET ***************************
* ��Ʒ����: BNOS 2012
* �ļ�����: devicesinit.h
* ��������: BOOLESION.NET ������(BOOLESION)���ӿƼ� - NETC (�½���)
* ����汾: V1.2
* ��������: 2012/03/20
* ��������: BNOS �豸��ʼ��.
**********************************************************************************/

#ifndef __DEVICESINIT_H__
#define __DEVICESINIT_H__
/* SPI FLASH ���ݴ洢�� */
/* 
**ʹ��Imaga2LCD.EXE��BMP�ļ�ת��ΪC��������
**ʹ��Text2Bin.exe��C���������ļ�ת����2�����ļ�
**BMP�ļ�������ͷ�ļ�����
**GB2312      GB2312�����ֿ�� 0 - 261695 �ֽ�
**SLOGO     	ͼ���ļ� 100 x 66  24bit �ֽ�
**Music  			����ͼ��  281497 - 287436 �ֽ�
**Photos 			���ͼ��  287437 - 293376 �ֽ�
**Ridio 			������ͼ��  293377 - 299316 �ֽ�
**Calendar  	������ͼ��  299317 - 305256 �ֽ�
**Ebook 			������ͼ��  305257 - 311196 �ֽ�
**Calculator 	������ͼ��  311197 - 317136 �ֽ�
**Application ����ͼ��  317137 - 323076 �ֽ�
**Settings 		����ͼ��  323077 - 329016 �ֽ�
*/

/* GB2312 �ֿ���ַ 0 - 261695*/
#define	FLASHADDR_GB2312 	0
/* ������LOGO SLOGO 261696 -  281496  */
#define	FLASHADDR_SLOGO   	261696	
/* ����ͼ��  281497 - 287436*/
#define	FLASHADDR_MUSIC		281497
/* Photos ���ͼ��  287437 - 293376 �ֽ� */
#define	FLASHADDR_PHOTOS	287437
/* Ridio ������ͼ��  293377 - 299316 �ֽ� */
#define	FLASHADDR_RADIO	     293377
/* Calendar ������ͼ��  299317 - 305256 �ֽ� */
#define	FLASHADDR_CALENDAR	     299317
/* Ebook ������ͼ��  305257 - 311196 �ֽ� */
#define	FLASHADDR_EBOOK	     305257
/* Calculator ������ͼ��  311197 - 317136 �ֽ� */
#define	FLASHADDR_CALCU	     311197
/* Application ����ͼ��  317137 - 323076 �ֽ� */
#define	FLASHADDR_APP     317137
/* Settings ����ͼ��  323077 - 329016 �ֽ� */
#define	FLASHADDR_SETTINGS     323077
void DeviceInit(void);
void FontGUILoad(void);

#endif	/* __DEVICESINIT_H__ */

