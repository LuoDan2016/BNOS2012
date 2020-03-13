/******************** (C) COPYRIGHT 2012 BOOLESION.NET ***************************
* 产品名称: 布尔创51开发板 E1101
* 文件名称: sdcard.c
* 程序作者: BOOLESION.NET 布尔创(BOOLESION)电子科技 - NETC (陈建长)
* 程序版本: V1.1
* 编制日期: 2012/01/20
* 功能描述: SD卡 驱动程序.
**********************************************************************************/

/* Includes ---------------------------------------------------------------------*/
#include "includes.h"	


/*********************************************************************************
** 函数名称: INT8U SD_sendCommand(INT8U cmd, INT32U arg).
** 功能描述: 向SD卡发送命令.
** 输入参数: INT8U cmd, INT32U arg.         
** 输出参数: None.
** 返回参数: return response .
**********************************************************************************/
INT8U SD_sendCommand(INT8U cmd, INT32U arg)
{
	INT8U response = 0xff;
	INT8U retry = 0;

	SD_CS_DEASSERT;
	spiTx(0xff); 
	SD_CS_ASSERT;
	spiTx(0xff);

	spiTx(cmd); 				/* 发送命令 */
	spiTx(arg>>24);
	spiTx(arg>>16);
	spiTx(arg>>8);
	spiTx(arg);
	spiTx(0x95);				/* CRC校验可选  CMD0命令时必须为 0x95 */

	do							/* 等待回应 */
	{
		response=spiRx(); 			
    	if(retry++ > 0xfe) break;	/* 超时 */
	}while(response == 0xff);

	SD_CS_DEASSERT;
	spiTx(0xff);
	
	return response;
}

/*********************************************************************************
** 函数名称: INT8U SD_init(void).
** 功能描述: SD卡初始化.
** 输入参数: None.         
** 输出参数: None.
** 返回参数: 正确 0 错误1 .
**********************************************************************************/
INT8U SD_init(void)
{
	INT8U response = 0xff;
	INT8U retry = 0;
	INT8U i = 0;

	FCLK_SLOW(); 				/* SPI低速模式 CLK <= 400kHz */
	
	SD_CS_DEASSERT;				/* CS和DI同时为高电平 */
	for(i=0;i<10;i++)
		spiTx(0xff); 			/* 80 clk  至少74个 */

	SD_CS_ASSERT;	  			/* CS片选信号拉低 */

	do
	{
		response = SD_sendCommand(CMD0, 0); 	/* 发送复位命令，若成功，返回0x01 */
		retry++;
		if(retry > 0xfe)	return 1; 			/* 超时 */
			
   	}while(response!=0x01);

	retry = 0;
	do
	{
	   	response = SD_sendCommand(CMD1, 0); 	/* 重复一次，提高对卡的兼容性 */
		retry++;
    	if(retry > 0xfe)	return 1; 			/* 超时 */
	}while(response);

	SD_sendCommand(CMD16, 512); /* 设定读写数据块长度,每个数据块设定为512Byte */

	FCLK_FAST(); 				/* SPI高速模式 */

	return 0; 					/* 正常返回 */
}
#if 0
/*********************************************************************************
** 函数名称: INT8U SD_erase(INT32U startBlock, INT32U totalBlocks).
** 功能描述: SD卡擦除块.
** 输入参数: INT32U startBlock, INT32U totalBlocks.         
** 输出参数: None.
** 返回参数: 正确 0 错误 错误代码 .
**********************************************************************************/
INT8U SD_erase(INT32U startBlock, INT32U totalBlocks)
{
	INT8U response;

	response = SD_sendCommand(CMD32, startBlock<<9); 	/* 发送起始块地址 */
	if(response != 0x00) 		                        /* 检测SD卡状态，0x00转态正常 */
  		return response;

	response = SD_sendCommand(CMD33,(startBlock + totalBlocks - 1)<<9); 	/* 发送结束块地址 */
	if(response != 0x00)
  		return response;

	response = SD_sendCommand(CMD38, 0); 	/* 擦除全部所选的块 */
	if(response != 0x00)
  		return response;

	return 0; 					            /* 正常返回 */
}

/*********************************************************************************
** 函数名称: INT8U SD_readSingleBlock(INT8U *buff, INT32U startBlock).
** 功能描述: SD卡读单个块.
** 输入参数: INT8U *buff, INT32U startBlock.         
** 输出参数: None.
** 返回参数: 正确 0 错误 1.
**********************************************************************************/
INT8U SD_readSingleBlock(INT8U *buff, INT32U startBlock)
{
	if(SD_sendCommand(CMD17, startBlock<<9)) return 1;

	if(receive_DataBlock(buff, 512)) return 1;

	return 0;
}

#endif	/* INT8U SD_erase(INT32U startBlock, INT32U totalBlocks) */

#if 0
/*********************************************************************************
** 函数名称: INT8U receive_DataBlock(INT8U *buff,INT16U btr).
** 功能描述: SD卡接收数据块.
** 输入参数: INT8U *buff 数据缓冲区，用于存储接收的数据,INT16U btr 字节数(必须为4的整倍数).         
** 输出参数: None.
** 返回参数: 正确 0 错误 1.
**********************************************************************************/
INT8U receive_DataBlock(INT8U *buff,INT16U btr)
{
	INT8U response = 0xff;
	INT16U retry = 0;

	SD_CS_ASSERT;
	do 							/* 等待起始数据块数据标志0xfe (0x11111110) */
	{
		response=spiRx();
    	if(retry++ > 0xfffe) 	/* 超时 */
		{
			SD_CS_DEASSERT;
			return 1;
		}
	}while(response != 0xfe); 	/* 等待回应 */

	do 							/* 接收到的数据块数据存入缓冲区 */
	{
		*buff++=spiRx();
		*buff++=spiRx();
		*buff++=spiRx();
		*buff++=spiRx();
	}while(btr -= 4);

	spiRx(); 					/* 忽略CRC校验（两个字节）*/
	spiRx();

	SD_CS_DEASSERT;
	spiTx(0xff); 				/* 等待8个 clk */

	return 0;
}
#endif	 /* INT8U receive_DataBlock(INT8U *buff,INT16U btr) */