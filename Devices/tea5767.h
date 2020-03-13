/******************** (C) COPYRIGHT 2012 BOOLESION.NET ***************************
* 产品名称: 布尔创51开发板 E1101
* 文件名称: TEA5767.H
* 程序作者: BOOLESION.NET 布尔创(BOOLESION)电子科技 - NETC (陈建长)
* 程序版本: V1.2
* 编制日期: 2012/03/20
* 功能描述: 文件包含.
**********************************************************************************/

#ifndef __TEA5767_H__
#define __TEA5767_H__
/* 硬件接口定义 -----------------------------------------------------------------*/
sbit SDA=P2^3;  /* I2C  数据 */ 
sbit SCL=P2^4;  /* I2C  时钟 */
sbit FM_SW =P4^0;

void radio_read(void);
void search(bit mode);
void auto_search(bit mode);
void radio_write(void);
void radio_close(void);
void Signal_CH_Show(void);
void FreqShow(INT32U freq);

#endif /* END __TEA5767_H__ */
