/******************** (C) COPYRIGHT 2012 BOOLESION.NET ***************************
* ��Ʒ����: ������51������ E1101
* �ļ�����: GUIMIAN.H
* ��������: BOOLESION.NET ������(BOOLESION)���ӿƼ� - NETC (�½���)
* ����汾: V1.2
* ��������: 2012/01/20
* ��������: �ļ�����.
**********************************************************************************/

#ifndef __GUIMIAN_H__
#define __GUIMIAN_H__

/* ��������GUI */
void GUI_BRCLOGO(void);
void GUI_BNOSWALPAPER(void);		

/* ��ɫ���� */
#define TASKBARCOLOR RGB(34,32,36)
/*  �˵���ʶ���� */
#define MAINMENU            0	 /* ���˵���ʶ 0 */
#define MAINMENU_MUSIC      1
#define MAINMENU_PHOTOS     2
#define MAINMENU_RADIO      3
#define MAINMENU_CALENDAR   4
#define MAINMENU_EBOOK      5
#define MAINMENU_CALCULATOR 6
#define MAINMENU_APP        7
#define MAINMENU_SETTINGS   8
/* SLOGO.BMP ������LOGO ·�� */
#define BRCLOGO  "system/slogo.bmp"
/* WPAPER.BMP ǽֽ ·��*/
#define WPAPER "system/Wpaper.bmp"
/* ��̬���˵�ѡ�� */
void MovMenu(void);
void GUI_MainMenu(void);
void MainIco(void);


#endif /* END __GUIMIAN_H__ */
