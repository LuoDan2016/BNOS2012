/******************** (C) COPYRIGHT 2012 BOOLESION.NET ***************************
* ��Ʒ����: ������51������ E1101
* �ļ�����: MUSICDECODE.H
* ��������: BOOLESION.NET ������(BOOLESION)���ӿƼ� - NETC (�½���)
* ����汾: V1.2
* ��������: 2012/01/20
* ��������: �ļ�����.
**********************************************************************************/

#ifndef __MUSICDECODE_H__
#define __MUSICDECODE_H__

/* ���ſ��� */
#define MUSICPLAY   0 /* ���� */
#define MUSICPAUSE  2 /* ��ͣ */	
/* ����ģʽ */
#define GENERALMODE   0 /* ��ͨģʽ ����Ŀ¼����������һ��*/
#define SINGLECYCLE   1	/* ����ѭ�� */
#define ALLCYCLE 	  2	/* ȫ��ѭ�� */
 
void MusicDecode(void);
unsigned int VsGetDecodeTime(void);


#endif /* END __MUSICDECODE_H__ */