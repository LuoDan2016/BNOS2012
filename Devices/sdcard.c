/******************** (C) COPYRIGHT 2012 BOOLESION.NET ***************************
* ��Ʒ����: ������51������ E1101
* �ļ�����: sdcard.c
* ��������: BOOLESION.NET ������(BOOLESION)���ӿƼ� - NETC (�½���)
* ����汾: V1.1
* ��������: 2012/01/20
* ��������: SD�� ��������.
**********************************************************************************/

/* Includes ---------------------------------------------------------------------*/
#include "includes.h"	


/*********************************************************************************
** ��������: INT8U SD_sendCommand(INT8U cmd, INT32U arg).
** ��������: ��SD����������.
** �������: INT8U cmd, INT32U arg.         
** �������: None.
** ���ز���: return response .
**********************************************************************************/
INT8U SD_sendCommand(INT8U cmd, INT32U arg)
{
	INT8U response = 0xff;
	INT8U retry = 0;

	SD_CS_DEASSERT;
	spiTx(0xff); 
	SD_CS_ASSERT;
	spiTx(0xff);

	spiTx(cmd); 				/* �������� */
	spiTx(arg>>24);
	spiTx(arg>>16);
	spiTx(arg>>8);
	spiTx(arg);
	spiTx(0x95);				/* CRCУ���ѡ  CMD0����ʱ����Ϊ 0x95 */

	do							/* �ȴ���Ӧ */
	{
		response=spiRx(); 			
    	if(retry++ > 0xfe) break;	/* ��ʱ */
	}while(response == 0xff);

	SD_CS_DEASSERT;
	spiTx(0xff);
	
	return response;
}

/*********************************************************************************
** ��������: INT8U SD_init(void).
** ��������: SD����ʼ��.
** �������: None.         
** �������: None.
** ���ز���: ��ȷ 0 ����1 .
**********************************************************************************/
INT8U SD_init(void)
{
	INT8U response = 0xff;
	INT8U retry = 0;
	INT8U i = 0;

	FCLK_SLOW(); 				/* SPI����ģʽ CLK <= 400kHz */
	
	SD_CS_DEASSERT;				/* CS��DIͬʱΪ�ߵ�ƽ */
	for(i=0;i<10;i++)
		spiTx(0xff); 			/* 80 clk  ����74�� */

	SD_CS_ASSERT;	  			/* CSƬѡ�ź����� */

	do
	{
		response = SD_sendCommand(CMD0, 0); 	/* ���͸�λ������ɹ�������0x01 */
		retry++;
		if(retry > 0xfe)	return 1; 			/* ��ʱ */
			
   	}while(response!=0x01);

	retry = 0;
	do
	{
	   	response = SD_sendCommand(CMD1, 0); 	/* �ظ�һ�Σ���߶Կ��ļ����� */
		retry++;
    	if(retry > 0xfe)	return 1; 			/* ��ʱ */
	}while(response);

	SD_sendCommand(CMD16, 512); /* �趨��д���ݿ鳤��,ÿ�����ݿ��趨Ϊ512Byte */

	FCLK_FAST(); 				/* SPI����ģʽ */

	return 0; 					/* �������� */
}
#if 0
/*********************************************************************************
** ��������: INT8U SD_erase(INT32U startBlock, INT32U totalBlocks).
** ��������: SD��������.
** �������: INT32U startBlock, INT32U totalBlocks.         
** �������: None.
** ���ز���: ��ȷ 0 ���� ������� .
**********************************************************************************/
INT8U SD_erase(INT32U startBlock, INT32U totalBlocks)
{
	INT8U response;

	response = SD_sendCommand(CMD32, startBlock<<9); 	/* ������ʼ���ַ */
	if(response != 0x00) 		                        /* ���SD��״̬��0x00ת̬���� */
  		return response;

	response = SD_sendCommand(CMD33,(startBlock + totalBlocks - 1)<<9); 	/* ���ͽ������ַ */
	if(response != 0x00)
  		return response;

	response = SD_sendCommand(CMD38, 0); 	/* ����ȫ����ѡ�Ŀ� */
	if(response != 0x00)
  		return response;

	return 0; 					            /* �������� */
}

/*********************************************************************************
** ��������: INT8U SD_readSingleBlock(INT8U *buff, INT32U startBlock).
** ��������: SD����������.
** �������: INT8U *buff, INT32U startBlock.         
** �������: None.
** ���ز���: ��ȷ 0 ���� 1.
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
** ��������: INT8U receive_DataBlock(INT8U *buff,INT16U btr).
** ��������: SD���������ݿ�.
** �������: INT8U *buff ���ݻ����������ڴ洢���յ�����,INT16U btr �ֽ���(����Ϊ4��������).         
** �������: None.
** ���ز���: ��ȷ 0 ���� 1.
**********************************************************************************/
INT8U receive_DataBlock(INT8U *buff,INT16U btr)
{
	INT8U response = 0xff;
	INT16U retry = 0;

	SD_CS_ASSERT;
	do 							/* �ȴ���ʼ���ݿ����ݱ�־0xfe (0x11111110) */
	{
		response=spiRx();
    	if(retry++ > 0xfffe) 	/* ��ʱ */
		{
			SD_CS_DEASSERT;
			return 1;
		}
	}while(response != 0xfe); 	/* �ȴ���Ӧ */

	do 							/* ���յ������ݿ����ݴ��뻺���� */
	{
		*buff++=spiRx();
		*buff++=spiRx();
		*buff++=spiRx();
		*buff++=spiRx();
	}while(btr -= 4);

	spiRx(); 					/* ����CRCУ�飨�����ֽڣ�*/
	spiRx();

	SD_CS_DEASSERT;
	spiTx(0xff); 				/* �ȴ�8�� clk */

	return 0;
}
#endif	 /* INT8U receive_DataBlock(INT8U *buff,INT16U btr) */