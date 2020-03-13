/******************** (C) COPYRIGHT 2012 BOOLESION.NET ***************************
* 产品名称: 布尔创51开发板 E1101
* 文件名称: UART.H
* 程序作者: BOOLESION.NET 布尔创(BOOLESION)电子科技 - NETC (陈建长)
* 程序版本: V1.1
* 编制日期: 2012/01/20
* 功能描述: 文件包含.
**********************************************************************************/

#ifndef __UART_H__
#define __UART_H__


#define USE_TransmitByte 0	 /* 暂不使用函数 */
#define USE_TransmitHex  0

void UartInit(void);
/*从串口发送一个字节数据*/
void TransmitByte(INT8U byte);
/*从串口发送字符串*/
void TransmitString(INT8U *String);
/*以16进制格式发送一个字节数据*/
void TransmitHex(INT8U hex);

	
#endif	/* END __UART_H__ */
