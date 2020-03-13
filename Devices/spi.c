/******************** (C) COPYRIGHT 2012 BOOLESION.NET ***************************
* ��Ʒ����: ������51������ E1101
* �ļ�����: spi.c
* ��������: BOOLESION.NET ������(BOOLESION)���ӿƼ� - NETC (�½���)
* ����汾: V1.2
* ��������: 2012/03/20
* ��������: SPI ��������.
**********************************************************************************/

/* Includes ---------------------------------------------------------------------*/
#include "includes.h"

/* STCӲ��SPIӲ���ӿ� -----------------------------------------------------------*/
/*
** SD_CS   P1^4
** SD_MOSI P1^5
** SD_MISO P1^6 
** SD_SCLK P1^7   
*/ 


//SPI��ʼ��
void SPI_Init(void)
{
    SPDAT = 0;                	//���ݼĴ�����0
    SPSTAT = 0xC0;       		//��SPI״̬SPIF��WCOLд1��0
	SPCTL = 0xDE;				//11011110b����SSλ����MSB������ģʽ��ʱ�ӿ���ʱΪ�ߵ�ƽ����ʼ�����ã������ز���	
}

//SPIʱ����������
void SPI_SetSpeed(unsigned char speed)
{
	switch(speed)
	{
		case 0:	SPCTL&=0xFC;break;				//SysClk/4,SPR1=0,SPR0=0 
		case 1:	SPCTL&=0xFD;SPCTL|=0x01;break; 	//SysClk/16,SPR1=0,SPRO=1
		case 2:	SPCTL|=0x02;SPCTL&=0xFE;break;	//SysClk/64,SPR1=1,SPR0=0
		case 3:	SPCTL|=0x03;break;				//SysClk/128,SPR1=1,SPR0=1
	}
}
/*********************************************************************************
** ��������: void spiTx(INT8U sddat).
** ��������: SPI�������ݺ���.
** �������: INT8U sddat д���ֽ�.         
** �������: None.
** ���ز���: None.
**********************************************************************************/
void spiTx(INT8U sddat)
{
	SPDAT=sddat;
	while((SPSTAT&0x80)==0);
	SPSTAT=0x80;  /* SPIFд1��0 */
}

/*********************************************************************************
** ��������: void spiTx(INT8U sddat).
** ��������: SPI�������ݺ���.
** �������: None.         
** �������: None.
** ���ز���: None.
**********************************************************************************/
INT8U spiRx()
{
	SPDAT = 0xff;
	while((SPSTAT&0x80)==0);
	SPSTAT=0x80;  /*  SPIFд1��0 */
	return SPDAT;
}
/* ��SPI�ӿڶ��� -------------------------------------------------------------------------*/

//sbit SPI_CS =P2^5;
sbit SPI_MOSI =P4^4; 
sbit SPI_SCLK =P2^7;   
sbit SPI_MISO =P2^6; 

/* ȫ�ֱ������� -------------------------------------------------------------------------*/
INT8U bdata dat;
sbit dat7=dat^7;
sbit dat6=dat^6;
sbit dat5=dat^5;
sbit dat4=dat^4;
sbit dat3=dat^3;
sbit dat2=dat^2;
sbit dat1=dat^1;
sbit dat0=dat^0;

/*********************************************************************************
** ��������: void SPI_WriteByte(uchar w_dat).
** ��������: SPI�ӿڸ���д�ֽں���.
** �������: INT8U w_dat Ҫд����ֽ�.         
** �������: None.
** ���ز���: None.
**********************************************************************************/
void SPI_Flash_Write(INT8U w_dat) 
{
	dat=w_dat; 
	SPI_MOSI=dat7;SPI_SCLK=0;SPI_SCLK=1;
	SPI_MOSI=dat6;SPI_SCLK=0;SPI_SCLK=1;
	SPI_MOSI=dat5;SPI_SCLK=0;SPI_SCLK=1;
	SPI_MOSI=dat4;SPI_SCLK=0;SPI_SCLK=1;
	SPI_MOSI=dat3;SPI_SCLK=0;SPI_SCLK=1;
	SPI_MOSI=dat2;SPI_SCLK=0;SPI_SCLK=1;
	SPI_MOSI=dat1;SPI_SCLK=0;SPI_SCLK=1;
	SPI_MOSI=dat0;SPI_SCLK=0;SPI_SCLK=1;
}

/*********************************************************************************
** ��������: INT8U SPI_Flash_Read(void).
** ��������: SPI�ӿڸ��ٶ��ֽں���.
** �������: None.         
** �������: None.
** ���ز���: return (dat) �������ֽ�.
**********************************************************************************/
INT8U SPI_Flash_Read(void)
{  
	SPI_MISO=1;
	SPI_SCLK=1;SPI_SCLK=0;dat7=SPI_MISO; 
	SPI_SCLK=1;SPI_SCLK=0;dat6=SPI_MISO;
	SPI_SCLK=1;SPI_SCLK=0;dat5=SPI_MISO;
	SPI_SCLK=1;SPI_SCLK=0;dat4=SPI_MISO;
	SPI_SCLK=1;SPI_SCLK=0;dat3=SPI_MISO;
	SPI_SCLK=1;SPI_SCLK=0;dat2=SPI_MISO;
	SPI_SCLK=1;SPI_SCLK=0;dat1=SPI_MISO;
	SPI_SCLK=1;SPI_SCLK=0;dat0=SPI_MISO;
	return (dat);
}
