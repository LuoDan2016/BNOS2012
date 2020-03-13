/******************** (C) COPYRIGHT 2012 BOOLESION.NET ***************************
* 产品名称: BNOS 2012
* 文件名称: devicesinit.h
* 程序作者: BOOLESION.NET 布尔创(BOOLESION)电子科技 - NETC (陈建长)
* 程序版本: V1.2
* 编制日期: 2012/03/20
* 功能描述: BNOS 设备初始化.
**********************************************************************************/

#ifndef __DEVICESINIT_H__
#define __DEVICESINIT_H__
/* SPI FLASH 数据存储表 */
/* 
**使用Imaga2LCD.EXE将BMP文件转化为C语言数组
**使用Text2Bin.exe将C语言数组文件转换成2进制文件
**BMP文件不包含头文件数据
**GB2312      GB2312汉字字库表 0 - 261695 字节
**SLOGO     	图像文件 100 x 66  24bit 字节
**Music  			音乐图标  281497 - 287436 字节
**Photos 			相册图标  287437 - 293376 字节
**Ridio 			收音机图标  293377 - 299316 字节
**Calendar  	万年历图标  299317 - 305256 字节
**Ebook 			电子书图标  305257 - 311196 字节
**Calculator 	计算器图标  311197 - 317136 字节
**Application 程序图标  317137 - 323076 字节
**Settings 		设置图标  323077 - 329016 字节
*/

/* GB2312 字库表基址 0 - 261695*/
#define	FLASHADDR_GB2312 	0
/* 布尔创LOGO SLOGO 261696 -  281496  */
#define	FLASHADDR_SLOGO   	261696	
/* 音乐图标  281497 - 287436*/
#define	FLASHADDR_MUSIC		281497
/* Photos 相册图标  287437 - 293376 字节 */
#define	FLASHADDR_PHOTOS	287437
/* Ridio 收音机图标  293377 - 299316 字节 */
#define	FLASHADDR_RADIO	     293377
/* Calendar 万年历图标  299317 - 305256 字节 */
#define	FLASHADDR_CALENDAR	     299317
/* Ebook 电子书图标  305257 - 311196 字节 */
#define	FLASHADDR_EBOOK	     305257
/* Calculator 计算器图标  311197 - 317136 字节 */
#define	FLASHADDR_CALCU	     311197
/* Application 程序图标  317137 - 323076 字节 */
#define	FLASHADDR_APP     317137
/* Settings 设置图标  323077 - 329016 字节 */
#define	FLASHADDR_SETTINGS     323077
void DeviceInit(void);
void FontGUILoad(void);

#endif	/* __DEVICESINIT_H__ */

