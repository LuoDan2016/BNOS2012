/******************** (C) COPYRIGHT 2012 BOOLESION.NET ***************************
* 产品名称: 布尔创51开发板 E1101
* 文件名称: GUIMIAN.H
* 程序作者: BOOLESION.NET 布尔创(BOOLESION)电子科技 - NETC (陈建长)
* 程序版本: V1.2
* 编制日期: 2012/01/20
* 功能描述: 文件包含.
**********************************************************************************/

#ifndef __GUIMIAN_H__
#define __GUIMIAN_H__

/* 启动界面GUI */
void GUI_BRCLOGO(void);
void GUI_BNOSWALPAPER(void);		

/* 颜色定义 */
#define TASKBARCOLOR RGB(34,32,36)
/*  菜单标识定义 */
#define MAINMENU            0	 /* 主菜单标识 0 */
#define MAINMENU_MUSIC      1
#define MAINMENU_PHOTOS     2
#define MAINMENU_RADIO      3
#define MAINMENU_CALENDAR   4
#define MAINMENU_EBOOK      5
#define MAINMENU_CALCULATOR 6
#define MAINMENU_APP        7
#define MAINMENU_SETTINGS   8
/* SLOGO.BMP 布尔创LOGO 路径 */
#define BRCLOGO  "system/slogo.bmp"
/* WPAPER.BMP 墙纸 路径*/
#define WPAPER "system/Wpaper.bmp"
/* 动态主菜单选择 */
void MovMenu(void);
void GUI_MainMenu(void);
void MainIco(void);


#endif /* END __GUIMIAN_H__ */
