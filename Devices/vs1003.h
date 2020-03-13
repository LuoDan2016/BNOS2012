/******************** (C) COPYRIGHT 2012 BOOLESION.NET ***************************
* 产品名称: 布尔创51开发板 E1101
* 文件名称: VS1003.H
* 程序作者: BOOLESION.NET 布尔创(BOOLESION)电子科技 - NETC (陈建长)
* 程序版本: V1.2
* 编制日期: 2012/03/20
* 功能描述: 文件包含.
**********************************************************************************/


#ifndef __VS1003_H__
#define __VS1003_H__

/* 硬件接口定义 */
sbit VS_DCS  =P3^4;
sbit VS_DREQ =P3^5;
sbit VS_RST  =P3^6;
sbit VS_CS   =P3^3; 

#define  VS_WriteByte	spiTx
#define  VS_ReadByte 	spiRx
  
/* 宏定义 */   
#define VS_WRITE_CMD        0x02    //写命令
#define VS_Read             0x03    //读命令
#define VS_MODE             0x00    //控制模式
#define VS_STATUS           0x01    //VS1003 状态
#define VS_BASS             0x02    //内置高/低音增强器
#define VS_CLOCKF           0x03    //时钟频率 + 倍频数
#define VS_DECODE_TIME      0x04    //每秒解码次数
#define VS_AUDATA           0x05    //音频数据
#define VS_WRAM             0x06    //RAM 读写
#define VS_WRAMADDR         0x07    //RAM 读写地址
#define VS_HDAT0            0x08    //流头数据0
#define VS_HDAT1            0x09    //流头数据1
#define VS_AIADDR           0x0A    //应用程序起始地址
#define VS_VOL              0x0B    //音量控制
#define VS_AICTRL0          0x0C    //应用控制寄存器0
#define VS_AICTRL1          0x0D    //应用控制寄存器1
#define VS_AICTRL2          0x0E    //应用控制寄存器2
#define VS_AICTRL3          0x0F    //应用控制寄存器3




/* 函数声明 */
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
