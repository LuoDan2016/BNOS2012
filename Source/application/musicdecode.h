/******************** (C) COPYRIGHT 2012 BOOLESION.NET ***************************
* 产品名称: 布尔创51开发板 E1101
* 文件名称: MUSICDECODE.H
* 程序作者: BOOLESION.NET 布尔创(BOOLESION)电子科技 - NETC (陈建长)
* 程序版本: V1.2
* 编制日期: 2012/01/20
* 功能描述: 文件包含.
**********************************************************************************/

#ifndef __MUSICDECODE_H__
#define __MUSICDECODE_H__

/* 播放控制 */
#define MUSICPLAY   0 /* 播放 */
#define MUSICPAUSE  2 /* 暂停 */	
/* 播放模式 */
#define GENERALMODE   0 /* 普通模式 播放目录下所有音乐一遍*/
#define SINGLECYCLE   1	/* 单曲循环 */
#define ALLCYCLE 	  2	/* 全部循环 */
 
void MusicDecode(void);
unsigned int VsGetDecodeTime(void);


#endif /* END __MUSICDECODE_H__ */