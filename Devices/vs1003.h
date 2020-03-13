/******************** (C) COPYRIGHT 2012 BOOLESION.NET ***************************
* ��Ʒ����: ������51������ E1101
* �ļ�����: VS1003.H
* ��������: BOOLESION.NET ������(BOOLESION)���ӿƼ� - NETC (�½���)
* ����汾: V1.2
* ��������: 2012/03/20
* ��������: �ļ�����.
**********************************************************************************/


#ifndef __VS1003_H__
#define __VS1003_H__

/* Ӳ���ӿڶ��� */
sbit VS_DCS  =P3^4;
sbit VS_DREQ =P3^5;
sbit VS_RST  =P3^6;
sbit VS_CS   =P3^3; 

#define  VS_WriteByte	spiTx
#define  VS_ReadByte 	spiRx
  
/* �궨�� */   
#define VS_WRITE_CMD        0x02    //д����
#define VS_Read             0x03    //������
#define VS_MODE             0x00    //����ģʽ
#define VS_STATUS           0x01    //VS1003 ״̬
#define VS_BASS             0x02    //���ø�/������ǿ��
#define VS_CLOCKF           0x03    //ʱ��Ƶ�� + ��Ƶ��
#define VS_DECODE_TIME      0x04    //ÿ��������
#define VS_AUDATA           0x05    //��Ƶ����
#define VS_WRAM             0x06    //RAM ��д
#define VS_WRAMADDR         0x07    //RAM ��д��ַ
#define VS_HDAT0            0x08    //��ͷ����0
#define VS_HDAT1            0x09    //��ͷ����1
#define VS_AIADDR           0x0A    //Ӧ�ó�����ʼ��ַ
#define VS_VOL              0x0B    //��������
#define VS_AICTRL0          0x0C    //Ӧ�ÿ��ƼĴ���0
#define VS_AICTRL1          0x0D    //Ӧ�ÿ��ƼĴ���1
#define VS_AICTRL2          0x0E    //Ӧ�ÿ��ƼĴ���2
#define VS_AICTRL3          0x0F    //Ӧ�ÿ��ƼĴ���3




/* �������� */
void VS_Init(void);
void VS_Send_Dat32(INT8U *dat);
void VS_Flush_Buffer(void);
void VS_SinTest(INT16U x);
void VS_Write_Reg(INT8U addr,INT16U vsdata);
INT16U VS_Read_Reg(INT8U addr);
void VsGetSpec(unsigned short *p);
void VsLoadPatch(void);
void VsSetVolume(unsigned char volume);

#endif	/*END __VS1003_H__ */
