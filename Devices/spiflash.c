/******************** (C) COPYRIGHT 2012 BOOLESION.NET ***************************
* 产品名称: 布尔创51开发板 E1101
* 文件名称: spiflash.c
* 程序作者: BOOLESION.NET 布尔创(BOOLESION)电子科技 - NETC (陈建长)
* 程序版本: V1.2
* 编制日期: 2012/03/20
* 功能描述: SPI FLASH W25X16驱动程序.
**********************************************************************************/

/* Includes ---------------------------------------------------------------------*/
#include "includes.h"

/* 变量声明 ---------------------------------------------------------------------*/

#if 0
/*********************************************************************************
** 函数名称: void M25P16_Read_Id(INT8U * id).
** 功能描述: 读取芯片ID.
** 输入参数: INT8U * id.         
** 输出参数: None.
** 返回参数: None.
**********************************************************************************/
void M25P16_Read_Id(INT8U * id)
{
	INT8U i;	
	Select_Flash();	
	SPI_Flash_Write(READ_ID);	
	for(i=0;i<20;i++)
	{
		id[i] = SPI_Flash_Read();
	}
	NotSelect_Flash();
}
#endif /* M25P16_Read_Id */
/*********************************************************************************
** 函数名称: void SPI_FLASH_Write_Enable(void).
** 功能描述: SPI_FLASH写使能，将WEL置位.
** 输入参数: None.         
** 输出参数: None.
** 返回参数: None.
**********************************************************************************/
void M25P16_Write_Enable(void)
{
	Select_Flash();	
	SPI_Flash_Write(WRITE_ENABLE);	
	NotSelect_Flash();
}



/*********************************************************************************
** 函数名称: void SPI_FLASH_Write_Disable(void).
** 功能描述: SPI_FLASH写禁止， 将WEL清零.
** 输入参数: None.         
** 输出参数: None.
** 返回参数: None.
**********************************************************************************/
void M25P16_Write_Disable(void)
{
	Select_Flash();	
	SPI_Flash_Write(WRITE_DISABLE);	
	NotSelect_Flash();
}

/*********************************************************************************
** 函数名称: void SPI_Flash_Read(INT8U* pBuffer,INT16U ReadAddr,u16 NumByteToRead).
** 功能描述: 读取SPI FLASH， 在指定地址开始读取指定长度的数据.
** 输入参数: pBuffer:数据存储区
			 ReadAddr:开始读取的地址(24bit)
			 NumByteToRead:要读取的字节数(最大65535).         
** 输出参数: None.
** 返回参数: None.
**********************************************************************************/
INT8U M25P16_Read_Status_Reg(void)
{
	INT8U sta;
	
	Select_Flash();	
	SPI_Flash_Write(READ_STAUS_REG);	
 
	sta= SPI_Flash_Read();	
	
	NotSelect_Flash();
	
	return sta;
}

/*********************************************************************************
** 函数名称: void M25P16_Write_Status_Reg(INT8U reg).
** 功能描述: 读取SPI FLASH， 在指定地址开始读取指定长度的数据.
** 输入参数: INT8U reg.         
** 输出参数: None.
** 返回参数: None.
**********************************************************************************/
void M25P16_Write_Status_Reg(INT8U reg)
{
	Select_Flash();	
	SPI_Flash_Write(WRITE_STAUS_REG);	
	SPI_Flash_Write(reg);
	NotSelect_Flash();
}

/*********************************************************************************
** 函数名称: void M25P16_Page_Program(INT16U addr,u16 len,INT8U *buf).
** 功能描述: 页编程函数，页编程前一定要进行页擦除.
** 输入参数: INT16U addr,u16 len,INT8U *buf.         
** 输出参数: None.
** 返回参数: None.
**********************************************************************************/
//void M25P16_Page_Program(INT16U addr,unsigned short len,INT8U *buf)
void M25P16_Page_Program(unsigned long addr,unsigned int len,INT8U *buf)

