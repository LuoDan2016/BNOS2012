/******************** (C) COPYRIGHT 2012 BOOLESION.NET ***************************
* ��Ʒ����: ������51������ E1101
* �ļ�����: MOUSEKEY.H
* ��������: BOOLESION.NET ������(BOOLESION)���ӿƼ� - NETC (�½���)
* ����汾: V1.2
* ��������: 2012/01/20
* ��������: �ļ�����.
**********************************************************************************/

#ifndef __MOUSEKEY_H__
#define __MOUSEKEY_H__



/* �������� */
sbit KEY_ENTER      = P2^1;	 /* ȷ��/���� */
sbit KEY_PRE        = P2^2;	 /* ��һ��/��һ�� */
sbit KEY_NEXT       = P2^0;	 /* ��һ��/��һ�� */
sbit KEY_DOWN_EXIT  = P3^2;	 /* ����/�˳� */
sbit KEY_UP_VOL     = P4^5;	 /* ����/���� */


 
void MouseInit(INT16U x,INT16U y);
void MouseScan(void);



#endif /*NED  __MOUSEKEY_H__ */