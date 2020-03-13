/******************** (C) COPYRIGHT 2012 BOOLESION.NET ***************************
* 产品名称: 布尔创51开发板 E1101
* 文件名称: SDCARD.H
* 程序作者: BOOLESION.NET 布尔创(BOOLESION)电子科技 - NETC (陈建长)
* 程序版本: V1.1
* 编制日期: 2012/01/20
* 功能描述: 文件包含.
**********************************************************************************/

#ifndef __SDCARD_H__
#define __SDCARD_H__

/*命令宏*/
#define CMD0	  	(0x40+0)	/* GO_IDLE_STATE */
#define CMD1	  	(0x40+1)	/* SEND_OP_COND */
#define ACMD41		(0xC0+41)	/* SEND_OP_COND */
#define CMD8	  	(0x40+8)	/* SEND_IF_COND */
#define CMD9	  	(0x40+9)	/* SEND_CSD */
#define CMD10 		(0x40+10)	/* SEND_CID */
#define CMD12	  	(0x40+12)	/* STOP_TRANSMISSION */
#define ACMD13		(0xC0+13)	/* SD_STATUS */
#define CMD16	  	(0x40+16)	/* SET_BLOCKLEN */
#define CMD17	  	(0x40+17)	/* READ_SINGLE_BLOCK */
#define CMD18	  	(0x40+18)	/* READ_MULTIPLE_BLOCK */
#define ACMD23		(0xC0+23)	/* SET_WR_BLK_ERASE_COUNT */
#define CMD24	  	(0x40+24)	/* WRITE_BLOCK */
#define CMD25	  	(0x40+25)	/* WRITE_MULTIPLE_BLOCK */
#define CMD32	  	(0x40+32)	/* ERASE_BLOCK_START_ADDR */
#define CMD33	  	(0x40+33)	/* ERASE_BLOCK_END_ADDR */
#define CMD38	  	(0x40+38)	/* ERASE_SELECTED_BLOCKS */
#define CMD55	  	(0x40+55)	/* APP_CMD */
#define CMD58	  	(0x40+58)	/* READ_OCR */

/* 定义SD卡CS引脚 */
sbit    SD_CS       =         	P1^4;
#define SD_CS_ASSERT     	SD_CS = 0
#define SD_CS_DEASSERT   	SD_CS = 1

/*SD卡初始化*/
INT8U SD_init(void);

/*命令发送函数*/
INT8U SD_sendCommand(INT8U cmd, INT32U arg);

/*块擦除*/
INT8U SD_erase (INT32U startBlock, INT32U totalBlocks);

INT8U SD_readSingleBlock(INT8U *buff, INT32U startBlock);
INT8U receive_DataBlock(INT8U *buff,INT16U btr);

#endif /* END __SDCARD_H__ */
