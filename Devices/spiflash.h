/******************** (C) COPYRIGHT 2012 BOOLESION.NET ***************************
* ��Ʒ����: ������51������ E1101
* �ļ�����: SPIFLASH.H
* ��������: BOOLESION.NET ������(BOOLESION)���ӿƼ� - NETC (�½���)
* ����汾: V1.1
* ��������: 2012/01/20
* ��������: �ļ�����.
**********************************************************************************/

#ifndef __SPIFLASH_H__
#define __SPIFLASH_H__

/* ���ܼĴ�����ַ */
#define WRITE_ENABLE 0X06
#define WRITE_DISABLE 0X04
#define READ_ID 0X9F
#define READ_STAUS_REG 0X05
#define WRITE_STAUS_REG 0X01
#define READ_DATA 0X03
#define FAST_READ_DATA 0X0B
#define PAGE_PROGRAM 0X02
#define SECTOR_ERASE 0XD8
#define BULK_ERASE 0XC7
#define DEEP_POWER_DOWN 0XB9
#define WAKE_UP 0XAB

/* Ƭѡ */
sbit SPI_CS = P2^5;
#define Select_Flash()     SPI_CS=0
#define NotSelect_Flash()  SPI_CS=1

/* �洢���� */
#define GB2312_TABLE_BASE 0
#define SPI_FLASH_PAGE_SIZE  256       /*  ÿҳ256���ֽ� */
#define CHARATER_CODE_TABLE_SIZE 87172 /* ���size����λ:�ֽ� */
#define TABLE_MAX_PAGE 341             /* 87172/512+1 */


void M25P16_Fast_Read_Data(unsigned long  addr,unsigned int len,INT8U *buf);
void M25P16_Read_Id(unsigned char * id);
void M25P16_Page_Program(unsigned long addr,unsigned int len,INT8U *buf);
void M25P16_Sector_Erase(unsigned long addr);
void M25P16_Bulk_Erase(void);
unsigned char M25P16_Init(void);

/*
** GN2312�� ����� 0 - 282752  �ֽ�
*/

#endif /* END __SPIFLASH_H__ */