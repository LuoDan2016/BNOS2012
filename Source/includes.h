/******************** (C) COPYRIGHT 2012 BOOLESION.NET ***************************
* 产品名称: 布尔创51开发板 E1101
* 文件名称: includes.h
* 程序作者: BOOLESION.NET 布尔创(BOOLESION)电子科技 - NETC (陈建长)
* 程序版本: V1.2
* 编制日期: 2012/01/20
* 功能描述: BNOS 文件包含.
**********************************************************************************/

#ifndef __INCLUDES_H__
#define __INCLUDES_H__

/* TASK PRIO DEFINE*/
#define		OSMAINTASK     5
#define		MENUAPP        7
#define		OSTIMETASK	   6
#define		SDCHECKTASK	   8
/* INCLUDE OS CORE H-FILES */
#include    <stc12c5a60s2.h>
#include    <string.h>
#include    <intrins.h>
#include 	<math.h>
#include    "os_cpu.h"
#include    "os_cfg.h"
#include    "bnos.h"
/* INCLUDE APPLICATION H-FILES */
#include 	"application.h"
#include 	"uart.h"
#include 	"OTM4001.h"
#include 	"spi.h"
#include 	"spiflash.h"
#include 	"sdcard.h"	
#include 	"sdcard.h"
#include 	"diskio.h"
#include 	"pff.h"
#include 	"guimain.h"
#include 	"bmpdecode.h"
#include 	"vs1003.h"
#include 	"bGUI.h"
#include 	"mousekey.h"
#include 	"guimusicplayer.h"
#include 	"musicdecode.h"
#include 	"guiphotos.h"
#include 	"photosplay.h"
#include 	"commonfun.h"
#include    "time.h"
#include    "guicalendar.h"
#include 	"tea5767.h"
#include 	"guiradio.h"
#include 	"guiebook.h"
#include 	"ebook.h"
#include 	"guicalculator.h"
#include	"calculator.h"
#include	"guihelloworld.h"
#include	"helloworld.h"
#include	"guisettings.h"
#include	"settings.h"
#include	"fm.h"
#include	"osmsg.h"
#include	"ch.h"
#include	"en.h"
#include	"langcommon.h"
#include	"devicesinit.h"


#endif	/*END __INCLUDES__ */

