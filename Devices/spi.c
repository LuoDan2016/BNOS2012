/******************** (C) COPYRIGHT 2012 BOOLESION.NET ***************************
* 产品名称: 布尔创51开发板 E1101
* 文件名称: spi.c
* 程序作者: BOOLESION.NET 布尔创(BOOLESION)电子科技 - NETC (陈建长)
* 程序版本: V1.2
* 编制日期: 2012/03/20
* 功能描述: SPI 驱动程序.
**********************************************************************************/

/* Includes ---------------------------------------------------------------------*/
#include "includes.h"

/* STC硬件SPI硬件接口 -----------------------------------------------------------*/
/*
** SD_CS   P1^4
** SD_MOSI P1^5
** SD_MISO P1^6 
** SD_SCLK P1^7   
*/ 


//SPI初始化
void SPI_Init(void)
{
    SPDAT = 0;                	//数据寄存器清0
    SPSTAT = 0xC0;       		//清SPI状态SPIF和WCOL写1清0
	SPCTL = 0xDE;				//11011110b忽略SS位，先MSB、主机模式、时钟空闲时为高电平、起始沿设置，结束沿采样	
}

//SPI时钟速率设置
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
** 函数名称: void spiTx(INT8U sddat).
** 功能描述: SPI发送数据函数.
** 输入参数: INT8U sddat 写入字节.         
** 输出参数: None.
** 返回参数: None.
**********************************************************************************/
void spiTx(INT8U sddat)
{
	SPDAT=sddat;
	while((SPSTAT&0x80)==0);
	SPSTAT=0x80;  /* SPIF写1清0 */
}

/*********************************************************************************
** 函数名称: void spiTx(INT8U sddat).
** 功能描述: SPI接收数据函数.
** 输入参数: None.         
** 输出参数: None.
** 返回参数: None.
**********************************************************************************/
INT8U spiRx()
{
	SPDAT = 0xff;
	while((SPSTAT&0x80)==0);
	SPSTAT=0x80;  /*  SPIF写1清0 */
	return SPDAT;
}
/* 软SPI接口定义 -------------------------------------------------------------------------*/

//sbit SPI_CS =P2^5;
sbit SPI_MOSI =P4^4; 
sbit SPI_SCLK =P2^7;   
sbit SPI_MISO =P2^6; 

/* 全局变量定义 -------------------------------------------------------------------------*/
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
** 函数名称: void SPI_WriteByte(uchar w_dat).
** 功能描述: SPI接口高速写字节函数.
** 输入参数: INT8U w_dat 要写入的字节.         
** 输出参数: None.
** 返回参数: None.
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
** 函数名称: INT8U SPI_Flash_Read(void).
** 功能描述: SPI接口高速读字节函数.
** 输入参数: None.         
** 输出参数: None.
** 返回参数: return (dat) 读出的字节.
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
