/******************** (C) COPYRIGHT 2012 BOOLESION.NET ***************************
* ��Ʒ����: ������51������ E1101
* �ļ�����: spiflash.c
* ��������: BOOLESION.NET ������(BOOLESION)���ӿƼ� - NETC (�½���)
* ����汾: V1.2
* ��������: 2012/03/20
* ��������: SPI FLASH W25X16��������.
**********************************************************************************/

/* Includes ---------------------------------------------------------------------*/
#include "includes.h"

/* �������� ---------------------------------------------------------------------*/

#if 0
/*********************************************************************************
** ��������: void M25P16_Read_Id(INT8U * id).
** ��������: ��ȡоƬID.
** �������: INT8U * id.         
** �������: None.
** ���ز���: None.
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
** ��������: void SPI_FLASH_Write_Enable(void).
** ��������: SPI_FLASHдʹ�ܣ���WEL��λ.
** �������: None.         
** �������: None.
** ���ز���: None.
**********************************************************************************/
void M25P16_Write_Enable(void)
{
	Select_Flash();	
	SPI_Flash_Write(WRITE_ENABLE);	
	NotSelect_Flash();
}



/*********************************************************************************
** ��������: void SPI_FLASH_Write_Disable(void).
** ��������: SPI_FLASHд��ֹ�� ��WEL����.
** �������: None.         
** �������: None.
** ���ز���: None.
**********************************************************************************/
void M25P16_Write_Disable(void)
{
	Select_Flash();	
	SPI_Flash_Write(WRITE_DISABLE);	
	NotSelect_Flash();
}

/*********************************************************************************
** ��������: void SPI_Flash_Read(INT8U* pBuffer,INT16U ReadAddr,u16 NumByteToRead).
** ��������: ��ȡSPI FLASH�� ��ָ����ַ��ʼ��ȡָ�����ȵ�����.
** �������: pBuffer:���ݴ洢��
			 ReadAddr:��ʼ��ȡ�ĵ�ַ(24bit)
			 NumByteToRead:Ҫ��ȡ���ֽ���(���65535).         
** �������: None.
** ���ز���: None.
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
** ��������: void M25P16_Write_Status_Reg(INT8U reg).
** ��������: ��ȡSPI FLASH�� ��ָ����ַ��ʼ��ȡָ�����ȵ�����.
** �������: INT8U reg.         
** �������: None.
** ���ز���: None.
**********************************************************************************/
void M25P16_Write_Status_Reg(INT8U reg)
{
	Select_Flash();	
	SPI_Flash_Write(WRITE_STAUS_REG);	
	SPI_Flash_Write(reg);
	NotSelect_Flash();
}

/*********************************************************************************
** ��������: void M25P16_Page_Program(INT16U addr,u16 len,INT8U *buf).
** ��������: ҳ��̺�����ҳ���ǰһ��Ҫ����ҳ����.
** �������: INT16U addr,u16 len,INT8U *buf.         
** �������: None.
** ���ز���: None.
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
** ��������: void M25P16_Sector_Erase(INT16U addr).
** ��������: ҳ����.
** �������: INT16U addr.         
** �������: None.
** ���ز���: None.
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
** ��������: void M25P16_Bulk_Erase(void).
** ��������: ȫ������.
** �������: None.         
** �������: None.
** ���ز���: None.
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
** ��������: void M25P16_Bulk_Erase(void).
** ��������: ����״̬.
** �������: None.         
** �������: None.
** ���ز���: None.
**********************************************************************************/
void M25P16_Deep_Power_Down(void)
{
	Select_Flash();	
	SPI_Flash_Write(DEEP_POWER_DOWN);	
	NotSelect_Flash();
}

/*********************************************************************************
** ��������: INT8U M25P16_Wake_Up(void).
** ��������: ���Ѻ���.
** �������: None.         
** �������: None.
** ���ز���: None.
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
** ��������: void M25P16_Fast_Read_Data(INT16U addr,INT16U len,INT8U *buf).
** ��������: ���ٶ�����.
** �������: INT16U addr,INT16U len,INT8U *buf.         
** �������: None.
** ���ز���: None.
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
** ��������: INT8U M25P16_Init(void).
** ��������: SPI FLASH ��ʼ��.
** �������: None.         
** �������: None.
** ���ز���: FLASH_ID ����ID.
**********************************************************************************/
INT8U M25P16_Init(void)
{	
// 	INT8U *FLASH_ID;
	/* ��ѡflash */
	NotSelect_Flash();
//	M25P16_Read_Id(FLASH_ID);
//	return FLASH_ID;
}