{
	INT32U i;
	
	M25P16_Write_Enable();
	Select_Flash();	
	SPI_Flash_Write(PAGE_PROGRAM);	
	SPI_Flash_Write((addr>>16) & 0xff);
	SPI_Flash_Write((addr>>8) & 0xff);
	SPI_Flash_Write(addr & 0xff);

	for(i=0;i<len;i++)
		SPI_Flash_Write(buf[i]);

	NotSelect_Flash();

	while(M25P16_Read_Status_Reg()&0x01);	
}

/*********************************************************************************
** 函数名称: void M25P16_Sector_Erase(INT16U addr).
** 功能描述: 页擦除.
** 输入参数: INT16U addr.         
** 输出参数: None.
** 返回参数: None.
**********************************************************************************/
void M25P16_Sector_Erase(unsigned long addr)
{
	M25P16_Write_Enable();

	Select_Flash();	
	SPI_Flash_Write(SECTOR_ERASE);	
	SPI_Flash_Write((addr>>16) & 0xff);
	SPI_Flash_Write((addr>>8) & 0xff);
	SPI_Flash_Write(addr & 0xff);
	NotSelect_Flash();

	while(M25P16_Read_Status_Reg()&0x01);
}

/*********************************************************************************
** 函数名称: void M25P16_Bulk_Erase(void).
** 功能描述: 全部擦除.
** 输入参数: None.         
** 输出参数: None.
** 返回参数: None.
**********************************************************************************/
void M25P16_Bulk_Erase(void)
{
	M25P16_Write_Enable();
	Select_Flash();	
	SPI_Flash_Write(BULK_ERASE);	
	NotSelect_Flash();

	while(M25P16_Read_Status_Reg()&0x01);
}

/*********************************************************************************
** 函数名称: void M25P16_Bulk_Erase(void).
** 功能描述: 休眠状态.
** 输入参数: None.         
** 输出参数: None.
** 返回参数: None.
**********************************************************************************/
void M25P16_Deep_Power_Down(void)
{
	Select_Flash();	
	SPI_Flash_Write(DEEP_POWER_DOWN);	
	NotSelect_Flash();
}

/*********************************************************************************
** 函数名称: INT8U M25P16_Wake_Up(void).
** 功能描述: 唤醒函数.
** 输入参数: None.         
** 输出参数: None.
** 返回参数: None.
**********************************************************************************/
INT8U M25P16_Wake_Up(void)
{
	INT8U res;

	Select_Flash();	
	SPI_Flash_Write(WAKE_UP);	
	SPI_Flash_Write(0);	
	SPI_Flash_Write(0);	
	SPI_Flash_Write(0);	
	res=SPI_Flash_Read();
	
	NotSelect_Flash();
    
	return res;
}

/*********************************************************************************
** 函数名称: void M25P16_Fast_Read_Data(INT16U addr,INT16U len,INT8U *buf).
** 功能描述: 快速读数据.
** 输入参数: INT16U addr,INT16U len,INT8U *buf.         
** 输出参数: None.
** 返回参数: None.
**********************************************************************************/
//void M25P16_Fast_Read_Data(INT16U addr,INT16U len,INT8U *buf)
void M25P16_Fast_Read_Data(unsigned long  addr,unsigned int len,INT8U *buf)
{
	INT32U i;

	Select_Flash();	
	SPI_Flash_Write(FAST_READ_DATA);	
	SPI_Flash_Write((addr>>16) & 0xff);
	SPI_Flash_Write((addr>>8) & 0xff);
	SPI_Flash_Write(addr & 0xff);
	SPI_Flash_Write(0);
	
	for(i=0;i<len;i++)
	{
		buf[i]=SPI_Flash_Read();
	}
	NotSelect_Flash();
}

/*********************************************************************************
** 函数名称: INT8U M25P16_Init(void).
** 功能描述: SPI FLASH 初始化.
** 输入参数: None.         
** 输出参数: None.
** 返回参数: FLASH_ID 器件ID.
**********************************************************************************/
INT8U M25P16_Init(void)
{	
// 	INT8U *FLASH_ID;
	/* 不选flash */
	NotSelect_Flash();
//	M25P16_Read_Id(FLASH_ID);
//	return FLASH_ID;
}

