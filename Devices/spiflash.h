/******************** (C) COPYRIGHT 2012 BOOLESION.NET ***************************
* 产品名称: 布尔创51开发板 E1101
* 文件名称: SPIFLASH.H
* 程序作者: BOOLESION.NET 布尔创(BOOLESION)电子科技 - NETC (陈建长)
* 程序版本: V1.1
* 编制日期: 2012/01/20
* 功能描述: 文件包含.
**********************************************************************************/

#ifndef __SPIFLASH_H__
#define __SPIFLASH_H__

/* 功能寄存器地址 */
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

/* 片选 */
sbit SPI_CS = P2^5;
#define Select_Flash()     SPI_CS=0
#define NotSelect_Flash()  SPI_CS=1

/* 存储定义 */
#define GB2312_TABLE_BASE 0
#define SPI_FLASH_PAGE_SIZE  256       /*  每页256个字节 */
#define CHARATER_CODE_TABLE_SIZE 87172 /* 表的size，单位:字节 */
#define TABLE_MAX_PAGE 341             /* 87172/512+1 */


void M25P16_Fast_Read_Data(unsigned long  addr,unsigned int len,INT8U *buf);
void M25P16_Read_Id(unsigned char * id);
void M25P16_Page_Program(unsigned long addr,unsigned int len,INT8U *buf);
void M25P16_Sector_Erase(unsigned long addr);
void M25P16_Bulk_Erase(void);
unsigned char M25P16_Init(void);

/*
** GN2312表 存放于 0 - 282752  字节
*/

#endif /* END __SPIFLASH_H__ */