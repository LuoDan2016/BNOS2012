/******************** (C) COPYRIGHT 2012 BOOLESION.NET ***************************
* 产品名称: 布尔创51开发板 E1101
* 文件名称: SPI.H
* 程序作者: BOOLESION.NET 布尔创(BOOLESION)电子科技 - NETC (陈建长)
* 程序版本: V1.2
* 编制日期: 2012/03/20
* 功能描述: 文件包含.
**********************************************************************************/

#ifndef __SPI_H__
#define __SPI_H__

#define	FCLK_SLOW()		SPCTL=0xd1; /* Set slow clock  */
#define	FCLK_FAST()		SPCTL=0xd0; /* Set fast clock  */

void SPI_Init(void);
/*SPI发送数据函数*/
void spiTx(INT8U sddat);
/*SPI接收数据函数*/
INT8U spiRx();
void SPI_Flash_Write(INT8U w_dat);
INT8U SPI_Flash_Read(void);
#endif	/* END __SPI_H__ */
