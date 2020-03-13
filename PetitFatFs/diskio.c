/*-----------------------------------------------------------------------*/
/* Low level disk I/O module skeleton for Petit FatFs (C)ChaN, 2009      */
/*-----------------------------------------------------------------------*/

#include "diskio.h"
#include "pff.h"

#include "includes.h"




/*-----------------------------------------------------------------------*/
/* Initialize Disk Drive                                                 */
/*-----------------------------------------------------------------------*/

DSTATUS disk_initialize (void)
{
	DSTATUS stat=STA_NOINIT;
	if (!SD_init())				//��ʼ���ɹ�
	{			
		stat &= ~STA_NOINIT; 	//��STA_NOINIT
	} 

	return stat;
}



/*-----------------------------------------------------------------------*/
/* Read Partial Sector                                                   */
/*-----------------------------------------------------------------------*/

/*-----------------------------------------------------------------------*/
/* �������ܣ���ָ������                            		                 */
/* ����������															 */
/*  	BYTE* buff,					Pointer to the destination object	 */
/*		DWORD sector,				Sector number (LBA)					 */
/*		WORD offset,				Offset in the sector				 */
/*		WORD count					Byte count (bit15:destination)		 */
/* �������أ�															 */
/*		RES_OK (0)
/*The function succeeded.
/*		RES_ERROR
/*Any hard error occured during the disk read operation and could not recover it.
/*		RES_PARERR
/*	Invalid parameter.
/*		RES_NOTRDY
/*The disk drive has not been initialized.
/*-----------------------------------------------------------------------*/

DRESULT disk_readp(BYTE* buff,DWORD sector,WORD offset,WORD count)
{
	DRESULT res;
	INT8U response=0xff;
	INT16U byteLeft,retry=0;

	byteLeft=512-offset-count;                //�������ݺ��������ֽ���

	if((offset+count)>512)					return RES_PARERR;	//��ȡ�ֽڳ�������	
	if(SD_sendCommand(CMD17, sector<<9))	return RES_ERROR;	//�������ʧ��
			
	SD_CS_ASSERT;
	do 							//�ȴ���ʼ���ݿ���ʼ��־0xfe (0x11111110)
	{  		
		response=spiRx();
		if(retry++ > 0xfffe)	//��ʱ����
		{
			SD_CS_DEASSERT;
			return RES_ERROR;
		} 
	}while(response != 0xfe); 	//�ȴ���Ӧ

	if (offset) 				//����offset��ƫ���ֽ�����������
	{	
		do
		{
			spiRx(); 
		}while (--offset);
	}
	if(buff)
	{
		do 						//���յ������ݿ����ݴ��뻺����
		{
			*buff++=spiRx();
		}while (--count);

	}
	else
	{
		//dummy
	}

	if (byteLeft) 				//����byteLeft������
	{	
		do
		{
			spiRx(); 
		}while (--byteLeft);
	}

	spiRx(); 					//����CRCУ�飨�����ֽڣ�
	spiRx();

	res= RES_OK;

	SD_CS_DEASSERT;
	spiTx(0xff); 				//�ȴ�8�� clk

	return res;
}


/*-----------------------------------------------------------------------*/
/* Write Partial Sector                                                  */
/*-----------------------------------------------------------------------*/

/*-----------------------------------------------------------------------*/
/* �������ܣ�дָ������                            		                 */
/* ����������															 */
/*  	BYTE* buff,					Pointer to the destination object	 */
/*		DWORD sector,				Sector number (LBA)					 */
/* �������أ�															 */
/*		RES_OK (0)
/*The function succeeded.
/*		RES_ERROR
/*Any hard error occured during the disk read operation and could not recover it.
/*		RES_PARERR
/*	Invalid parameter.
/*		RES_NOTRDY
/*The disk drive has not been initialized.
/*-----------------------------------------------------------------------*/
#if _USE_WRITE
DRESULT disk_writep (BYTE* buff,DWORD sector)
{
	DRESULT res;
	INT16U retry;// 
	WORD bc;
	static WORD wc;

	res=RES_ERROR;

	if (!buff) 
	{
		if (sector) 				// (0.1)Initiate write process
		{		
			if (SD_sendCommand(CMD24,sector<<9)== 0)/* WRITE_SINGLE_BLOCK */
			{
				spiTx(0xFF);							/* Data block header */

				SD_CS_ASSERT;

				spiTx(0xFE);
				wc = 512;								/* Set byte counter */
				res = RES_OK;
			}
		}
		 
		else  						// (0.0)Finalize write process
		{
			while (wc--) spiTx(0);	/* Fill left bytes with zeros */

			spiRx(); 			//����CRCУ�飨�����ֽڣ�
			spiRx();

			if ((spiRx() & 0x1F) != 0x05) 	/* Receive data resp and wait for end of write process in timeout of 300ms */
			{
				SD_CS_DEASSERT;           /*AAA='110'-data rejected due to write error*/
 		 		return 1;
			}

			do
			{
				if(retry++ > 0xfffe)
				{
					SD_CS_DEASSERT;
					return RES_ERROR;
				}
			}while(spiRx()!=0xff); //wait until the SD is not busy
		
			SD_CS_DEASSERT;
			spiTx(0xff); 		//�ȴ�8�� clk

			res = RES_OK;			 
		}
		return res;
	}
	 
	else       						// (1.1)Send data to the disk
	{  
		bc=(WORD)sector;

		while(bc&&wc)
		{
			spiTx(*buff++);
			bc--; wc--;
		}
		
		res=RES_OK;	 
	}

	return res;
}
#endif