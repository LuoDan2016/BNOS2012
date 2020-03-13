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
	if (!SD_init())				//初始化成功
	{			
		stat &= ~STA_NOINIT; 	//清STA_NOINIT
	} 

	return stat;
}



/*-----------------------------------------------------------------------*/
/* Read Partial Sector                                                   */
/*-----------------------------------------------------------------------*/

/*-----------------------------------------------------------------------*/
/* 函数功能：读指定扇区                            		                 */
/* 函数参数：															 */
/*  	BYTE* buff,					Pointer to the destination object	 */
/*		DWORD sector,				Sector number (LBA)					 */
/*		WORD offset,				Offset in the sector				 */
/*		WORD count					Byte count (bit15:destination)		 */
/* 函数返回：															 */
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

	byteLeft=512-offset-count;                //接收数据后，跳过的字节数

	if((offset+count)>512)					return RES_PARERR;	//读取字节超出扇区	
	if(SD_sendCommand(CMD17, sector<<9))	return RES_ERROR;	//读命令发送失败
			
	SD_CS_ASSERT;
	do 							//等待起始数据块起始标志0xfe (0x11111110)
	{  		
		response=spiRx();
		if(retry++ > 0xfffe)	//超时错误
		{
			SD_CS_DEASSERT;
			return RES_ERROR;
		} 
	}while(response != 0xfe); 	//等待回应

	if (offset) 				//跳过offset（偏移字节数）个数据
	{	
		do
		{
			spiRx(); 
		}while (--offset);
	}
	if(buff)
	{
		do 						//接收到的数据块数据存入缓冲区
		{
			*buff++=spiRx();
		}while (--count);

	}
	else
	{
		//dummy
	}

	if (byteLeft) 				//跳过byteLeft个数据
	{	
		do
		{
			spiRx(); 
		}while (--byteLeft);
	}

	spiRx(); 					//忽略CRC校验（两个字节）
	spiRx();

	res= RES_OK;

	SD_CS_DEASSERT;
	spiTx(0xff); 				//等待8个 clk

	return res;
}


/*-----------------------------------------------------------------------*/
/* Write Partial Sector                                                  */
/*-----------------------------------------------------------------------*/

/*-----------------------------------------------------------------------*/
/* 函数功能：写指定扇区                            		                 */
/* 函数参数：															 */
/*  	BYTE* buff,					Pointer to the destination object	 */
/*		DWORD sector,				Sector number (LBA)					 */
/* 函数返回：															 */
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

			spiRx(); 			//忽略CRC校验（两个字节）
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
			spiTx(0xff); 		//等待8个 clk

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