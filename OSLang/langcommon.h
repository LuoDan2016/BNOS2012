/******************** (C) COPYRIGHT 2012 BOOLESION.NET ***************************
* 产品名称: BNOS 2012
* 文件名称: langcommon.h
* 程序作者: BOOLESION.NET 布尔创(BOOLESION)电子科技 - NETC (陈建长)
* 程序版本: V1.2
* 编制日期: 2012/03/20
* 功能描述: 系统语言.
**********************************************************************************/

#ifndef __LANGCOMMON_H__
#define __LANGCOMMON_H__

/* 版本信息 */
#define COMNLANG_BNOSINF LCD_Write_String(4,4,"BNOS 2012 BOOLESION.NET -NETC",White,Back_Color,1)
/* Flash 初始化显示 */
#define COMNLANG_FLASHINIT LCD_Write_String(4,22,"SPI Flash Initialize.",White,Back_Color,1)
/* SD/TF卡初始化 */
#define COMNLANG_SDCARDINIT LCD_Write_String(4,40,"SD/TF Card Initialize And FaFs Mount...",White,Back_Color,1)
#define COMNLANG_SDOK LCD_Write_String(4,58,"TF/SD Crad Initialize And FaFs Mount OK.",White,Back_Color,1)
#define COMNLANG_SDERROR LCD_Write_String(4,58,"TF/SD Crad Initialize ERROR!",Red,Back_Color,1)
/* VS1003初始化 */
#define COMNLANG_VSINIT LCD_Write_String(4,76,"VS1003 Initialize",White,Back_Color,1)
/* GBK 字库表 */
#define COMNLANG_FONTOK	LCD_Write_String(4,94,"GB2312 Font Table OK.",White,Back_Color,1)
#define COMNLANG_FONTERROR	LCD_Write_String(4,94,"GB2312 Font Table Error.",Red,Back_Color,1)
#define COMNLANG_BGKLOAD LCD_Write_String(4,110,"Loading GB2312 Font...",White,Back_Color,1)
#define COMNLANG_BGKLOADERROR LCD_Write_String(4,110,"Set the font file is stored in the SD card!",Red,Back_Color,1)
#define COMNLANG_BGKWRITEINF LCD_Write_String(4,110,"Is being written to GB2312 font, please wait...",White,Back_Color,1)

#define COMNLANG_BGKTEST LCD_Write_String(4,110,"中文语言加载完成.字库:GB2312，宋体，常规，12号.",String_Color,Back_Color,1)


/* 布尔创logo信息 */
#define COMNLANG_COPYRIGHT LCD_Write_String(4,216,"Boolesion Electronic Technology Co., Ltd.",White,Back_Color,1)




#endif /* __LANGCOMMON_H__ */