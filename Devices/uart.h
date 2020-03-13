/******************** (C) COPYRIGHT 2012 BOOLESION.NET ***************************
* ��Ʒ����: ������51������ E1101
* �ļ�����: UART.H
* ��������: BOOLESION.NET ������(BOOLESION)���ӿƼ� - NETC (�½���)
* ����汾: V1.1
* ��������: 2012/01/20
* ��������: �ļ�����.
**********************************************************************************/

#ifndef __UART_H__
#define __UART_H__


#define USE_TransmitByte 0	 /* �ݲ�ʹ�ú��� */
#define USE_TransmitHex  0

void UartInit(void);
/*�Ӵ��ڷ���һ���ֽ�����*/
void TransmitByte(INT8U byte);
/*�Ӵ��ڷ����ַ���*/
void TransmitString(INT8U *String);
/*��16���Ƹ�ʽ����һ���ֽ�����*/
void TransmitHex(INT8U hex);

	
#endif	/* END __UART_H__ */
