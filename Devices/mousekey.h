/******************** (C) COPYRIGHT 2012 BOOLESION.NET ***************************
* 产品名称: 布尔创51开发板 E1101
* 文件名称: MOUSEKEY.H
* 程序作者: BOOLESION.NET 布尔创(BOOLESION)电子科技 - NETC (陈建长)
* 程序版本: V1.2
* 编制日期: 2012/01/20
* 功能描述: 文件包含.
**********************************************************************************/

#ifndef __MOUSEKEY_H__
#define __MOUSEKEY_H__



/* 按键定义 */
sbit KEY_ENTER      = P2^1;	 /* 确定/进入 */
sbit KEY_PRE        = P2^2;	 /* 上一步/上一个 */
sbit KEY_NEXT       = P2^0;	 /* 下一步/下一个 */
sbit KEY_DOWN_EXIT  = P3^2;	 /* 向下/退出 */
sbit KEY_UP_VOL     = P4^5;	 /* 向上/音量 */


 
void MouseInit(INT16U x,INT16U y);
void MouseScan(void);



#endif /*NED  __MOUSEKEY_H__ */