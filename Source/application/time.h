/******************** (C) COPYRIGHT 2012 BOOLESION.NET ***************************
* ��Ʒ����: ������51������ E1101
* �ļ�����: TIME.H
* ��������: BOOLESION.NET ������(BOOLESION)���ӿƼ� - NETC (�½���)
* ����汾: V1.2
* ��������: 2012/01/20
* ��������: �ļ�����.
**********************************************************************************/


#ifndef __TIME_H__
#define __TIME_H__

/* ϵͳʱ��ṹ�� */
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
