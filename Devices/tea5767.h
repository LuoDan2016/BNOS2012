/******************** (C) COPYRIGHT 2012 BOOLESION.NET ***************************
* ��Ʒ����: ������51������ E1101
* �ļ�����: TEA5767.H
* ��������: BOOLESION.NET ������(BOOLESION)���ӿƼ� - NETC (�½���)
* ����汾: V1.2
* ��������: 2012/03/20
* ��������: �ļ�����.
**********************************************************************************/

#ifndef __TEA5767_H__
#define __TEA5767_H__
/* Ӳ���ӿڶ��� -----------------------------------------------------------------*/
sbit SDA=P2^3;  /* I2C  ���� */ 
sbit SCL=P2^4;  /* I2C  ʱ�� */
sbit FM_SW =P4^0;

void radio_read(void);
void search(bit mode);
void auto_search(bit mode);
void radio_write(void);
void radio_close(void);
void Signal_CH_Show(void);
void FreqShow(INT32U freq);

#endif /* END __TEA5767_H__ */
