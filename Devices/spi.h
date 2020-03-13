/******************** (C) COPYRIGHT 2012 BOOLESION.NET ***************************
* ��Ʒ����: ������51������ E1101
* �ļ�����: SPI.H
* ��������: BOOLESION.NET ������(BOOLESION)���ӿƼ� - NETC (�½���)
* ����汾: V1.2
* ��������: 2012/03/20
* ��������: �ļ�����.
**********************************************************************************/

#ifndef __SPI_H__
#define __SPI_H__

#define	FCLK_SLOW()		SPCTL=0xd1; /* Set slow clock  */
#define	FCLK_FAST()		SPCTL=0xd0; /* Set fast clock  */

void SPI_Init(void);
/*SPI�������ݺ���*/
void spiTx(INT8U sddat);
/*SPI�������ݺ���*/
INT8U spiRx();
void SPI_Flash_Write(INT8U w_dat);
INT8U SPI_Flash_Read(void);
#endif	/* END __SPI_H__ */
