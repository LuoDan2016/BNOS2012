/******************** (C) COPYRIGHT 2012 BOOLESION.NET ***************************
* 产品名称: 布尔创51开发板 E1101
* 文件名称: TIME.H
* 程序作者: BOOLESION.NET 布尔创(BOOLESION)电子科技 - NETC (陈建长)
* 程序版本: V1.2
* 编制日期: 2012/01/20
* 功能描述: 文件包含.
**********************************************************************************/


#ifndef __TIME_H__
#define __TIME_H__

/* 系统时间结构体 */
typedef struct {
	INT16U year;
	INT8U mon;
	INT8U day;
	INT8U week;
	INT8U hour;
	INT8U min;
	INT8U sec;
}SYS_TIME;


INT8U GetWeekMaxDay(INT16U year,INT8U m,INT8U d);
void CalendarApp(void);

#endif /* END __TIME_H__ */
