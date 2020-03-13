/******************** (C) COPYRIGHT 2012 BOOLESION.NET ***************************
* 产品名称: BNOS 2012
* 文件名称: BMPDECODE.H
* 程序作者: BOOLESION.NET 布尔创(BOOLESION)电子科技 - NETC (陈建长)
* 程序版本: V1.2
* 编制日期: 2012/03/20
* 功能描述: BMP解码处理.
**********************************************************************************/

#ifndef __BMPDECODE_H__
#define __BMPDECODE_H__


INT8U BmpDecode(INT16U x,INT8U y,INT8U *BMPPath);
void FlashGraphDis(INT16U x,INT16U y,INT16U width,INT16U high,INT32U GraphAddr);


#endif /* END __BMPDECODE_H__ */