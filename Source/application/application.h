/******************** (C) COPYRIGHT 2012 BOOLESION.NET ***************************
* 产品名称: 布尔创51开发板 E1101
* 文件名称: APPLICATION.H
* 程序作者: BOOLESION.NET 布尔创(BOOLESION)电子科技 - NETC (陈建长)
* 程序版本: V1.1
* 编制日期: 2012/01/20
* 功能描述: 文件包含.
**********************************************************************************/

#ifndef __APPLICATION_H__
#define __APPLICATION_H__

/* 任务函数声明 */
extern void OSMainTask(void *pdat);
extern void MenuApp(void *pdat);
extern void OSTimeTask(void *pdat);
extern void SDCheckTask(void *pdat);

#endif /* __APPLICATION_H__ */
